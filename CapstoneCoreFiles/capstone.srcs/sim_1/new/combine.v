`timescale 1ns / 1ps
`define STRLEN 32
module combine;
task passTest;// Test passed 
        input [31:0] actualOut, expectedOut; // actualout= actual output, expected output = correct output
        input [`STRLEN*8:0] testType; //string that describes test
        inout [256:0] passed; // number of tests that passed
if(actualOut === expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end //if 
            else $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);// if generated output = real output then passed++ and display
        endtask //else passed does not iterate
        
         task allPassed; //test that checks if all tests passed
            input [7:0] passed; // number of passed tests
            input [7:0] numTests;// number of tests
            
            if(passed == numTests) $display ("All tests passed"); //if passed= nmtests display top
            else $display("Some tests failed"); //else display this one
    endtask
// NCO INPUTS
       reg clk; // clk
        reg [31:0] dphase; //incoming phase
        reg i_ce; //ctrl
        //outputs
        wire [7:0] out; //output oltage
        reg [256:0] passed; // passed tests
        wire [31:0] r_phase; //current phase
    reg [63:0] f;
       parameter P = 8, // log2(tbl)
	    W = 32, // word size
		OW = 8, // output width
			PW =8; // Number of bits in the input phase
   	reg	[(OW-1):0] tbl[0:((1<<PW)-1)]; //sinetable
    initial	$readmemh("C:/Users/Andrew Nguyen/capstone/table92_squished.txt", tbl);//read in sinetabel from file
          integer i=0; //iterator i

// ADC_SIMPLE INPUTS
 nco uut1( //initializes nco program
    .i_clk(clk), // setting i_clk to clk
     .o_voltage(out), //setting o_voltage to out
     .ctrl(i_ce)// setting ctrl to i_ce
     );
     
adc_simple uut2( //initializes adc_simple program
.i_clk(clk), //creating sets clks equal to each other
.voltage(out), //setting voltage to out
.f(f) //setting filename to f
);

  initial begin
  clk=1; //set clk to 1
  passed = 0; //set passed tests to 0
  f = $fopen("C:/Users/Andrew Nguyen/capstone/combine_test.txt", "w"); //opening the output file    
    i_ce = 1'b1; //set i_ce to 1
 repeat (1000) begin //repeat an arbitrarily amount of times
 
 #5 clk = 0; //sets clk to 0
 #5 clk = 1; //sets clk to 1: gives 1 clk tick
 passTest(out, tbl[i],"test",passed) ; //compraes actual voltage to tbl value
 i=i+1; //iterates
 if (i>255) //if i =256  which is 1 phase, then reset
 begin
    i=0; //resets phase
    end
 end
allPassed(passed, 1000); //calls allpassed to check if all tests passed
     end
endmodule
