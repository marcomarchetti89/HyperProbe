#include <stdint.h>
#include "globals.h"

//definizioni comandi
#ifndef MYCMD
#define MYCMD

//funzioni di inizializzazione

//inizializzazione pins
void init_PINS();

//inizializzazione LED
void init_LED();

//inizializza lettura analogica
void init_analog();

//segnale di fine inizializzazione
void end_init();


//funzioni sui led da seriale

//prende il comando dato da seriale e lo inoltra alla funzione che serve
void esegui_comando(t_cmd* command_ptr);

/*in base al valore dato, imposta il led definito con nome_LED 
alla potenza power e segna il valore su leds[].actual_power o 
segna il valore su leds[].acquisition_power*/
void set_LED(char nome_LED, int power);

//traduce il nome del led nel pin corrispondente
uint8_t get_led_pin(char nome_LED);

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

//controlla tutti i led (sempre 0-100)
void set_all_leds(int power);

int led_index(char nome_LED);

#endif