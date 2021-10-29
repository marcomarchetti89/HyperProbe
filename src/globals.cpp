#include "globals.h"
#include "myCMD.h"
#include <stdint.h>


//variabili globali
t_cmd cmd_buffer;  //buffer per il comando
t_led led_buffer;  //buffer per riempire info led
uint8_t power_resolution = 12;  //risoluzione in bit della corrente
uint8_t analog_power_resolution = 12;  //risoluzione in bit della lettura analogica
bool analog_ctrl = false; 
t_led leds[NUMERO_LED];

//PINS
const uint8_t PIN_PWR_12V = 10;      //da connettere al rele
const uint8_t PIN_RED_LED = 19;      //pwm led rosso     
const uint8_t PIN_GREEN_LED = 14;    //pwm led verde
const uint8_t PIN_BLUE_LED = 37;     //pwm led blu
const uint8_t PIN_CAMERA = 4;        //to trigger the camera
const uint8_t PIN_START = 23;        //to start acquisition
const uint8_t ANALOG_POWER_RED_LED = 21;      //to set analog reference red led 
const uint8_t ANALOG_POWER_GREEN_LED = 17;    //to set analog reference green led 
const uint8_t ANALOG_POWER_BLUE_LED = 15;     //to set analog reference blue led 

//
