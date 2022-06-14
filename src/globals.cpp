#include "globals.h"
#include "myCMD.h"
#include <stdint.h>


//variabili globali
t_cmd cmd_buffer;  //buffer per il comando
t_led led_buffer;  //buffer per riempire info led
uint8_t power_resolution = 12;  //risoluzione in bit della corrente
t_led leds[NUMERO_LED];
int LedSettlingTime = 1000;
int exp_time = 12000;
int ReadoutTime = 2000;
uint32_t acq_period = 100000;

//PINS
const uint8_t PIN_PWR_12V = 10;      //da connettere al rele
const uint8_t PIN_FRD_LED = 23;      //pwm led far led
const uint8_t PIN_DRD_LED = 22;      //pwm led deep red
const uint8_t PIN_RNG_LED = 19;      //pwm led red-orange
const uint8_t PIN_AMB_LED = 18;      //pwm led amber
const uint8_t PIN_GRN_LED = 15;      //pwm led green
const uint8_t PIN_CYN_LED = 14;      //pwm led cyan
const uint8_t PIN_BLU_LED = 37;      //pwm led blue
const uint8_t PIN_RYL_LED = 36;      //pwm led royal blue
const uint8_t PIN_VLT_LED = 29;      //pwm led violet
const uint8_t PIN_CAMERA = 4;        //to trigger the camera
const uint8_t PIN_CAMERA2 = 3;       //to monitor camera trigger
const uint8_t PIN_START = 24;        //to start acquisition



