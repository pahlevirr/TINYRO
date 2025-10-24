library ieee;
use ieee.std_logic_1164.all;

entity puf_bit is
  port (
    chall  : in  std_logic_vector(7 downto 0);
    clk    : in  std_logic;
    rst    : in  std_logic;
    en     : in  std_logic;
    resp   : out std_logic;
    finish : out std_logic
  );
end entity;

architecture rtl of puf_bit is
  constant n_ro   : integer := 8;
  constant n_half : integer := n_ro/2;

  -- Compute selector width = ceil(log2(n_half))
  function clog2(n : positive) return natural is
    variable r : natural := 0;
    variable v : natural := n - 1;
  begin
    while v > 0 loop
      r := r + 1;
      v := v / 2;
    end loop;
    return r;
  end function;

  constant SELW : integer := clog2(n_half);

  signal ro_out    : std_logic_vector(n_ro-1 downto 0);
  signal mux_out_1 : std_logic;
  signal mux_out_2 : std_logic;
  signal ctr_out_1 : std_logic;
  signal ctr_out_2 : std_logic;
begin
  -- Ensure challenge bus can cover both MUX selects
  assert 2*SELW <= 8 report "chall width insufficient for n_ro" severity failure;
  -- First half ring oscillators (0..15)
  gen_ro_1 : for i in 0 to n_half-1 generate
  begin
    ro_i : entity work.ring_osc
      port map (
        en => en,
        ro => ro_out(i)
      );
  end generate;

  -- Second half ring oscillators (16..31)
  gen_ro_2 : for i in 0 to n_half-1 generate
  begin
    ro_i : entity work.ring_osc
      port map (
        en => en,
        ro => ro_out(n_half + i)
      );
  end generate;

  mux_1 : entity work.mux_16
    generic map (
      N    => n_half,
      SELW => SELW
    )
    port map (
      ro    => ro_out(n_half-1 downto 0),
      chall => chall(SELW-1 downto 0),
      o     => mux_out_1
    );

  mux_2 : entity work.mux_16
    generic map (
      N    => n_half,
      SELW => SELW
    )
    port map (
      ro    => ro_out(n_ro-1 downto n_half),
      chall => chall((2*SELW)-1 downto SELW),
      o     => mux_out_2
    );

  cnt_1 : entity work.counter
    port map (
      din => mux_out_1,
      clk => clk,
      rst => rst,
      q   => ctr_out_1
    );

  cnt_2 : entity work.counter
    port map (
      din => mux_out_2,
      clk => clk,
      rst => rst,
      q   => ctr_out_2
    );

  race_arb : entity work.arbiter
    port map (
      out_1  => ctr_out_1,
      out_2  => ctr_out_2,
      clk    => clk,
      rst    => rst,
      resp   => resp,
      finish => finish
    );

end architecture;
