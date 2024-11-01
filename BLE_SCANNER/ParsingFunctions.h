#ifndef PARSINGFUNCTIONS_H
#define PARSINGFUNCTIONS_H

#include <Arduino.h>

void parseMokoS03D(uint8_t* payload, size_t payloadLength);
void parseMokoS01P(uint8_t* payload, size_t payloadLength);
void parseMokoH4Pro(uint8_t* payload, size_t payloadLength);

#endif // PARSINGFUNCTIONS_H
