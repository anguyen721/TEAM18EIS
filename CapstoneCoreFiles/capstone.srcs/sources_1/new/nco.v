`timescale 1ns / 1ps

module	nco(i_clk, /*iphase,*/ o_voltage, ctrl); //initializing Numerically Controlled Oscillator
	parameter	TBL_BIT = 8, // log2(tbl)
			    WORD = 32, // word size
			    OUTPUT_SIZE = 8; // output width
	input	wire i_clk; //input clock
	input	wire ctrl;  //allows phase to advance
	output	wire [OUTPUT_SIZE-1:0]	o_voltage ; //the final output voltage
	/*input	wire*/reg [WORD-1:0]	iphase = 32'd16777216; //the phase step, calculated with 2^(WORD) / 2^(TBL_BIT)
	                                                       //adjusting this determines beat frequency
	reg	[WORD-1:0]	phaser; //  phase value
    initial phaser = 0; //initializes phaser
    always @(posedge i_clk) //on positive edge
            if (ctrl/*&&o_voltage*/) //if the control input is on, and voltage is valid
                begin
                    phaser <= phaser + iphase;  //phase advances by the step
                    //$display("phasr is %d", phaser); //displays phase
                    $display("%h", o_voltage); //displays voltage for graphing/testing
                end
             else
                phaser <= phaser + iphase; //still advances phase, but does not output, if control is off
    sintable stbl(i_clk, 1'b0, ctrl, phaser[(WORD-1):(WORD-TBL_BIT)], o_voltage);   //calls function sintable with inputs clock, reset, control,                      
                                                                                    //the top 8 bits of phaser, and the output o_voltage
endmodule
