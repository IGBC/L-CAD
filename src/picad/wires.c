// Dependency Injection Layer over wiringPi
#include "wires.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef FAKEWIRES_IMPLEMENT
    int wiringPiSetup(void){
        printf("Using Fake GPIO Library\n");
        return 0;
    };
    int wiringPiSetupGpio(void){
        printf("Using Fake GPIO Library\n");
        return 0;
    };
    int wiringPiSetupPhys(void){
        printf("Using Fake GPIO Library\n");        
        return 0;
    };
    int wiringPiSetupSys(void){
        printf("Using Fake GPIO Library\n");
        return 0;
    };
    
    void pinMode(int pin, int mode){
    };
    void pullUpDnControl(int pin, int pud){
    };
    void digitalWrite(int pin, int value){
        // Write only memory anyone?
    };
    void pwmWrite(int pin, int value){
    };
    int digitalRead (int pin) {
        // Here we make up some fake data with a 50% chance of being 1S
        srand(time(NULL));
        return rand()/2;
    }
#endif
