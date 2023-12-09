#ifndef STM32F446_CONTROL_HEXAPOD_SPI_DRIVER_H
#define STM32F446_CONTROL_HEXAPOD_SPI_DRIVER_H

#include <unistd.h>
#include "spi.h"


// Message lengths
#define MESSAGE_MAX_LEN         255
#define ALL_SERVO_TYPE_LEN      37
#define ONE_LEG_TYPE_LEN        8
#define ONE_SERVO_LEN           6
// TODO Define lengths of other types of frames when their description will be available


typedef enum{
    ALL_SERVO,
    ONE_LEG,
    ONE_SERVO,
    READ_ADC,
    OTHER
} TYPE;

typedef struct{
    uint8_t pData[MESSAGE_MAX_LEN];
    uint8_t dataLength;
} RAW_SPI_Message;

// Blocking functions
void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);
void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);

void analyzeRawMessage(RAW_SPI_Message* message);

#endif
