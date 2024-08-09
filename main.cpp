/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


DigitalOut myled(LED1);
UnbufferedSerial pc(USBTX, USBRX); // Changed to UnbufferedSerial
UnbufferedSerial dev(PA_0, PA_1); // Changed pins
//As Per https://docs.neqto.com/docs/en/stm32-discovery-series/hardware/about-stm32-discovery-kit-b-l4s5i-iot01a

void dev_recv() {
    char c;
    while (dev.readable()) {
        dev.read(&c, 1); // Read from dev serial
        pc.write(&c, 1); // Write to pc serial
    }
}

void pc_recv() {
    char c;
    while (pc.readable()) {
        pc.read(&c, 1); // Read from pc serial
        dev.write(&c, 1); // Write to dev serial
    }
}

int main() {
    pc.baud(9600); // set baud rates 
    dev.baud(9600);

    pc.attach(callback(pc_recv), SerialBase::RxIrq); // for pc
    dev.attach(callback(dev_recv), SerialBase::RxIrq); // for dev

    pc.write("Hello!! \r\n", 10); // send hello to serial

   
    while (1) {
        myled = 1;
        wait_us(1000); // Updated delay 
        myled = 0;
        wait_us(1000); // Updated delay 

    }
    }