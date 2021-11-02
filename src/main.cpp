#include <Arduino.h>
#include "globals.h"
#include "myCMD.h"
#include "myIO.h"



void setup() {
  serial_setup(9600); 
  init_PINS();
  init_LED();
  init_analog();
  end_init();
}

void loop() {
  read_command(&cmd_buffer);
  if (analog_ctrl == true){
    for (size_t i = 0; i < NUMERO_LED; i++){
        set_analog_power(leds[i].letter);
    }
    //delay(1000);
  }
}