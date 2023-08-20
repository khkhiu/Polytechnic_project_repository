`timescale 1ns / 1ps

module Int_to_BCD(money, bcd);
    input [9:0] money; // Range: 0 to 99
	output reg [15:0] bcd; // 4-digit (16-bit)

    parameter MAX = 9999;//Restrict max number to 9999 on 7 seg
    parameter BLANK = 4'hF;// BLANK = 4 bit hex F = 4'b1111 = 16
    wire [13:0] n;
    wire [3:0] d3, d2, d1, d0; //Range: 0 to 9
    wire [3:0] x3, x2; //Range: 0 to 9
    
    assign n = (money > MAX)? MAX : money; //n = MAX if (int > MAX), else n = int. Hence limiting n to MAX

    assign d0 = n % 10;         //BCD LSB  
    assign d1 = (n/10) % 10;    //BCD 2-LSB
    assign d2 = (n/100) % 10;   //BCD 2-MSB, unless {d3,d2}==0
    assign d3 = (n/1000) % 10;  //BCD MSB, unless == 0
    /* Example
    let n=2170

    d0 = 2170 % 10 = 0
    d1 = (2170)/10 % 10 = 7
    d2 = (2170)/100 % 10 = 1
    d3 = (2170)/1000 % 10 = 2
    */
    assign x3 = (d3==0)? BLANK : d3;// x3 = BLANK if (d3==0), else x3 = d3
    assign x2 = ({d3,d2}==0)? BLANK : d2;// x2 = BLANK if {d3,d2}==0, else x2 = d2
                                        // BLANK only if d3 AND d2 are 0
    
    always @(*)
        bcd = {x3,x2,d1,d0};// concatenate x3, x2, d1, d0
       
endmodule