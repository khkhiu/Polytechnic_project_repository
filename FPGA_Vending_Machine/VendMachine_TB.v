`timescale 1ns / 1ns

module VendMachine_TB();
    reg clk=0, btnU=0, btnL=0, btnR=0, btnD=0, btnC=0;
    reg [15:0] sw=0;
    wire [3:0] an; //Anodes
    wire [0:7] seg; //Segment a..g, dp
    wire [15:0] led;
    
    VendMachine dut(clk, btnU, btnL, btnR, btnD, btnC, sw, an, seg, led);

    always #5 clk = ~clk;

    initial begin 
        #700 sw[2]=1; // Price: $12
        #200 btnL=1;  #100 btnL=0; //Insert $2
        #200 btnR=1;  #100 btnR=0; //Insert $5
        #200 btnD=1;  #100 btnD=0; //Insert $10
        #2800 sw[2]=0; 
        #3700 sw[0]=1; // Price: $8
        #1200 $stop;
   end
    
 endmodule
