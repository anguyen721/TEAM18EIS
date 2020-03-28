`timescale 1ns / 1ps//time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

module sintable_tb; 

task passTest; // test to see if output is same as expected value
        input [31:0] actualOut, expectedOut; //actualout = output , expectedout = expected value
        input [`STRLEN*8:0] testType; // string that names test
        inout [31:0] passed; // passed indexer to see if it is passed
if(actualOut === expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end // if values match then display passed else display failed
            else $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);
        endtask
  task allPassed; //test to see if all tests passed
            input [256:0] passed; //number of passed tests
            input [256:0] numTests; // number of actual tests
            
            if(passed == numTests) $display ("All tests passed"); // if all tests passed display passed else display failed
            else $display("%d tests failed",numTests-passed);
    endtask
reg clk; //clk
reg i_reset; //reset 
reg i_ce; //ctrl
reg [7:0] i_phase; //phasse input
wire [7:0] o_val; // output voltage
reg [31:0] passed = 0; //passed test indexer
reg [31:0] r_phase; //total phase
 sintable uut(//calls sintable program
     .i_clk(clk),   //i_clk set to clk
     .i_reset(i_reset), //i_reset set to i_reset
     .ctrl(i_ce), // ctrl set to i_ce
     .iphase(i_phase), // iphase set to i_phase
     .o_voltage(o_val) //o_voltage set to o_val
     );
      integer i=0; // indexer for period
      
           parameter P = 8, // log2(tbl)
	    W = 32, // word size
		OW = 8, // output width
			PW =8; // Number of bits in the input phase
   	reg	[(OW-1):0] nottbl[0:((1<<PW)-1)]; //nottbl will hold input file values
   	reg [32-1:0]	i_dphase = 32'd16777216; // phase arbitrary value subject to change
    initial    r_phase = 0; // initial total phase
    initial	$readmemh("C:/Users/Andrew Nguyen/capstone/table51_squished.txt", nottbl); //reads file into nottbl
     initial begin
     clk =1;
     repeat (512) begin //repeats an arbitrary number of times 
     if (i != 0) // if it isnt the beginning of period
     begin
     r_phase = r_phase + i_dphase; //r_phase is calculated by adding i_dphase lse r_phase is 0
     end
     i_phase =  r_phase[(32-1):(32-8)]; // i_phase is top 8 bits of r_phase
    {i_reset, i_ce, i_phase } = {1'b0, 1'b1, i_phase}; //sets reset and i_ce to 0 and 1

 #5 clk = 0;
 #5 clk = 1;
 passTest(o_val, nottbl[i],"test",passed) ; // checks to see if o_val passes
 i=i+1; //iterates
 if (i>255) //if end of period eset i and r_phase
 begin
    i=0;
    r_phase =0;
    end
end
allPassed(passed,512);
     end
     endmodule