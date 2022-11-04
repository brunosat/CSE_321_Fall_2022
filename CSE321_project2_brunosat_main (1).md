-------------------
About
-------------------
Project Description: This project requires a lock/unlock functionality using a 4 digit code, using and LCD to output information and a matrix keypad to input
Contribitor List: Bruno Sato


--------------------
Features
--------------------
An LED will blink every time a button is pressed in the keypad.
An LCD will display "LOCKED" to represent the system is locked.

--------------------
Required Materials
--------------------
-Nucleo L4R5ZI
-LCD
-LED
-Resistors
-Wires


--------------------
Resources and References
--------------------
Nucleo Reference Manual:
https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

Libraries:
mbed.h
1802.h                    
1802.cpp    

--------------------
Getting Started
-------------------- 

----------
API and Built In Elements Used
----------
LCD built-in functions based on the 1802.cpp and 1802.h files:
-<lcdObject>.begin()
-<lcdObject>.clear()
-<lcdObject>.setCursor(x,y)
-<lcdObject>.print("string")

InterruptIn

----------
Custom Functions
----------
light_up():
    lights up an external LED momentarily when called


