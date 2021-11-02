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
    uint8_t analog_pin;
    int actual_power;
    int acquisition_power;
    int analog_power;
}t_led;

//variabili globali
extern t_cmd cmd_buffer;  //buffer per il comando
extern uint8_t power_resolution;  //risoluzione in bit della corrente
extern uint8_t analog_power_resolution;  //risoluzione in bit della corrente settata analogicamente
extern bool analog_ctrl; //controllo del setting analogico/digitale
extern t_led leds[]; //vettore dei led

//PINS
extern const uint8_t PIN_PWR_12V;   //da connettere al rele da montere al posto dell'interruttore
extern const uint8_t PIN_RED_LED;   //pin pwm led rosso       
extern const uint8_t PIN_GREEN_LED; //pin pwm led verde       
extern const uint8_t PIN_BLUE_LED;  //pin pwm led blu
extern const uint8_t PIN_CAMERA;    //pin trigger camera, al momento libero      
extern const uint8_t PIN_START;     //pin interruttore fisico a filo
extern const uint8_t ANALOG_POWER_RED_LED;   //AI su partitore relativo a led rosso 
extern const uint8_t ANALOG_POWER_GREEN_LED; //AI su partitore relativo a led verde
extern const uint8_t ANALOG_POWER_BLUE_LED;  //AI su partitore relativo a led blu

#endif