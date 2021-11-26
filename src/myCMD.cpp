#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "globals.h"
#include "myCMD.h"


void init_PINS(){
    //inizializzo pin led come output
    pinMode(PIN_FRD_LED, OUTPUT );
    pinMode(PIN_DRD_LED, OUTPUT );
    pinMode(PIN_RNG_LED, OUTPUT );
    pinMode(PIN_AMB_LED, OUTPUT );
    pinMode(PIN_GRN_LED, OUTPUT );
    pinMode(PIN_BLU_LED, OUTPUT );
    pinMode(PIN_RYL_LED, OUTPUT );
    
    //set frequenza del pwm
    analogWriteFrequency(PIN_FRD_LED, PWM_frequency); 
    analogWriteFrequency(PIN_DRD_LED, PWM_frequency); 
    analogWriteFrequency(PIN_RNG_LED, PWM_frequency); 
    analogWriteFrequency(PIN_AMB_LED, PWM_frequency); 
    analogWriteFrequency(PIN_GRN_LED, PWM_frequency); 
    analogWriteFrequency(PIN_BLU_LED, PWM_frequency); 
    analogWriteFrequency(PIN_RYL_LED, PWM_frequency); 

    //set frequenza del pwm
    analogWriteResolution(power_resolution); 

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
    //far red
    leds[FRD_INDEX].letter = 'q';
    leds[FRD_INDEX].state = false;
    leds[FRD_INDEX].pin = PIN_FRD_LED;
    leds[FRD_INDEX].actual_power = 0;
    leds[FRD_INDEX].acquisition_power = 0;

    //deep red
    leds[DRD_INDEX].letter = 'w';
    leds[DRD_INDEX].state = false;
    leds[DRD_INDEX].pin = PIN_DRD_LED;
    leds[DRD_INDEX].actual_power = 0;
    leds[DRD_INDEX].acquisition_power = 0;

    //red-orange
    leds[RNG_INDEX].letter = 'e';
    leds[RNG_INDEX].state = false;
    leds[RNG_INDEX].pin = PIN_RNG_LED;
    leds[RNG_INDEX].actual_power = 0;
    leds[RNG_INDEX].acquisition_power = 0;

    //amber
    leds[AMB_INDEX].letter = 'r';
    leds[AMB_INDEX].state = false;
    leds[AMB_INDEX].pin = PIN_RNG_LED;
    leds[AMB_INDEX].actual_power = 0;
    leds[AMB_INDEX].acquisition_power = 0;

    //green
    leds[GRN_INDEX].letter = 't';
    leds[GRN_INDEX].state = false;
    leds[GRN_INDEX].pin = PIN_RNG_LED;
    leds[GRN_INDEX].actual_power = 0;
    leds[GRN_INDEX].acquisition_power = 0;

    //blue
    leds[BLU_INDEX].letter = 'y';
    leds[BLU_INDEX].state = false;
    leds[BLU_INDEX].pin = PIN_RNG_LED;
    leds[BLU_INDEX].actual_power = 0;
    leds[BLU_INDEX].acquisition_power = 0;

    //royal blue
    leds[RYL_INDEX].letter = 'u';
    leds[RYL_INDEX].state = false;
    leds[RYL_INDEX].pin = PIN_RNG_LED;
    leds[RYL_INDEX].actual_power = 0;
    leds[RYL_INDEX].acquisition_power = 0;
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
    case 'q':
    case 'w':
    case 'e':
    case 'r':
    case 't':
    case 'y':
    case 'u':
        set_LED(command_ptr->command, command_ptr->value);
        break;
    case 'a':
        set_all_leds(command_ptr->value);
        break;
    case 's':
        exp_time = command_ptr->value;
        break;
    case 'd':
        acquisition();
        break;
    case 'd':
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
    case 'q':
        return FRD_INDEX;
        break;
    case 'w':
        return DRD_INDEX;
        break;
    case 'e':
        return RNG_INDEX;
        break;
    case 'r':
        return AMB_INDEX;
        break;
    case 't':
        return GRN_INDEX;
        break;
    case 'y':
        return BLU_INDEX;
        break;
    case 'u':
        return RYL_INDEX;
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



