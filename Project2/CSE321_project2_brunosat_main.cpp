/*
Author: Bruno Sato
Date: Fall 2022
Course: CSE 321
Assignment: Project 2 Stage 2

Purpose/Summary:
The purpose of this assignment is to create a 4 digit lock system using a matrix keypad and output through an LCD.

Constraints:
4 digit code = last 4 digits of your person number 
Code entered via matrix keypad 
Everytime a value is entered, an LED lights up 
When 4 values are entered it will lock or unlock 
Lock/unlock mode will display on the LCD 
Must have a response of some kind if the wrong code is entered 
Must run “forever”
Have at least 1 interrupt and ISR
BONUS: Add in a password reset to allow user to restart entering their password at any point
*/
//Files to Include:
#include "mbed.h"
//#include "lcd1602.h"
#include "1802.h"

//References:
//Nucleo Reference Manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

//Global Variables:
InterruptIn push_button(PC_13);             //declaring Interrupts
InterruptIn c1(PC_12,PullDown);
InterruptIn c2(PC_11,PullDown);
InterruptIn c3(PC_10,PullDown);
InterruptIn c4(PC_9,PullDown);

void light_up(void);            //declaring functions
void column1(void);
void column2(void);
void column3(void);
void column4(void);

CSE321_LCD lcd(16,2,LCD_5x10DOTS,PF_0,PF_1);           
//main inputs and outputs:

//Main:
int main(){
    lcd.begin();                            //enabling lcd
    lcd.clear();    
    lcd.setCursor(0,0);
    wait_us(10);
    lcd.print("LOCKED");                    //starting with it locked
    
    //num_1.enable_irq();
    RCC->AHB2ENR |= 0x4;                    //enabling GPIOC clock
    RCC->AHB2ENR |= 0x8;                    //enabling GPIOD clock

    GPIOC->MODER|= 0x10000;                 //enabling pc8 (output for LED)
    GPIOC->MODER&=~(0x20000);
    GPIOC->MODER&=~(0xC000000);             //pc13 (push button) input for testing



    GPIOD->MODER&=~(0x8000);                //PD7 as output for row4
    GPIOD->MODER|= 0x4000;
    
    GPIOD->MODER&=~(0x2000);                //PD6 as output for row 3
    GPIOD->MODER|= 0x1000;

    GPIOD->MODER&=~(0x800);                 //PD5 as output for row 2
    GPIOD->MODER|=0x400;

    GPIOD->MODER&=~(0x200);                 //PD4 as output for row 1
    GPIOD->MODER|= 0x100;               
    
    GPIOC->MODER&=~(0xC0000);               //PC9 input
    GPIOC->MODER&=~(0x300000);             //PC10 input
    GPIOC->MODER&=~(0xC00000);              //PC11 input
    GPIOC->MODER&=~(0x3000000);             //PC 12 input

    
    c1.enable_irq();
    c2.enable_irq();
    c3.enable_irq();
    c4.enable_irq();

        
    c1.rise(&column1);
    c2.rise(&column2);
    c3.rise(&column3);        
    c4.rise(&column4);

    
    while(true){                  
        GPIOD->ODR |= 0x10;                     //PD4 is 1
        wait_us(1000);
        GPIOD->ODR&=~(0x10);                    //and turn off

        GPIOD->ODR |= 0x20;                     //PD5 is 1
        wait_us(1000);
        GPIOD->ODR&=~(0x20);                    //and turn off


        GPIOD->ODR |= 0x40;                     //PD6 is 1
        wait_us(1000);
        GPIOD->ODR&=~(0x40);                    //and turn off


        GPIOD->ODR |= 0x80;                     //PD7 is 1
        wait_us(1000);
        GPIOD->ODR&=~(0x80);                    //and turn off
        
        
    
    }
    
    return 0;
}

//(Helper) Functions:
void column1(void){
    light_up();
}
void column2(void){
    light_up();
}
void column3(void){
    light_up();
}
void column4(void){
    light_up();
}
void light_up(void){
    //every time this function is called via the interrput:
    wait_us(100000);
    GPIOC->ODR|=0x100;          //PC8 is 1
    wait_us(100000);
    GPIOC->ODR&=~(0x100);       //and turns off right after
    wait_us(100000);
}
