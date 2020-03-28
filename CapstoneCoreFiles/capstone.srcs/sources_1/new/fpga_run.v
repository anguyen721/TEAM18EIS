`timescale 1ns / 1ps


module fpga_run(i_clk, i_ld, o_val, i_ce, voltage );

	parameter	P = 8, // log2(tbl)
			W = 32, // word size
			OW = 8; // output width
	//
	input	wire		i_clk;
	//
	input	wire		i_ld;
	
	
	//
	input	wire		i_ce;
	input wire [7:0] voltage;
	output	wire [OW-1:0]	o_val;
	integer f;
	initial begin
	   f = $fopen("C:/Users/Andrew Nguyen/capstone/combo_test.txt", "w");
	end
    
    nco osc(i_clk, i_ld, o_val, i_ce);
    adc_simple adc(i_clk, voltage, f);

	
endmodule
