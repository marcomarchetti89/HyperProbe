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



