library ieee;
use ieee.std_logic_1164.all;

entity notGate is
  port (
    Y : out std_logic; -- Output
    A : in  std_logic  -- Input
  );
end entity;

architecture rtl of notGate is
  signal y_i : std_logic;

  -- Preserve the inverter output net
  attribute keep    : boolean;
  attribute noprune : boolean;
  attribute keep    of y_i : signal is true;
  attribute noprune of y_i : signal is true;
begin
  y_i <= not A;
  Y   <= y_i;
end architecture;

