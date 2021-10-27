#include <Arduino.h>
#include "myCMD.h"
#include "myIO.h"
#include "globals.h"


void setup() {
  serial_setup(9600); 
}

void loop() {
  read_command(&cmd_buffer);
  write_command(&cmd_buffer);
}