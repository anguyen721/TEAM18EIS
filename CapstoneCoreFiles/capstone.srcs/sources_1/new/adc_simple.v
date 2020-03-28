`timescale 1ns / 1ps
`default_nettype none
module adc_simple(i_clk, voltage, f); //Initializes adc
    input wire i_clk; 
    input wire [7:0] voltage; //voltage input from ADC or other source
    input wire [63:0] f; //function name input to allow file to be opened in another program
    integer i = 0; //iterator for for loop, faster than built-in for loop and allows for fclose(f) at end of for loop
    
   // initial begin  
   //     f = $fopen("C:/Users/Andrew Nguyen/capstone/wowthisworkssowell.txt", "w"); //opening the output file    
   // end
    
    always@(posedge i_clk)
        begin
            $fwrite(f, "%h\n", voltage); //write voltage to text file, not synthesizable
            $display("adc reading is %h\n", voltage);   //displays adc read voltage
            i = i + 1; //iteration for for loop
        end
    always@(posedge i_clk)
        if( i > 1000) //closes file and ends program once it has looped 1000 times, can be adjusted
            begin
                $fclose(f); //close file
                $finish;    //end program
            end
endmodule