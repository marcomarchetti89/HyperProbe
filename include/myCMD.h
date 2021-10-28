#include <stdint.h>


//definizioni comandi
#ifndef MYCMD
#define MYCMD

//definizione del tipo comando = lettera + intero
typedef struct {
    char command;
    int value;
}t_cmd;

//analizza il comando in ingresso 
void esegui_comando(t_cmd* command_ptr);

//imposta il led definito con nome_LED alla potenza power
void set_LED(char nome_LED, int power);

//traduce il nome del led nel pin corrispondente
int8_t get_led_pin(char nome_LED);

#endif