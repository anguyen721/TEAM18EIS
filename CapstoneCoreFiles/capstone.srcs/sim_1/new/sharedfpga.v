`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/13/2019 09:40:53 PM
// Design Name: 
// Module Name: sharedfpga
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sharedfpga;
//inputs
parameter	P = 8, // log2(tbl)
			W = 32, // word size
			OW = 8; // output width
	//
		reg		i_clk; // clk
	//
		reg		i_ld; //
	
	
	//
		reg		i_ce;
	 reg [7:0] voltage;
		wire [OW-1:0]	o_val;
 fpga_run uut(
 .i_clk(i_clk),
 .i_ld(i_ld),
 .o_val(o_val),
 .i_ce(i_ce),
  .voltage(voltage) );
 initial begin
  i_clk=1;     
  {i_ld,  i_ce} = {1'b1 , 1'b1 };
 repeat (1000) begin
 
 #5 i_clk = 0;
 #5 i_clk = 1;
 voltage = $urandom%255;

 end
  
     end
endmodule
