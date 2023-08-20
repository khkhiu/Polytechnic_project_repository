`timescale 1ns / 1ns

module Clock(clk, trig_1Hz, trig_2Hz);
    input clk;
    output trig_1Hz, trig_2Hz;
    
    // 100 MHz clk div. by N = 1 Hz:
    parameter N = 100_000_000; //for real-time execution
//    parameter N = 100; //for simulation
 
    reg [26:0] counter=0; //27-bit counter (2**27 = 134,217,728)
    // count from 0 to 99,999,999, or from 0 to 99 for simulation. From lab_3 BCD
   
    always@(posedge clk)
      if (counter < N) counter <= counter + 1;// non blocking assignment to allow increment of counter
      else counter <= 1; // Range: 1 to N

    // trig_1Hz -> goes 'High' for one clock cycle every 1 second
    // trig_2Hz -> goes 'High' for one clock cycle every 0.5 second
    assign trig_1Hz = (counter == N);
    assign trig_2Hz = (counter % (N/2) == 0);// trig_2Hz = half of trig_1Hz
    
endmodule
