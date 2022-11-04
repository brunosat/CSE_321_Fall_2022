-------------------
About
-------------------
Project Description: 
Contribitor List:
Bruno Sato

--------------------
Features
--------------------

--------------------
Required Materials
--------------------
-Nucleo L4R5ZI

--------------------
Resources and References
Nucleo user manual: https://www.st.com/resource/en/user_manual/dm00368330-stm32-nucleo-144-boards-mb1312-stmicroelectronics.pdf
--------------------



--------------------
Getting Started
--------------------
This section will describe the general setup

--------------------
cse321_fall_22_ProvidedCode.cpp:
--------------------
 
The purpose of this project is to create a thread to drive an LED to have an on time of 2000ms and off time 500ms.


----------
Things Declared
----------
Variables, functions, objects, and APIs are used. 

int frodo=0
int parade=0

----------
API and Built In Elements Used
----------
Thread
DigitalOut
InterrputIn
----------
Custom Functions
----------

timer:
	Determines the timing for the LED to be on and off
	Inputs:
		None
	Globally referenced variables used: frodo

flipflop:
	Sets parade to 1
	Inputs: None
	Globally referenced variables used: parade

unicorn:
	Alternates frodo between 1 and 0
	Inputs: None
	Globally referenced variables used: frodo, parade
	


