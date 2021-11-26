#include <stdint.h>

#ifndef GLOBALS
#define GLOBALS

#define PWM_frequency 2000

/*lo definisco costante perché poi crerò un array di led
e se è variabile devo mallocare la memoria*/
#define NUMERO_LED 7
#define FRD_INDEX 0
#define DRD_INDEX 1
#define RNG_INDEX 2
#define AMB_INDEX 3
#define GRN_INDEX 4
#define BLU_INDEX 5
#define RYL_INDEX 6

extern const uint8_t PIN_FRD_LED;      //pwm led far led
extern const uint8_t PIN_DRD_LED;      //pwm led deep red
extern const uint8_t PIN_RNG_LED;      //pwm led red-orange
extern const uint8_t PIN_AMB_LED;      //pwm led amber
extern const uint8_t PIN_GRN_LED;      //pwm led green
extern const uint8_t PIN_BLU_LED;      //pwm led blue
extern const uint8_t PIN_RYL_LED;      //pwm led royal blue


//definizione del tipo comando = lettera + intero
typedef struct {
    char command;
    int value;
}t_cmd;

//definizione dell'oggetto led
typedef struct {
    char letter;
    bool state;
    uint8_t pin;
    int actual_power;
    int acquisition_power;
}t_led;

//variabili globali
extern t_cmd cmd_buffer;  //buffer per il comando
extern uint8_t power_resolution;  //risoluzione in bit della corrente
extern t_led leds[]; //vettore dei led
extern int LedSettlingTime;
extern int exp_time;
extern int ReadoutTime;

//PINS
extern const uint8_t PIN_PWR_12V;   //da connettere al rele da montere al posto dell'interruttore
extern const uint8_t PIN_FRD_LED;      //pwm led far led
extern const uint8_t PIN_DRD_LED;      //pwm led deep red
extern const uint8_t PIN_RNG_LED;      //pwm led red-orange
extern const uint8_t PIN_AMB_LED;      //pwm led amber
extern const uint8_t PIN_GRN_LED;      //pwm led green
extern const uint8_t PIN_BLU_LED;      //pwm led blue
extern const uint8_t PIN_RYL_LED;      //pwm led royal blue
extern const uint8_t PIN_CAMERA;    //pin trigger camera, al momento libero      
extern const uint8_t PIN_START;     //pin interruttore fisico a filo

#endif