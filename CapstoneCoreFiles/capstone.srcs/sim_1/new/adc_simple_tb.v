`timescale 1ns / 1ps
module adc_simple_tb; 
reg clk; //clk 
reg [7:0] voltage = 0; //voltage
reg [63:0] f; //file

 adc_simple uut(//initializes adc_simple program
.i_clk(clk), //i_clk set to clk
.voltage(voltage), // voltage is set to voltage
.f(f) // f is set to f
);
initial begin
clk = 1;
voltage = 8'b0; //voltage initialized to 0
 f = $fopen("C:/Users/Andrew Nguyen/capstone/adc_simple_test.txt", "w"); //opening the output file    

repeat (1000) begin //repeat an arbitrary number of times
    #5 clk = 0;
    #5 clk = 1; //clk 0 and clk 1 = 1 tick 
    voltage = $urandom%255; //set voltage = to random value between 1 and 255
end
end
endmodule
