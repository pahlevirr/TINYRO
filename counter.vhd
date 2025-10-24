library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity counter is
  port (
    din  : in  std_logic;
    clk  : in  std_logic;
    rst  : in  std_logic;
    q    : out std_logic
  );
end entity;

architecture rtl of counter is
  signal ctr      : unsigned(15 downto 0) := (others => '0');
  constant thresh : unsigned(15 downto 0) := x"FFFF";
  signal finish   : std_logic := '0';
begin
  q <= '1' when finish = '1' else '0';

  process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        ctr    <= (others => '0');
        finish <= '0';
      else
        if din = '1' then
          ctr <= ctr + 1;
        end if;
        if ctr = thresh then
          finish <= '1';
        end if;
      end if;
    end if;
  end process;
end architecture;
