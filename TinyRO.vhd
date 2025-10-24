library ieee;
use ieee.std_logic_1164.all;

entity TinyRO is
  port (
    ui_in  : in  std_logic_vector(7 downto 0); -- Dedicated inputs
    uo_out : out std_logic_vector(7 downto 0); -- Dedicated outputs
    ena    : in  std_logic;                     -- always 1 when powered
    clk    : in  std_logic;                     -- clock
    rst_n  : in  std_logic;                      -- reset_n (active low)
	 fin	  : out std_logic_vector(7 downto 0)
  );
end entity;

architecture rtl of TinyRO is
  constant n_bits : integer := 8;
  signal rst      : std_logic;
  signal finish_b : std_logic_vector(n_bits-1 downto 0);
begin

  rst <= not rst_n;

  gen_puf : for i in 0 to n_bits-1 generate
  begin
    puf_i : entity work.puf_bit
      port map (
        chall  => ui_in,
        clk    => clk,
        rst    => rst,
        en     => ena,
        resp   => uo_out(i),
        finish => fin(i)
      );
  end generate;

end architecture;

