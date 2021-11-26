#include "globals.h"
#include "myCMD.h"
#include <stdint.h>


//variabili globali
t_cmd cmd_buffer;  //buffer per il comando
t_led led_buffer;  //buffer per riempire info led
uint8_t power_resolution = 12;  //risoluzione in bit della corrente
t_led leds[NUMERO_LED];
int LedSettlingTime = 10;
int exp_time = 10000;
int ReadoutTime = 1000;

//PINS
const uint8_t PIN_PWR_12V = 10;      //da connettere al rele
const uint8_t PIN_FRD_LED = 23;      //pwm led far led
const uint8_t PIN_DRD_LED = 22;      //pwm led deep red
const uint8_t PIN_DRD_LED = 19;      //pwm led red-orange
const uint8_t PIN_AMB_LED = 18;      //pwm led amber
const uint8_t PIN_GRN_LED = 15;      //pwm led green
const uint8_t PIN_BLU_LED = 14;      //pwm led blue
const uint8_t PIN_RYL_LED = 22;      //pwm led royal blue
const uint8_t PIN_CAMERA = 4;        //to trigger the camera
const uint8_t PIN_START = 23;        //to start acquisition



