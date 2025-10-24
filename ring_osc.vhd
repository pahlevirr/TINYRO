library ieee;
use ieee.std_logic_1164.all;

entity ring_osc is
  port (
    en : in  std_logic;
    ro : out std_logic
  );
end entity;

architecture rtl of ring_osc is
  constant num_inv : integer := 9; -- keep odd for oscillation
  signal inter_wire : std_logic_vector(num_inv downto 0);
  signal ro_i       : std_logic;

  -- Preserve the loop nets so Quartus does not optimize it away
  attribute keep    : boolean;
  attribute noprune : boolean;
  attribute keep    of inter_wire : signal is true;
  attribute noprune of inter_wire : signal is true;
  attribute keep    of ro_i       : signal is true;
  attribute noprune of ro_i       : signal is true;
begin

  -- Gate the loop; when en='0' the ring is held
  inter_wire(0) <= ro_i and en;

  gen_inv : for i in 0 to num_inv-1 generate
  begin
    inv_inst : entity work.notGate
      port map (
        Y => inter_wire(i+1),
        A => inter_wire(i)
      );
  end generate;

  ro_i <= inter_wire(num_inv);
  ro   <= ro_i;

end architecture;
