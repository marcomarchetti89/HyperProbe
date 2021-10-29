#include <stdint.h>

#ifndef GLOBALS
#define GLOBALS

#define PWM_frequency 200

/*lo definisco costante perché poi crerò un array di led
e se è variabile devo mallocare la memoria*/
#define NUMERO_LED 3 
#define RED_INDEX 0
#define GREEN_INDEX 1
#define BLUE_INDEX 2

//definizione del tipo comando = lettera + intero
typedef struct {
    char command;
    int value;
}t_cmd;

//definizione dell'oggetto led
typedef struct {
    char letter;
    uint8_t pin;
    int actual_power;
    int acquisition_power;
    int analog_power;
}t_led;

//variabili globali
extern t_cmd cmd_buffer;  //buffer per il comando
extern uint8_t power_resolution;  //risoluzione in bit della corrente
extern uint8_t analog_power_resolution;  //risoluzione in bit della corrente
extern bool analog_ctrl;
extern t_led leds[]; //

//PINS
extern const uint8_t PIN_PWR_12V;//da connettere al rele
extern const uint8_t PIN_RED_LED;       // brown    to PWM red        
extern const uint8_t PIN_GREEN_LED;       // pink     to PWM green  
extern const uint8_t PIN_BLUE_LED;       //          to PWM white
extern const uint8_t PIN_CAMERA;        //          to the camera
extern const uint8_t PIN_START;        // yellow   to the button
extern const uint8_t ANALOG_POWER_RED_LED;       // brown    to PWM red        
extern const uint8_t ANALOG_POWER_GREEN_LED;       // pink     to PWM green  
extern const uint8_t ANALOG_POWER_BLUE_LED;

#endif