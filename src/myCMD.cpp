#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "globals.h"
#include "myCMD.h"


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
    pinMode(PIN_CAMERA, OUTPUT);
}

void init_LED(){  
    //RED
    leds[RED_INDEX].letter = 'r';
    leds[RED_INDEX].state = false;
    leds[RED_INDEX].pin = PIN_RED_LED;
    leds[RED_INDEX].analog_pin = ANALOG_POWER_RED_LED;
    leds[RED_INDEX].actual_power = 0;
    leds[RED_INDEX].acquisition_power = 0;
    leds[RED_INDEX].analog_power = 0;

    //GREEN
    leds[GREEN_INDEX].letter = 'g';
    leds[GREEN_INDEX].state = false;
    leds[GREEN_INDEX].pin = PIN_GREEN_LED;
    leds[GREEN_INDEX].analog_pin = ANALOG_POWER_GREEN_LED;
    leds[GREEN_INDEX].actual_power = 0;
    leds[GREEN_INDEX].acquisition_power = 0;
    leds[GREEN_INDEX].analog_power = 0;

    //BLUE
    leds[BLUE_INDEX].letter = 'b';
    leds[BLUE_INDEX].state = false;
    leds[BLUE_INDEX].pin = PIN_BLUE_LED;
    leds[BLUE_INDEX].analog_pin = ANALOG_POWER_BLUE_LED;
    leds[BLUE_INDEX].actual_power = 0;
    leds[BLUE_INDEX].acquisition_power = 0;
    leds[BLUE_INDEX].analog_power = 0;

    //inizializzo power a 0
    set_all_leds(0);
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


void esegui_comando(t_cmd* command_ptr){
    switch (command_ptr->command){
    case 'r':
    case 'g':
    case 'b':
        set_LED(command_ptr->command, command_ptr->value);
        break;
    case 'a':
        set_all_leds(command_ptr->value);
        break;
    case 'z':
        analog_ctrl = true;
        update_leds();
        for (size_t i = 0; i < NUMERO_LED; i++){
            Serial.print(leds[i].letter);
            Serial.print(leds[i].analog_power + 100);
        }
        break;
    case 'x':
        analog_ctrl = false;
        update_leds();
        break;
    case 'e':
        exp_time = command_ptr->value;
        break;
    case 't':
        acquisition();
        break;
    case 'p':
        digitalWrite(PIN_CAMERA, HIGH);
        analogWrite(PIN_BLUE_LED, power_logic(100));
        delayMicroseconds(command_ptr->value);
        analogWrite(PIN_BLUE_LED, power_logic(60));
        delayMicroseconds(command_ptr->value);
        analogWrite(PIN_BLUE_LED, power_logic(30));
        delayMicroseconds(command_ptr->value);
        analogWrite(PIN_BLUE_LED, power_logic(15));
        delayMicroseconds(command_ptr->value);
        digitalWrite(PIN_CAMERA, LOW);
        delayMicroseconds(1);
        analogWrite(PIN_BLUE_LED, power_logic(0));
        break;
    default: 
        Serial.println("comando non presente");
        break;
    }
}

void turn_ON_LED(char nome_LED){
    leds[led_index(nome_LED)].state = true;
    if (analog_ctrl == false){
        analogWrite((int)get_led_pin(nome_LED), power_logic(leds[led_index(nome_LED)].actual_power));
    }
    else{
        analogWrite((int)get_led_pin(nome_LED), power_logic(leds[led_index(nome_LED)].analog_power));
    }
    
}

void turn_OFF_LED(char nome_LED){
    leds[led_index(nome_LED)].state = false;
    analogWrite((int)get_led_pin(nome_LED), power_logic(0));
}

void set_LED(char nome_LED, int power){
    if (power == 0){
        turn_OFF_LED(nome_LED);
    }
    if (power > 0 && power < 120){
        leds[led_index(nome_LED)].actual_power = power;
    }
    else if(power >= 120 && power < 240){
        leds[led_index(nome_LED)].acquisition_power = power-120;
    }
    else if(power == 240){
        turn_ON_LED(nome_LED);
    }
    else{
    }   
}

uint8_t get_led_pin(char nome_LED){
    for (size_t i = 0; i < NUMERO_LED; i++){
        if (leds[i].letter == nome_LED){
            return leds[i].pin;
        }
    }
}

int power_logic(int power){
    double res = pow(2, power_resolution);
    int pwm_power = floor(res - power * res / 120);
    return pwm_power;
}

int led_index(char nome_LED){
    switch (nome_LED){
    case 'r':
        return RED_INDEX;
        break;
    case 'g':
        return GREEN_INDEX;
        break;
    case 'b':
        return BLUE_INDEX;
        break;
    default:
        return -1;
        break;
    }
}

void set_all_leds(int power){ 
    if (power == 0){
        for (size_t i = 0; i < NUMERO_LED; i++){
            turn_OFF_LED(leds[i].letter);
        }
    }
    else{
        for (size_t i = 0; i < NUMERO_LED; i++){
            turn_ON_LED(leds[i].letter);
        }
    }
}

void update_leds(){
    for (size_t i = 0; i < NUMERO_LED; i++){
        if (leds[i].state == true){
            turn_ON_LED(leds[i].letter);
        }
        else{
            turn_OFF_LED(leds[i].letter);
        }
    }
}




void acquisition(){
    set_all_leds(0);
    delayMicroseconds(1000000);
    for (size_t i = 0; i < NUMERO_LED; i++){
            analogWrite( (int)leds[i].pin, power_logic(leds[i].actual_power));
            delayMicroseconds(LedSettlingTime);
            takePhoto();
            analogWrite( (int)leds[i].pin, power_logic(0));
            delayMicroseconds(ReadoutTime);
    }
}

void takePhoto(){
    digitalWriteFast(PIN_CAMERA, HIGH);
    delayMicroseconds(exp_time);
    digitalWriteFast(PIN_CAMERA, LOW);
}



