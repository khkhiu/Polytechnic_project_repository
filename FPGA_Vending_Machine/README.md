# Singapore Polytechnic-FPGA project
 
This is a showcase of an FPGA project I did while in Singapore Polytechnic

<strong>Introduction</strong>

***
<strong>Digital Systems Design </strong>introduces students to the world of digital electronic system design. It will cover topics such as PLD, Verilog and the design of Synchronous Sequential Logic. Students will learn about the basic programming logics devices such as PLA, PAL, CPLD and FPGA and design simple logic systems using these devices.

In this assignment, students are required to design and implement a digital system using synchronous sequential logic using finite state machines(FSM) in Verilog on a Basys-3 FPGA board.

![Basys-3](https://github.com/khkhiu/Singapore_Polytechnic-FPGA_project/blob/main/img/Basys-3.jpg)

<em>A Basys-3 board</em>

***

<strong>Problem statement</strong>

***
Students are to design a generic Vending machine that will dispense a product of 3 different price points. The block diagram of the Vending machine controller is shown below.

![BlockDiagram](https://github.com/khkhiu/Singapore_Polytechnic-FPGA_project/blob/main/img/BlockDiagram.png)

![FlowChart](https://github.com/khkhiu/Singapore_Polytechnic-FPGA_project/blob/main/img/FlowChart.png)
<em>Vending Machine flow chart</em>

<em>Vending Machine block diagram</em>

The clock comes from the oscillator of the Basys3 board and has a frequency of 100 MHz.DIP switches are used to select the size of the product to purchase, 3 LEDs are used to show which product is to be dispensed when the correct amount of money is inserted. The 7-segment display is used to show the amount of money inserted. The push buttons are used to input the money into the machine as shown Below. Only denomination of $2, $5 and $10 will be accepted by the machine.

![MoneyTable](https://github.com/khkhiu/Singapore_Polytechnic-FPGA_project/blob/main/img/MoneyTable.png)

<em>Money table</em>

<strong>Operations of the vending machine</strong>

<strong>TASK 1</strong>
Upon power up, the 7-segment device should show “00.0” as the amount of money inserted is zero. LEDs 1,2,3 will be blinking to indicate that all 3 items are available.<strong>ALL OTHER LEDs WILL BE TURNED OFF.</strong>

<strong>TASK 2</strong>
The user selects the product by flipping the relevant DIP switches(Dip switches 1,2,3). Once the product is selected, the selected LEDs will stop blinking.<strong> The 3 assigned LEDs will turn OFF. All other LEDs will be ON.</strong>

<strong>TASK 3</strong>
User can insert money by pressing push buttons according to the money table. One press of button indicates one note is inserted to the vending machine. While user is inserting money, the 7-segment device will update and display the current amount of money inserted into the machine. If the amount is equal or higher than the price, the LED of the selected size will blink once times and all other LEDS will be off to indicate dispensing of the product.<strong> Meanwhile, the 7-segment display device will start counting down from 20 to 0.</strong>

<strong>TASK 4A</strong>
After dispensing the product, the vending machine will refund change to the user if any. The amount refunded will be displayed by the 7‐segment display device. A ‘‐’ character will be used to indicate dispensing of change.

For example, if the refund amount is S$2.0, the 7‐segment display should show “‐02.0”.

The refund amount will be displayed until the 3 switches are changed back to LOW to return to the initial state(task 1).

<strong>TASK 4B</strong>
If user would like to cancel a purchase, press on Push Button BTNC (Centre). Once
BTNC is pressed, a full refund will happen and system will go back to initial state(task 1) after all 3 switches are changed back to LOW.

In addition,during COIN state(task 3), user does not press any button within the expiration time of 10 seconds, the system will time out and go to REFUND state(task 4A).

***

<strong>Solution in action</strong>

***
<strong>TASK 1</strong>

[![Task 1](http://img.youtube.com/vi/w3tbH47_ZbM/0.jpg)](http://www.youtube.com/watch?v=w3tbH47_ZbM)

<strong>TASK 2</strong>

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/N_VRto3Au94/0.jpg)](http://www.youtube.com/watch?v=N_VRto3Au94)

<strong>TASK 3</strong>

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/QQ1-BU1P8tY/0.jpg)](http://www.youtube.com/watch?v=QQ1-BU1P8tY)

<strong>TASK 4</strong>

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/kNeVc25HB6w/0.jpg)](http://www.youtube.com/watch?v=kNeVc25HB6w)
