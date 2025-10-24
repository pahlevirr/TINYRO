library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mux_16 is
  generic (
    N    : positive := 16; -- number of inputs; must be 2**SELW
    SELW : positive := 4    -- select width
  );
  port (
    ro    : in  std_logic_vector(N-1 downto 0);
    chall : in  std_logic_vector(SELW-1 downto 0);
    o     : out std_logic
  );
end entity;

architecture rtl of mux_16 is
begin
  -- Variable-index select driven by chall
  o <= ro(to_integer(unsigned(chall)));
end architecture;
