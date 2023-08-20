`timescale 1ns / 1ps

// This module produces a trig signal of one clock cycle whenever the button is pressed.
module PB_Capture(clk, button, trig);
    input clk, button;
    output reg trig;

    reg reg1, reg2;
   
    always @(posedge clk) 
    begin
        reg1 <= button;// assign 'button' to reg1
        reg2 <= reg1;// assign reg1 to reg2
        trig <= reg1 & ~reg2;// assign reg1 AND negate reg2 to trig
    end
    
endmodule
