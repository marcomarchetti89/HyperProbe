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
        if (command_ptr->value > 120){
            Serial.println("out of range");
        }
        else if (command_ptr->value > 100 && command_ptr->value <= 120){
            Serial.println("lower the value asap!!");
            set_LED(command_ptr->command, command_ptr->value);
        }
        else{
            set_LED(command_ptr->command, command_ptr->value);
        }
        break;
    case 'a':
        if (command_ptr->value > 120){
            Serial.println("out of range");
        }
        else if (command_ptr->value > 100 && command_ptr->value <= 120){
            Serial.println("lower the value asap!!");
            set_all_leds(command_ptr->value);
        }
        else{
            set_all_leds(command_ptr->value);
        }
        break;
    case 'z':
        analog_ctrl = true;
        Serial.println("controllo analogico attivato");
        break;
    case 'x':
        Serial.println("controllo digitale attivato");
        analog_ctrl = false;
        break;
    default: 
        Serial.println("comando non presente");
        break;
    }
}

void set_LED(char nome_LED, int power){
    analogWrite((int)get_led_pin(nome_LED), power_logic(power));
}

int8_t get_led_pin(char nome_LED){
    for (size_t i = 0; i < NUMERO_LED; i++){
        if (leds[i].letter == nome_LED){
            return leds[i].pin;
        }
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
    
    //accensione alimentazione led
    digitalWriteFast(PIN_PWR_12V, HIGH);
    
    //attacco interrupt per acquisizione
    pinMode(PIN_START, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_START), acquisition, FALLING);

    //inizializzazione led builtin
    pinMode(LED_BUILTIN, OUTPUT);
}

void end_init(){
    //accensione led builtin per fine inizializzazione
    for (size_t i = 1; i < 10; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500/i);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500/i);
    }
}

void acquisition(){  //da scrivere
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

void set_analog_power(char nome_LED){  
    int val = read_analog_power(nome_LED);
    int power = analog_power_logic(val);
    set_LED(nome_LED, power);
}

int read_analog_power(char nome_LED){  
    switch (nome_LED){
    case 'r': 
        return analogRead(ANALOG_POWER_RED_LED);
    case 'g': 
        return analogRead(ANALOG_POWER_GREEN_LED);
    case 'b': 
        return analogRead(ANALOG_POWER_BLUE_LED);
    default: 
        return -1;
    }
}

int analog_power_logic(int analog_power){
    double res = pow(2, analog_power_resolution);
    int power = floor(analog_power * 120 / res);
    return power;
}

void init_LED(){  
    //RED
    leds[RED_INDEX].letter = 'r';
    leds[RED_INDEX].pin = PIN_RED_LED;
    leds[RED_INDEX].analog_pin = ANALOG_POWER_RED_LED;
    leds[RED_INDEX].actual_power = 0;
    leds[RED_INDEX].acquisition_power = 0;
    leds[RED_INDEX].analog_power = 0;

    //GREEN
    leds[GREEN_INDEX].letter = 'g';
    leds[GREEN_INDEX].pin = PIN_GREEN_LED;
    leds[GREEN_INDEX].analog_pin = ANALOG_POWER_GREEN_LED;
    leds[GREEN_INDEX].actual_power = 0;
    leds[GREEN_INDEX].acquisition_power = 0;
    leds[GREEN_INDEX].analog_power = 0;

    //BLUE
    leds[BLUE_INDEX].letter = 'b';
    leds[BLUE_INDEX].pin = PIN_BLUE_LED;
    leds[BLUE_INDEX].analog_pin = ANALOG_POWER_BLUE_LED;
    leds[BLUE_INDEX].actual_power = 0;
    leds[BLUE_INDEX].acquisition_power = 0;
    leds[BLUE_INDEX].analog_power = 0;

    //inizializzo power a 0
    set_all_leds(0);
}

void set_all_leds(int power){ //salvare le cose sulla struct
    for (size_t i = 0; i < NUMERO_LED; i++){
        analogWrite( (int)leds[i].pin, power_logic(power));
    }
}

void init_analog(){
    for (size_t i = 0; i < NUMERO_LED; i++){
        int val = analogRead(leds[i].analog_pin);
        leds[i].analog_power = val;
        Serial.print(leds[i].letter);
        Serial.print(" analog power ");
        Serial.println(val);
    }
    
}
