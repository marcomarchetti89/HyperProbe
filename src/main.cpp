#include <Arduino.h>
#include "myCMD.h"
#include "myIO.h"

//variabili globali
t_cmd cmd_buffer;

void setup() {
  serial_setup(9600); 
}

void loop() {
  read_command(&cmd_buffer);
  write_command(&cmd_buffer);
}