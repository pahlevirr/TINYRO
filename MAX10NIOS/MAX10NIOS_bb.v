
module MAX10NIOS (
	busy_export,
	clk_clk,
	enabler_export,
	response_export,
	reset_reset_n,
	challenge_export,
	request_export);	

	input		busy_export;
	input		clk_clk;
	output		enabler_export;
	input	[7:0]	response_export;
	input		reset_reset_n;
	output	[7:0]	challenge_export;
	output		request_export;
endmodule
