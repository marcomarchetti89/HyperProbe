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

void write_command(t_cmd* command_ptr){
    Serial.print("lettera: ");
    Serial.print(command_ptr->command);
    Serial.print(" valore: ");
    Serial.println(command_ptr->value);
    if (command_ptr->command == 'r'){
        Serial.print("red LED power = ");
        Serial.println(command_ptr->value);
    }
    else if(command_ptr->command == 'g'){
        Serial.print("green LED power = ");
        Serial.println(command_ptr->value);
    }
    else if(command_ptr->command == 'b'){
        Serial.print("blue LED power = ");
        Serial.println(command_ptr->value);
    }
    else{
        Serial.println("invalid command");
    }

}