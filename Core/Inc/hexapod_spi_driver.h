#ifndef STM32F446_CONTROL_HEXAPOD_SPI_DRIVER_H
#define STM32F446_CONTROL_HEXAPOD_SPI_DRIVER_H

#include <unistd.h>
#include "spi.h"


// Message lengths
#define MESSAGE_MAX_LEN         64
#define ONE_LEG_TYPE_LEN        14
#define ONE_SERVO_LEN           6

typedef enum{
    ONE_LEG=1,
    ONE_SERVO=2,
} TYPE;

typedef struct{
    uint8_t pData[MESSAGE_MAX_LEN];
    uint8_t dataLength;
} RAW_SPI_Message;

/**
 * @brief Sends a Hexapod SPI message in pooling mode
 *
 * @param hspi: Pointer to the SPI Handle structure
 * @param message: Pointer to the SPI message structure to send
 */
void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);

/**
 * @brief Receives a Hexapod SPI message in pooling mode
 *
 * @param hspi: Pointer to the SPI Handle structure
 * @param message: Pointer to the SPI message structure to receive
 */
void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);

/**
 * @brief Interprets the content of a Hexapod SPI message based on its type
 *
 * @param message: Pointer to the SPI message structure to interpret
 */
void interpretMessage(RAW_SPI_Message* message);

/**
 * @brief Interprets the content of a byte array representing data for one servo motor
 *
 * @param data: Pointer to the data array representing control information regarding one servo
 */
void interpretOneServoData(const uint8_t* data);

#endif
