library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity shiftreg16 is
  port (
    din    : in  std_logic;                 -- serial input bit
    sample : in  std_logic;                 -- shift strobe (e.g., puf finish)
    clk    : in  std_logic;
    rst    : in  std_logic;
    q      : out std_logic_vector(15 downto 0); -- parallel contents
    full   : out std_logic                  -- high after 16 samples
  );
end entity;

architecture rtl of shiftreg16 is
  signal sr   : std_logic_vector(15 downto 0) := (others => '0');
  signal cnt  : unsigned(4 downto 0) := (others => '0'); -- counts 0..16
  signal full_i : std_logic := '0';
begin
  q    <= sr;
  full <= full_i;

  process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        sr     <= (others => '0');
        cnt    <= (others => '0');
        full_i <= '0';
      else
        if sample = '1' and full_i = '0' then
          sr  <= sr(14 downto 0) & din; -- shift left, new bit into LSB
          cnt <= cnt + 1;
          if cnt = 15 then
            full_i <= '1';
          end if;
        end if;
      end if;
    end if;
  end process;
end architecture;

