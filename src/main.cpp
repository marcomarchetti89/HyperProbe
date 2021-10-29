#include <Arduino.h>
#include "globals.h"
#include "myCMD.h"
#include "myIO.h"



void setup() {
  serial_setup(9600); 
  init_PINS();
  init_LED();
}

void loop() {
  read_command(&cmd_buffer);
  write_command(&cmd_buffer);

  esegui_comando(&cmd_buffer);
  if (analog_ctrl == true){
    set_analog_power('r');
    set_analog_power('g');
    set_analog_power('b');
  }
}