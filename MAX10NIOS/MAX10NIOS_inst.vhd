	component MAX10NIOS is
		port (
			busy_export      : in  std_logic                    := 'X';             -- export
			clk_clk          : in  std_logic                    := 'X';             -- clk
			enabler_export   : out std_logic;                                       -- export
			response_export  : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			reset_reset_n    : in  std_logic                    := 'X';             -- reset_n
			challenge_export : out std_logic_vector(7 downto 0);                    -- export
			request_export   : out std_logic                                        -- export
		);
	end component MAX10NIOS;

	u0 : component MAX10NIOS
		port map (
			busy_export      => CONNECTED_TO_busy_export,      --      busy.export
			clk_clk          => CONNECTED_TO_clk_clk,          --       clk.clk
			enabler_export   => CONNECTED_TO_enabler_export,   --   enabler.export
			response_export  => CONNECTED_TO_response_export,  --  response.export
			reset_reset_n    => CONNECTED_TO_reset_reset_n,    --     reset.reset_n
			challenge_export => CONNECTED_TO_challenge_export, -- challenge.export
			request_export   => CONNECTED_TO_request_export    --   request.export
		);

