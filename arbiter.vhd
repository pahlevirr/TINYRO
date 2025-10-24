library ieee;
use ieee.std_logic_1164.all;

entity arbiter is
  port (
    out_1  : in  std_logic;
    out_2  : in  std_logic;
    clk    : in  std_logic;
    rst    : in  std_logic;
    resp   : out std_logic;
    finish : out std_logic
  );
end entity;

architecture rtl of arbiter is
  signal marked_1 : std_logic := '0';
  signal marked_2 : std_logic := '0';
  signal tmp_res  : std_logic := '0';

  signal win_1    : std_logic;
  signal win_2    : std_logic;
begin
  win_1  <= out_1 and (not out_2);
  win_2  <= out_2 and (not out_1);
  finish <= marked_1 or marked_2;
  resp   <= tmp_res;

  process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        marked_1 <= '0';
        marked_2 <= '0';
      else
        if win_1 = '1' then
          tmp_res  <= '1';
          marked_1 <= '1';
        elsif win_2 = '1' then
          tmp_res  <= '0';
          marked_2 <= '1';
        end if;
      end if;
    end if;
  end process;
end architecture;

