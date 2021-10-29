#include <stdint.h>
#include <string>
using namespace std;


//definizioni comandi
#ifndef MYCMD
#define MYCMD

//definizione del tipo comando = lettera + intero
typedef struct {
    char command;
    int value;
}t_cmd;

//definizione dell'oggetto led
typedef struct {
    char letter;
    int actual_power;
    int acquisition_power;
    int analog_power;
}t_led;

//analizza il comando in ingresso 
void esegui_comando(t_cmd* command_ptr);

//imposta il led definito con nome_LED alla potenza power
void set_LED(char nome_LED, int power);

//traduce il nome del led nel pin corrispondente
int8_t get_led_pin(char nome_LED);

//inizializzazione pins
void init_PINS();

//trigger sequenza di acquisizione immagini
void acquisition();

//calcolo potenza led a partire da valore impostato e risoluzione
int power_logic(int power);

//setting led analogico
void set_analog_power(char nome_LED);

//lettura tensione per setting analogico
int read_analog_power(char nome_LED);

//calcolo di power a partire dal valore analogico
int analog_power_logic(int analog_power);

//inizializzazione LED
void init_LED();

#endif