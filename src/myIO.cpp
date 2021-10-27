//definizione funzioni di IO

#include <Arduino.h>
#include "myCMD.h"

void serial_setup(int baud){
    Serial.begin(baud);
}

void read_command(t_cmd* command_ptr){
    while (!Serial.available()){}
    command_ptr->command = (char) Serial.read(); 
    command_ptr->value = Serial.parseInt();
}

