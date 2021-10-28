#include <Arduino.h>
#include <stdint.h>
#include "globals.h"
#include "myCMD.h"



//prende il comando dato da seriale e lo inoltra alla funzione che serve
void esegui_comando(t_cmd* command_ptr){
    switch (command_ptr->command){
    case 'r':
    case 'g':
    case 'b':
        set_LED(command_ptr->command, command_ptr->value);
        break;
    default: 
        break;
    }
}

void set_LED(char nome_LED, int power){
    analogWrite((int)get_led_pin(nome_LED), power);
}

int8_t get_led_pin(char nome_LED){
    switch (nome_LED){
    case 'r': return PIN_RED_LED;
    case 'g': return PIN_RED_LED;
    case 'b': return PIN_RED_LED;
    default: return -1;
    }
}

void init_PINS(){
    //inizializzo pin led come output
    pinMode(PIN_RED_LED, OUTPUT );
    pinMode(PIN_GREEN_LED, OUTPUT );
    pinMode(PIN_BLUE_LED, OUTPUT );
    
    //set frequenza del pwm
    analogWriteFrequency(PIN_RED_LED, PWM_frequency); 
    analogWriteFrequency(PIN_GREEN_LED, PWM_frequency); 
    analogWriteFrequency(PIN_BLUE_LED, PWM_frequency); 
    
    //spengo led (logica negata)
    analogWrite(PIN_RED_LED, 255);
    analogWrite(PIN_GREEN_LED, 255);
    analogWrite(PIN_BLUE_LED, 255);
    
    //accensione alimentazione led
    digitalWriteFast(PIN_PWR_12V, HIGH);
    
    //attacco interrupt per acquisizione
    pinMode(PIN_START, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_START), acquisition, FALLING);

    //accensione led builtin per fine inizializzazione pin
    pinMode(LED_BUILTIN, OUTPUT);
    for (size_t i = 1; i < 10; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500/i);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500/i);
    }
    
}

void acquisition(){}


