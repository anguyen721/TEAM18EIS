`timescale 1ns / 1ps//time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

module NCO_tb(); //name of module

task passTest; //test that checks if outputted value matches expected value
        input [256:0] actualOut, expectedOut; //actual out = what is outputted , expected out = expected output
        input [`STRLEN*8:0] testType; //string that has name of test
        inout [256:0] passed;  //number of passed test counter
if(actualOut === expectedOut) begin
 $display ("%s passed", testType); 
 passed = passed + 1;
  end // if output alues match, display passed else display failed
            else 
            $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);
            
        endtask
        
        
       task allPassed; //test to see if all tests passed
            input [256:0] passed; //number of passed tests
            input [256:0] numTests; // number of actual tests
            
            if(passed == numTests) $display ("All tests passed"); // if all tests passed display passed else display failed
            else $display("%d tests failed",numTests-passed);
    endtask

     // Inputs
       reg clk; //clk
        reg i_ce; //ctrl variable
        //outputs
        wire [7:0] out; //voltage
        integer count =1;
        reg [512:0] numTests = 512; // number of tests arbitrary and subjected to change
        parameter P = 8, // log2(tbl)
	    W = 32, // word size
		OW = 8, // output width
			PW =8; // Number of bits in the input phase
			integer check = 0;
 nco uut( // calls nco program 
    .i_clk(clk), //  i clk is set to clk
     .o_voltage(out), //  o_voltage is set to out
     .ctrl(i_ce) //ctrl is set to i_ce
     );
   integer i=0; //indexer for period
   	reg	[(OW-1):0] nottbl[0:((1<<PW)-1)]; //nottbl is sinetable

    initial	$readmemh("C:/Users/Andrew Nguyen/capstone/table92_squished.txt", nottbl); //reads text file into nottbl
    integer passed = 0;
  initial begin
  clk=1;
   {i_ce} = { 1'b1 };  // set ctrl to 1
 repeat (1024) begin //repeats loop 512 times, arbitrary and subjected to change
 #5 clk = 0;
 #5 clk = 1; // sets clk to 0 and then 1 == 1 clock tick
 //passTest(out, nottbl[i],"test",passed) ;
 count = count +1;
 i=i+1; //iterates
 if (i>255) // if i == 256 -> more than 1 period so reset i for next period
 begin
    i=0;
    end
end
//allPassed(passed, 1024); //check to see if all tests passed

end
endmodule