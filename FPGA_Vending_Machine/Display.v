`timescale 1ns / 1ns

module Display(clk, display_input, an, seg);
	input clk;
	input [15:0] display_input;
	output reg [3:0] an; ////All Anodes
	output reg [0:7] seg; //All segments are used, active low, hence [0:7], Segment a..g, dp

//Generating the 250 Hz clock (100MHz/400,000) for 7-seg display:
    reg [18:0] counter; //Mod-400,000, 19-bit counter (2**19 = 524,288)
    wire clk250Hz;
    assign clk250Hz = (counter == 1); // Enable clock calculation. Don't use 0

    parameter N = 400_000; //for real-time execution
//    parameter N = 4; //for simulation
    
    always@(posedge clk)//Mod-400,000 counter
      if (counter < N-1) counter <= counter + 1;// non blocking assignment to allow increment of counter
      else counter <= 0;

// Mod-4 counter (2-bit):
    reg [1:0] mod4; ////Mod-4 counter 0..3
    always@(posedge clk) // f = 250 Hz, T = 4 ms
       if (clk250Hz == 1) //Mod-4 counter
            if (mod4 < 3) mod4 <= mod4 + 1;// non blocking assignment to allow increment of mod4 counter
            else mod4 <= 0;
            //if (mod4 < 3) mod4 <= mod4 + 1;// non blocking assignment to allow increment of mod4 counter
            //else mod4 <= 0;// copying from 'always@(posedge clk)', line 41
                

   reg [3:0] bcd;

// 2 to 4 Encoder:
   always@(*)
        case (mod4)
        // assigning range of encoder
            3: {an, bcd} = {4'b0111, display_input[15:12]};
            2: {an, bcd} = {4'b1011, display_input[11:8]};
            1: {an, bcd} = {4'b1101, display_input[7:4]};
            0: {an, bcd} = {4'b1110, display_input[3:0]};
        endcase

// BCD to 7-segment decoder:
    always@(*) 
      begin
        case(bcd)      //abcd_efg_DP (Active-LOW)
            0: seg = 8'b0000_0011; // display 0
            1: seg = 8'b1001_1111; // display 1
            2: seg = 8'b0010_0101; // display 2
            3: seg = 8'b0000_1101; // display 3
            4: seg = 8'b1001_1001; // display 4
            5: seg = 8'b0100_1001; // display 5
            6: seg = 8'b0100_0001; // display 6
            7: seg = 8'b0001_1111; // display 7
            8: seg = 8'b0000_0001; // display 8
            9: seg = 8'b0000_1001; // display 9
            'hA: seg = 8'b1111_1101; // display '-'
            'hC: seg = 8'b0110_0010; // display 'C.'
            default : seg = 8'b1111_1111; // Blank
        endcase
        if (mod4 == 1) seg[7] = 0; //dp at digit 1, e.g. 123.0
      end
    
endmodule
