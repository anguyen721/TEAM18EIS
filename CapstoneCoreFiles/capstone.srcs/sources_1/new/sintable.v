`default_nettype	none
//
module	sintable(i_clk, i_reset, ctrl, iphase, o_voltage); //initalize function sine table
	//
	parameter   TBL_BIT = 8, // Number of bits in the input phase
			OUTPUT_SIZE = 8; // Number of output bits
	// 
	input	wire	i_clk, i_reset, ctrl;  //initializes inputs clock, reset, and control
	input	wire	[(TBL_BIT-1):0]	iphase; //initializes iphase, the phase set by NCO
	output	reg	    [(OUTPUT_SIZE-1):0]	o_voltage; //the output voltage
	//

	reg	[(OUTPUT_SIZE-1):0] tbl[0:((1<<TBL_BIT)-1)]; //initializes the table into which the periodic text file will be read into
	                                                 //The table is as wide as the table, and has 8-bit values, as the project
	                                                 //is all 8-bit

	initial	$readmemh("C:/Users/Andrew Nguyen/capstone/table92_squished.txt", tbl); //reads the periodic text file to the tbl register
	initial	o_voltage = 0; //initializes o_voltage to 0
	
	always @(posedge i_clk) //on the positive edge of the clock input
       begin
	       if (i_reset) //if the output reset has been used
		      o_voltage <= 0; //set the output to zero
	       else if (ctrl) //as long as control is on
		       o_voltage <= tbl[iphase]; //output voltage is the entry in the pre-made table selected by the phase input
end
endmodule