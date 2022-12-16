/*
Author: Bruno Sato
Date: Fall 2022
Course: CSE 321
Assignment: Project 3

Purpose/Summary: The goal of this project is to activate a fire alarm properly and efficiently, giving the user feedback 
on when the fire alarm is about to be activated. To accomplish this, the project will have its’ behavior based on a 
regular fire alarm behavior. A form of indicator/warning/alert will be sent to the user whenever the temperature* reaches 
a certain “high, but not worrisome,” temperature*. And when the alarm is activated after it reaches a temperature* 
considered dangerous, signals will be outputted, similarly to what a fire alarm would do. 


Constraints:
*For this project’s purposes, the basis of the sensor will be humidity.

*/
//Files to Include:
#include "mbed.h"
//LCD library
#include "1802.h"
//DHT11 library
#include "DHT.h"

//References:
//Nucleo Reference Manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

DHT11 dht(PD_4);
CSE321_LCD lcd(16,2,LCD_5x10DOTS,PF_0,PF_1);          //building DHT and LCD objects

void led_blink(void);
void led_off(void);
void led_on(void);
void turn_on(void);                                 //declaring functions
void turn_off(void);
void alarm_on(void);
void alarm_off(void);

int enable=0;                                       //global variable to determine enable in the system

InterruptIn key2(PC_10, PullDown);
InterruptIn key1(PC_11, PullDown);                  //building Interrupts
/*EventQueue e(32* EVENTS_EVENT_SIZE);
Thread t1;*/

int main(){
    lcd.begin();
    lcd.setCursor(0,0);                         //initializing LCD

    /*t1.start(callback(&e, &EventQueue::dispatch_forever));
    i1.enable_irq();


    i1.rise(e.event(demoPrint));
    e.dispatch_forever();*/
    
    key2.enable_irq();
    key1.enable_irq();                      //initializing Interrupts

    RCC->AHB2ENR |= 0x8;                    //initializing GPIOD clock
    RCC->AHB2ENR |= 0x4;                    //Initializing GPIOC clock

    GPIOC->MODER |= 0x10000;                 //GPIOC pin 8 as output
    GPIOC->MODER &=~(0x20000);

    GPIOC->MODER &=~(0xf00000);              //GPIOC pin 10 and 11 as inputs

    GPIOC->MODER |= 0x1000000;              //GPIOC pin 12 as output 
    GPIOC->MODER &=~(0x2000000);


    GPIOC->ODR |= 0x1000;                   //GPIOC pin 12 is 1 (for Matrix keypad)

    GPIOD->MODER&=~(0x300);                  //GPIOD pin 4 as input
    GPIOD->MODER|= 0x4000;
    GPIOD->MODER&=~(0x8000);                //GPIOD pin 7 as output

    key1.rise(&turn_on);
    key2.rise(&turn_off);

    while(true){                        //runs forever
    
    while(enable==0){
        key1.rise(&turn_on);
        lcd.setCursor(0, 0);
        lcd.print("System Off");
        wait_us(500000);                //if the system is off, buzzer and LED are off, LCD will print acoordingly
        led_off();
        alarm_off();
        lcd.clear();
    }
    while(enable==1){
        key2.rise(&turn_off);
        lcd.setCursor(0, 0);
        lcd.print("System On");     //if system is on, LCD will print acoordingly
        dht.read();

        if(dht.getHumidity()<40){
            lcd.setCursor(0,1);
            lcd.print("under 40%");
        }else if(dht.getHumidity()>=40 && dht.getHumidity()<45){
            lcd.setCursor(0,1);
            lcd.print("40%");
        }else if(dht.getHumidity()>=45 && dht.getHumidity()<50){        //printing DHT measured humidity
            lcd.setCursor(0,1);
            lcd.print("45%");
            led_off();
            alarm_off();
        }else if(dht.getHumidity()>=50 && dht.getHumidity()<60){
            lcd.setCursor(0,1);
            lcd.print("55%");
            led_blink();                            //if humidity is above 50%, LED blinks
            alarm_off();
        }else if(dht.getHumidity()>=60){
            lcd.setCursor(0,1);
            lcd.print("FIRE");
            led_on();                               //if humidity is above 60%, alarm goes off (buzzer and LED are on)
            alarm_on();
        }
        wait_us(500000);
        lcd.clear();
    }
    }
    
}
void led_blink(void){
    //wait_us(500000);
    GPIOC->ODR|= 0x100;             //GPIOC pin 8 is 1, for LED
    wait_us(500000);        
    GPIOC->ODR&=~(0x100);           //and turn off after 1 sec
}
void led_off(void){
    wait_us(100000);
    GPIOC->ODR&=~(0x100);           //GPIOC pin 8 is 0, for LED
}
void led_on(void){
    wait_us(100000);
    GPIOC->ODR|= 0x100;             //GPIOC pin 8 is 1, for LED
}

void turn_on(void){
    wait_us(100000);
    enable=1;
    wait_us(100000);
}
void turn_off(void){
    wait_us(100000);
    enable=0;
    wait_us(100000);
}

void alarm_on(void){
    wait_us(100000);
    GPIOD->ODR|=0x80;       //GPIOD pin 7 is 1, for buzzer
    wait_us(100000);
}
void alarm_off(void){
    wait_us(100000);
    GPIOD->ODR&=~(0x80);    //GPIOD pin 7 is 0, for buzzer
    wait_us(100000);
}
