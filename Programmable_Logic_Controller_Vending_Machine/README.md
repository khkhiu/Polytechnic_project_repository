# Singapore Polytechnic-Programmable Logic Controller

***

<strong>Video demonstration</strong>

***
[![Video demonstration](http://img.youtube.com/vi/jhtM8-q5Ibk/0.jpg)](http://www.youtube.com/watch?v=jhtM8-q5Ibk)

***

<strong>Introduction</strong>

***

Programmable logic controller (PLC) are industrial computer systems that are designed to operate reliably in harsh environments. PLC are typically used for task, such as controlling manufacturing processes, machines, robotic devices, or any activity that requires high reliability, ease of programming, and process fault diagnosis.

<strong>Assigned task</strong>

For this project, we were tasked with coming up with an improvement to an existing solution to better address the problem. 

<strong>Issues chosen</strong>

![issue](https://khkhiu.github.io/assets/images/SP-PLC/Slide3.PNG)
<em>On January 3 2022, Singapore eased covid rules for working in office.</em>

![issue](https://khkhiu.github.io/assets/images/SP-PLC/Slide4.PNG)
<em>This means more people dining in at hawker centres and food courts. That many people in close proximity increases the risk of spreading COVID.</em>

![solution](https://khkhiu.github.io/assets/images/SP-PLC/Slide5.PNG)
<em>A way to stem the spread is using ready meal vending machines.</em>

![solution](https://khkhiu.github.io/assets/images/SP-PLC/Slide6.PNG)
<em>However, ready meal containers are quite hot when coming out of a vending machine.</em>

![improvement](https://khkhiu.github.io/assets/images/SP-PLC/Slide7.PNG)
<em>Give customers an option to add an additional container that insulates the heat. This ready meal will be placed in the container to act as an insulating area. For customers who want to use their own container, they can place their container onto a conveyor belt. This convenor will take the container into the machine and will place the ready meal onto the container.</em>

<strong>Proposed solution</strong>

**Note** HMI means Human Machine Interface, which is how a user interacts with a PLC system. For this project the HMI used are a touch screen, a series of push buttons, LED lights, photoelectric sensors and a bi-directional motor.

![HMI](https://khkhiu.github.io/assets/images/SP-PLC/HMI.png)
<em>The HMI that the project was ran on</em>

![Conveyor](https://khkhiu.github.io/assets/images/SP-PLC/Conveyor.png)
<em>Conveyor belt system used in project, which was provided by SP</em>

The following slides will provide a step by step guide on how the vending machine works

![root screen](https://khkhiu.github.io/assets/images/SP-PLC/Slide9.PNG)
<em>Root screen</em>

![screen 1](https://khkhiu.github.io/assets/images/SP-PLC/Slide10.PNG)
<em>Food selection screen</em>

![screen 2](https://khkhiu.github.io/assets/images/SP-PLC/Slide11.PNG)
<em>Container selection screen</em>

![screen 3](https://khkhiu.github.io/assets/images/SP-PLC/Slide12.PNG)
<em>Container insertion screen</em>

![screen 4](https://khkhiu.github.io/assets/images/SP-PLC/Slide13.PNG)
<em>Summary screen</em>

![screen 5](https://khkhiu.github.io/assets/images/SP-PLC/Slide14.PNG)
<em>Preparation screen. TON means 'On Delay Timer'</em>

![screen 6](https://khkhiu.github.io/assets/images/SP-PLC/Slide15.PNG)
<em>Ready screen</em>


<strong>PLC program</strong>

The following images will illustrate how the PLC programme looks like and its operations. 

![Network 1](https://khkhiu.github.io/assets/images/SP-PLC/N1.png)
<em>Used to 'load' the vending machine with food and containers</em>

![Network 2](https://khkhiu.github.io/assets/images/SP-PLC/N2.png)
![Network 2A](https://khkhiu.github.io/assets/images/SP-PLC/N2A.png)
<em>Counts the amount of food and containers left in the machine</em>

![Network 3](https://khkhiu.github.io/assets/images/SP-PLC/N3.png)
<em>Used to undo order and go back one screen</em>

![Network 4](https://khkhiu.github.io/assets/images/SP-PLC/N4.png)
<em>Used to control the summary screen</em>

![Network 5](https://khkhiu.github.io/assets/images/SP-PLC/N5.png)
<em>Used only if user desires to insert own container into machine</em>

![Network 6](https://khkhiu.github.io/assets/images/SP-PLC/N6.png)
<em>Used to signal preparation of food.</em>

![Network 7 & 8](https://khkhiu.github.io/assets/images/SP-PLC/N7_N8.png)
<em>Used to send food out of the vending mahcine and to reset all latches, hence allowing a new order to be enterred</em>

***

<strong>Appendix A - overview of PLC operations</strong>

***

![Appendix 1](https://khkhiu.github.io/assets/images/SP-PLC/A1.png)

![Appendix 2](https://khkhiu.github.io/assets/images/SP-PLC/A2.png)

![Appendix 3](https://khkhiu.github.io/assets/images/SP-PLC/A3.png)

![Appendix 4](https://khkhiu.github.io/assets/images/SP-PLC/A4.png)

![Appendix 5](https://khkhiu.github.io/assets/images/SP-PLC/A5.png)

![Appendix 6](https://khkhiu.github.io/assets/images/SP-PLC/A6.png)

![Appendix 7](https://khkhiu.github.io/assets/images/SP-PLC/A7.png)

![Appendix 8](https://khkhiu.github.io/assets/images/SP-PLC/A8.png)

![Appendix 9](https://khkhiu.github.io/assets/images/SP-PLC/A9.png)

***

<strong>Appendix B - Variables</strong>

***

![Variable 1](https://khkhiu.github.io/assets/images/SP-PLC/V1.PNG)

![Variable 2](https://khkhiu.github.io/assets/images/SP-PLC/V2.PNG)

![Variable 3](https://khkhiu.github.io/assets/images/SP-PLC/V3.PNG)

![Variable 4](https://khkhiu.github.io/assets/images/SP-PLC/V4.PNG)

![Variable 5](https://khkhiu.github.io/assets/images/SP-PLC/V5.PNG)

![Variable 6](https://khkhiu.github.io/assets/images/SP-PLC/V6.PNG)
