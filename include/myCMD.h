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

//accende il LED indicato al valore salvato in leds[].actual_power
void turn_ON_LED(char nome_LED);

//spenge il LED indicato mettendolo a 0
void turn_OFF_LED(char nome_LED);

//setta il LED in base al valore impostato su leds[].actual_power o su leds[].acquisition_power
void set_LED(char nome_LED, int power);

//traduce il nome del led nel pin corrispondente
uint8_t get_led_pin(char nome_LED);

//calcolo potenza led a partire da valore impostato e risoluzione
int power_logic(int power);

//data la lettera del led restituisce l'indice
int led_index(char nome_LED);

//controlla tutti i led (accensione o spengimento)
void set_all_leds(int power);



//trigger sequenza di acquisizione immagini
void acquisition();

//trigger camera 
void takePhoto();


//funzione relative al controllo analogico

//setting led analogico
void set_analog_power(char nome_LED);

//lettura tensione per setting analogico
int read_analog_power(char nome_LED);

//calcolo di power a partire dal valore analogico
int analog_power_logic(int analog_power);



#endif