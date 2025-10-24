library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TIny_RO_top is
  generic (
    N_BITS        : positive := 8;
    SETTLE_CYCLES : positive := 8
  );
  port (
    clk    : in  std_logic;
    rst_n  : in  std_logic
  );
end entity;

architecture rtl of TIny_RO_top is

  -- Qsys system
  component MAX10NIOS is
    port (
      busy_export      : in  std_logic := '0';
      challenge_export : out std_logic_vector(7 downto 0);
      clk_clk          : in  std_logic := '0';
      enabler_export   : out std_logic;
      request_export   : out std_logic;
      reset_reset_n    : in  std_logic := '0';
      response_export  : in  std_logic_vector(7 downto 0) := (others => '0')
    );
  end component;

  -- PUF bit
  component puf_bit is
    port (
      chall  : in  std_logic_vector(7 downto 0);
      clk    : in  std_logic;
      rst    : in  std_logic;
      en     : in  std_logic;
      resp   : out std_logic;
      finish : out std_logic
    );
  end component;

  type state_t is (IDLE, RECVCHL, SETCHL, GETRES, WAITFIN, SEND, WAITREQLOW);
  signal state, state_n : state_t := IDLE;

  -- Qsys <-> FSM signals
  signal s_challenge : std_logic_vector(7 downto 0);
  signal s_enabler   : std_logic;
  signal s_request   : std_logic;
  signal s_busy      : std_logic := '0';
  signal s_response  : std_logic_vector(7 downto 0) := (others => '0');

  -- Latched challenge and PUF control
  signal chall_latched : std_logic_vector(7 downto 0) := (others => '0');
  signal puf_en        : std_logic := '0';
  signal puf_rst       : std_logic := '1';
  signal rst_sync      : std_logic := '1';

  -- PUF arrays
  signal resp_vec   : std_logic_vector(N_BITS-1 downto 0);
  signal finish_vec : std_logic_vector(N_BITS-1 downto 0);
  signal all_finish : std_logic;

  -- delay counter for SETCHL
  signal settle_cnt   : unsigned(7 downto 0) := (others => '0');
  signal settle_done  : std_logic := '0';

begin

  -- Instantiate Nios II system
  u_sys : MAX10NIOS
    port map (
      busy_export      => s_busy,
      challenge_export => s_challenge,
      clk_clk          => clk,
      enabler_export   => s_enabler,
      request_export   => s_request,
      reset_reset_n    => rst_n,
      response_export  => s_response
    );

  -- Simple sync reset
  process(clk)
  begin
    if rising_edge(clk) then
      rst_sync <= not rst_n;
    end if;
  end process;

  -- PUF array instantiation
  gen_puf : for i in 0 to N_BITS-1 generate
  begin
    puf_i : puf_bit
      port map (
        chall  => chall_latched,
        clk    => clk,
        rst    => puf_rst,
        en     => puf_en,
        resp   => resp_vec(i),
        finish => finish_vec(i)
      );
  end generate;

  -- All finished when every bit is 1
  -- Quartus/older VHDL parsers dislike unconstrained aggregates with OTHERS.
  -- Use the vector's range to build an all-ones constant of matching length.
  all_finish <= '1' when finish_vec = (finish_vec'range => '1') else '0';

  -- FSM next-state and outputs
  process(state, s_request, s_enabler, s_challenge, all_finish, settle_done, clk, rst_n)
  begin
    -- Defaults
	 if (rst_n = '0') then
		 state_n       <= IDLE;
		 s_busy        <= '0';
		 puf_en        <= '0';
		 puf_rst       <= '1';
		 settle_done   <= '0';
		 s_response    <= (others => '0');
	
	elsif rising_edge(clk) then

		 case state is
			when IDLE =>
			  -- hold PUF in reset, not busy
			  if s_request = '1' then
				 state_n <= RECVCHL;
			  end if;

			when RECVCHL =>
			  -- wait for enabler
			  s_busy        <= '0';
			  if s_enabler = '1' then
				 state_n <= SETCHL;
			  end if;

			when SETCHL =>
			  -- small delay for challenge to settle; keep PUF reset
			  s_busy      <= '1';
			  puf_rst     <= '1';
			  if settle_cnt = to_unsigned(SETTLE_CYCLES-1, settle_cnt'length) then
				 settle_done <= '1';
				 state_n     <= GETRES;
			  end if;

			when GETRES =>
			  -- release reset, enable PUF; wait for all finishes
			  s_busy  <= '1';
			  puf_rst <= '0';
			  puf_en  <= s_enabler;
			  if all_finish = '1' then
				 state_n <= SEND;
			  end if;

			when WAITFIN =>
			  -- not used currently; placeholder for robustness
			  s_busy  <= '1';
			  puf_rst <= '0';
			  puf_en  <= s_enabler;
			  if all_finish = '1' then
				 state_n <= SEND;
			  end if;

			when SEND =>
			  -- drive response back to Nios; remain busy until CPU lowers request
			  s_busy     <= '0';
			  s_response <= resp_vec;
			  if s_request = '0' then
				 state_n <= IDLE;
			  else
				 state_n <= WAITREQLOW;
			  end if;

			when WAITREQLOW =>
			  s_busy     <= '0';
			  s_response <= resp_vec;
			  if s_request = '0' then
				 state_n <= IDLE;
			  end if;
		 end case;
	end if;
  end process;

  -- Settle counter
  process(clk)
  begin
    if rising_edge(clk) then
      if (state /= SETCHL) then
        settle_cnt <= (others => '0');
      else
        if settle_cnt /= to_unsigned(SETTLE_CYCLES-1, settle_cnt'length) then
          settle_cnt <= settle_cnt + 1;
        end if;
      end if;
    end if;
  end process;

  -- Latch challenge synchronously in RECVCHL
  process(clk)
  begin
    if rising_edge(clk) then
      if rst_sync = '1' then
        chall_latched <= (others => '0');
      else
        if state = RECVCHL then
          chall_latched <= s_challenge;
        end if;
      end if;
    end if;
  end process;

  -- State register
  process(clk)
  begin
    if rising_edge(clk) then
      if rst_sync = '1' then
        state <= IDLE;
      else
        state <= state_n;
      end if;
    end if;
  end process;

end architecture;
