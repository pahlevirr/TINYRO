library ieee;
use ieee.std_logic_1164.all;


entity TInyRO_top is
  port (
    clk    : in  std_logic;                     -- clock
    rst_n  : in  std_logic                      -- reset_n (active low)
  );
end entity;

architecture rtl of TInyRO_top is

	component TinyRO is
	  port (
		 ui_in  : in  std_logic_vector(7 downto 0); -- Dedicated inputs
		 uo_out : out std_logic_vector(7 downto 0); -- Dedicated outputs
		 ena    : in  std_logic;                     -- always 1 when powered
		 clk    : in  std_logic;                     -- clock
		 rst_n  : in  std_logic;                      -- reset_n (active low)
		 fin	  : out std_logic_vector(7 downto 0)
	  );
	end component;


	component MAX10NIOS is
	port (
		busy_export      : in  std_logic                    := '0';             --      busy.export
		challenge_export : out std_logic_vector(7 downto 0);                    -- challenge.export
		clk_clk          : in  std_logic                    := '0';             --       clk.clk
		enabler_export   : in  std_logic;                  						   --   enabler.export
		request_export   : out std_logic;                                       --   request.export
		reset_reset_n    : in  std_logic                    := '0';             --     reset.reset_n
		response_export  : in  std_logic_vector(7 downto 0) := (others => '0')  --  response.export
	);
	end component;


begin



end architecture;
