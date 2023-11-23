#ifndef SLAVECONTROL_HEXAPOD_SPI_DRIVER_H
#define SLAVECONTROL_HEXAPOD_SPI_DRIVER_H

#include <unistd.h>
#include "spi.h"


#define MESSAGE_MAX_LENGTH 255

typedef enum{
    ALL_SERVO,
    ONE_LEG,
    ONE_SERVO,
    READ_ADC,
    OTHER
} TYPE;

typedef struct{
    uint8_t pData[MESSAGE_MAX_LENGTH];
    uint8_t dataLength;
} RAW_SPI_Message;

// Blocking functions
void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);
void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);

#endif //SLAVECONTROL_HEXAPOD_SPI_DRIVER_H
