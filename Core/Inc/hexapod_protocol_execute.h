#ifndef HEXAPOD_PROTOCOL_EXECUTE_HPP
#define HEXAPOD_PROTOCOL_EXECUTE_HPP

#include <unistd.h>
#include "adc.h"

/**
 * @brief Interprets the content of a byte array representing data for one servo motor
 *
 * @param data: Pointer to the data array representing control information regarding one servo
 */
void interpretOneServoData(const uint8_t* data);

void executeOneServo(const uint8_t* data);

void executeOneLeg(const uint8_t* data);

#endif //HEXAPOD_PROTOCOL_EXECUTE_HPP