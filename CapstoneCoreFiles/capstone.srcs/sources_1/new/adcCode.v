`timescale 1ns / 1ps
`default_nettype none
module adcCode(i_clk, voltage);
    input wire i_clk;
    input wire [7:0] voltage ; //input voltage from ADC
    reg [7:0] tbl [0:255]; //register to store voltages
    integer f; 
    integer k = 0;
    integer i = 0;

   begin
   initial begin
        
        f = $fopen("C:/Users/Andrew Nguyen/capstone/output.txt", "w"); //opening the output file
    end
   
    always @(posedge i_clk)
        begin
            tbl[i] <= voltage;  //voltage is placed in table
            i = i + 1;
        end
       
     always @(posedge i_clk)
        if(i > 255) //if table is full
            begin
                i = 0;
                for(k = 0; k<255; k = k + 1) //iterates through table
                    begin
                        $fwrite(f, "%h\n", tbl[k]);  // table is written to file
                        $display("table %h\n", tbl[k]);
                    end
                    $fclose(f); //file is closed
                    $finish;
            end
     
endmodule