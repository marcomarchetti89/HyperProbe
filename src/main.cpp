#include <Arduino.h>
#include "globals.h"
#include "myCMD.h"
#include "myIO.h"



void setup() {
  serial_setup(115200); 
  init_PINS();
  init_LED();
  end_init();
}

void loop() {
  read_command(&cmd_buffer);
    
}