`timescale 1ns / 1ps
module adc_tb1;
reg clk;
reg [7:0] voltage;
adcCode uut(
.i_clk(clk),
.voltage(voltage)
);
initial begin
clk = 1;
voltage = 8'b0;
repeat (255) begin
    #5 clk = 0;
    #5 clk = 1;
    voltage = $urandom%255;
    $display("%d\n",voltage);
end
end
endmodule