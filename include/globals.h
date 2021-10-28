#include "myCMD.h"
#include <stdint.h>


#ifndef GLOBALS
#define GLOBALS

#define PWM_frequency 200
//variabili globali
extern t_cmd cmd_buffer;  //buffer per il comando
extern uint8_t current_resolution;  //risoluzione in bit della corrente


//PINS
extern const uint8_t PIN_PWR_12V;//da connettere al rele
extern const uint8_t PIN_RED_LED;       // brown    to PWM red        
extern const uint8_t PIN_GREEN_LED;       // pink     to PWM green  
extern const uint8_t PIN_BLUE_LED;       //          to PWM white
extern const uint8_t PIN_CAMERA;        //          to the camera
extern const uint8_t PIN_START;        // yellow   to the button



#endif