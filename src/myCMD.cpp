#include <Arduino.h>
#include <stdint.h>
#include <math.h>
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
    analogWrite((int)get_led_pin(nome_LED), power_logic(power));
}

int8_t get_led_pin(char nome_LED){
    switch (nome_LED){
    case 'r': return PIN_RED_LED;
    case 'g': return PIN_GREEN_LED;
    case 'b': return PIN_BLUE_LED;
    default: return -1;
    }
}

int power_logic(int power){
    double res = pow(2, power_resolution);
    int pwm_power = floor(res - power * res / 120);
    Serial.println(pwm_power);
    return pwm_power;
}

void init_PINS(){
    //inizializzo pin led come output
    pinMode(PIN_RED_LED, OUTPUT );
    pinMode(PIN_GREEN_LED, OUTPUT );
    pinMode(PIN_BLUE_LED, OUTPUT );
    
    //inizializzo pin di lettura analogica
    pinMode(ANALOG_POWER_RED_LED, INPUT );
    pinMode(ANALOG_POWER_GREEN_LED, INPUT );
    pinMode(ANALOG_POWER_BLUE_LED, INPUT );

    //set frequenza del pwm
    analogWriteFrequency(PIN_RED_LED, PWM_frequency); 
    analogWriteFrequency(PIN_GREEN_LED, PWM_frequency); 
    analogWriteFrequency(PIN_BLUE_LED, PWM_frequency); 
    
    //set frequenza del pwm
    analogWriteResolution(power_resolution); 

    //set risoluzione della tensione analogica
    analogReadResolution(analog_power_resolution);

    //spengo led (logica negata)
    set_LED('r', 0);
    set_LED('g', 0);
    set_LED('b', 0);
    
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

void acquisition(){
    /*detachInterrupt(digitalPinToInterrupt(START));
    set_LED('r', )
    delayMicroseconds(LedSettlingTime);
    takePhoto();
    analogWrite(RED_LED, 255);
    delayMicroseconds(ReadoutTime);
    val = round(pow(2,PowBit)*GreenPow/100);
    analogWrite(GREEN_LED, 255-val);
    Serial.println(val);
    delayMicroseconds(LedSettlingTime);
    takePhoto();
    analogWrite(GREEN_LED, 255);
    delayMicroseconds(ReadoutTime);
    Serial.println("done");
    //delayMicroseconds(1000000);
    attachInterrupt(digitalPinToInterrupt(START), acquisition, FALLING);*/
}



