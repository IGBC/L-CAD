// Dependancy Injection Layer over wiringPi

#if __has_include (<wiringPi.h>)
#include <wiringPi.h>
#else
    #define FAKEWIRES_IMPLEMENT

    int wiringPiSetup(void);
    int wiringPiSetupGpio(void);
    int wiringPiSetupPhys(void);
    int wiringPiSetupSys(void);
    
    void pinMode(int pin, int mode);
    void pullUpDnControl(int pin, int pud);
    void digitalWrite(int pin, int value);
    void pwmWrite(int pin, int value);
    int digitalRead (int pin);

    #define INPUT 0
    #define OUTPUT 1
    #define PWM_OUTPUT 2
    #define GPIO_CLOCK 3

    #define PUD_OFF 0
    #define PUD_UP 1
    #define PUD_DOWN 2

    #define HIGH 1
    #define LOW 0

#endif
