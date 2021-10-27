//definizione funzioni di IO

#include <Arduino.h>

void serial_setup(int baud){
    Serial.begin(baud);
}