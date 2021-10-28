#include "myCMD.h"
#include <stdint.h>


#ifndef GLOBALS
#define GLOBALS

//variabili globali
t_cmd cmd_buffer;

//PINS
const uint8_t PIN_PWR_12V = 10;//da connettere al rele
const uint8_t PIN_RED_LED   = 19;       // brown    to PWM red        
const uint8_t PIN_GREEN_LED = 14;       // pink     to PWM green  
const uint8_t PIN_BLUE_LED = 37;       //          to PWM white
const uint8_t PIN_CAMERA    = 4;        //          to the camera
const uint8_t PIN_START     = 23;        // yellow   to the button



#endif