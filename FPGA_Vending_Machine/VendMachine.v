`timescale 1ns / 1ns

module VendMachine(
    // I/O specifications
	input wire clk, btnU, btnL, btnR, btnD, btnC,// input, clk and pushbutton
	input wire [3:1] sw,//Switches 1,2,3 in use
	output [3:0] an, //All Anodes in use
	output [0:7] seg, //Segment of 7 segment displays, active low, hence [0:7]
	output reg [15:0]led = 0//All LEDs in use
    );

    // Project specification according to serial number
    parameter IDLE=0, COIN=1, VEND=2, REFUND=3;//Assigning states to integer
    parameter MSB=3, LSB=1; //Switches and LEDs used are 1,2,3
    parameter VEND_TIME = 1; //Vending time takes 1 seconds, make LED blink once
    parameter REFUND_TIME = 2; //Refund time takes 2 seconds
    integer i = 20;//For the countdown, starting at 20

    reg [3:0] timer=0; //4-bit time, up to 15 seconds
    reg [1:0] state=0; //Only 1 of 3 states active at once. IDLE=0, COIN=1, VEND=2, REFUND=3;
    reg [2:0] sw_reg;//For capturing the switch pattern in IDLE state.
    reg [1:0] index; //Index of the activated switches - sw1, sw2, sw3.
    reg [9:0] money=0, price=0; //10-bit to store price, from: 0 to 999
    
    //Function call display.v
    reg [15:0] display_input; // 4-digit (16-bit)
    Display display (clk, display_input, an, seg);
    
    //Function call clock.v
    wire trig_1Hz, trig_2Hz;
    Clock clock (clk, trig_1Hz, trig_2Hz);
    
    //Function call Int_to_BCD.v (convert money)
    wire [15:0] bcd; // 4-digit (16-bit)
    Int_to_BCD convert (money, bcd);
    
    //Function call PB_capture
    wire [3:0] trig; // Button signals
    PB_Capture pb1(clk, btnC, trig[0]); //Cancel
    PB_Capture pb2(clk, btnL, trig[1]); //Insert $2
    PB_Capture pb3(clk, btnR, trig[2]); //Insert $5
    PB_Capture pb4(clk, btnD, trig[3]); //Insert $10
      
    always@ (posedge clk)
        case (state)
            IDLE:   //------------------------------------------------
               begin 
                   //Task 1
                    display_input <= 16'hF000;// display 00.0
                    if (trig_2Hz == 1) //For blinking LED clk
                        led[MSB:LSB] <= ~led[MSB:LSB];//blinking LED with negation
                        money <= 0;// no money input yet, display 00.0
                    //Task 2
                    if (sw[MSB:LSB] > 0)// if any of the switches are activated
                        begin 
                            // price = 3 if sw[LSB], else price = sw[LSB+1]
                            // price = 5 if sw[LSB+1] else price = 11
                            price <= sw[LSB]? 30 : sw[LSB+1]? 70 : 110;
                            // index = 1 if sw[LSB], else index = sw[LSB+1]
                            // index = 2 if sw[LSB+1] else index = 3
                            index <= sw[LSB]? 0 : sw[LSB+1]? 1 : 2;//Assign switch pattern when in IDLE state
                            sw_reg <= sw[MSB:LSB];//Assign switch pattern when in IDLE state
                            led[15:4] <= ~led[15:4];//On LED 15 to 4
                            led[0] <= ~led[0];//On LED 0
                            led[MSB:LSB] <= ~led[MSB:LSB];//off LED 1,2,3
                            state <= COIN;// Change state to COIN
                        end//end Task 2
                end//End IDLE
            COIN:   //------------------------------------------------
                begin// Task 3
                    display_input <= bcd;//Assign fucntion call display.v to bcd
                    led[MSB:LSB] <= ~led[MSB:LSB] & sw_reg;//Assign sw pattern in IDLE state to LEDs
                    if (money >= price)// if 'money' is more than or equal to 'price'
                        begin 
                            state <= VEND;// Change state to VEND
                            timer <=0; //Assign timer as 0, changing state immediately
                        end
                    else if (trig[0]) //if BTNC(Center) is pressed, change state to REFUND 
                        begin
                            state <= REFUND;// Change state to REFUND
                            timer<=0;//Assign timer as 0, changing state immediately
                        end
                    else if (trig[1]) //if BTNL (Left) is pressed, $2 is inserted
                        begin
                            money <= money + 20;//Add $2 to 'money'
                            timer<=0;//Assign timer as 0, responding immediately
                        end
                    else if (trig[2]) //if BTNR (Right) is pressed, $5 is inserted
                        begin
                            money <= money + 50;//Add $5 to 'money'
                            timer<=0;//Assign timer as 0, responding immediately
                        end
                    else if (trig[3]) //if BTND (Down) is pressed, $10 is inserted
                        begin
                            money <= money + 100;//BTND (Down) to insert $10
                            timer<=0;//Assign timer as 0, responding immediately
                        end
                    //Jump to REFUND if user does not press in 10 seconds
                    if (trig_1Hz == 1) //trig_1Hz == 1 go 'HIGH' every 1 second
                        if (timer < 10) 
                            timer <= timer + 1;//if timer less than 10, increment to 10
                                if (timer == 10)//if timer == 10
                                    begin
                                        state <= REFUND;// Change state to REFUND
                                        timer <= 0;//Assign timer as 0, changing state immediately
                                    end

                end
            VEND:   //------------------------------------------------
            //Task 4a 
                begin 
                led[15:4]<=0;// off LED 15 to 4
                led[0]<=0;// off LED 0
                    if (trig_1Hz == 1)//trig_1Hz == 1 go 'HIGH' every 1 second
                        begin
                          i<=i-1;// For countdown, every second, i decrements by 1
                        case(i)//use 'case' for conutdown
                            20: 
                                begin
                                    display_input = 16'hF200;
                                    led[LSB+index] = 0;//LED for blinking once
                                end
                            19: 
                                begin
                                    display_input = 16'hF190;
                                    led[LSB+index] = 1;//LED for blinking once
                                end
                            18: 
                                begin
                                    display_input = 16'hF180;
                                    led[LSB+index] = 0;//LED for blinking once
                                end
                            17:
                                begin
                                    display_input = 16'hF170;
                                end
                            16: 
                                begin
                                    display_input = 16'hF160;
                                end
                            15: 
                                begin
                                    display_input = 16'hF150;
                                end
                            14: 
                                begin
                                    display_input = 16'hF140;
                                end
                            13: 
                                begin
                                    display_input = 16'hF130;
                                end
                            12: 
                                begin 
                                    display_input = 16'hF120;
                                end
                            11: 
                                begin 
                                    display_input = 16'hF110;
                                end
                            10: 
                                begin 
                                    display_input = 16'hF010;
                                end
                            9: 
                                begin
                                    display_input = 16'hF090;
                                end
                            8:
                                begin
                                    display_input = 16'hF080;
                                end
                            7: 
                                begin
                                    display_input = 16'hF070;
                                end
                            6: 
                                begin
                                    display_input = 16'hF060;
                                end
                            5: 
                                begin
                                    display_input = 16'hF050;
                                end
                            4: 
                                begin
                                    display_input = 16'hF040;
                                end
                            3: 
                                begin
                                    display_input = 16'hF030;
                                end
                            2: 
                                begin
                                    display_input = 16'hF020;
                                end
                            1:
                                begin
                                    display_input = 16'hF010;
                                end
                            0: 
                                begin 
                                    display_input = 16'hF000;
                                    state <= REFUND;//change state to refund
                                    i <= 20;// reset 'i' to 20
                                    money <= money - price;//calculate change
                                end
                        endcase// end of case
                end
            end//End task 4A
            REFUND:  //------------------------------------------------
            //Task 4b
                begin 
                    display_input <= {4'hA, bcd[11:0]};// 4'hA will show '-'
                    led[MSB:LSB] <= 0;//disale LEDs 1,2,3
                    if (trig_1Hz == 1) //trig_1Hz == 1 go 'HIGH' every 1 second
                       if (timer < REFUND_TIME) timer <= timer + 1;//increment timer, if timer less than 2 seconds 
                    if (timer == REFUND_TIME)// if timer = 2 second
                        if (sw[MSB:LSB]==0) //if switch disabled
                            begin
                                led <= 0;//Disable LEDs
                                state <= IDLE;//Change state to IDLE
                            end
                end//Task 4b
        endcase
                 
endmodule
