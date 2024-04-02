#ifndef HEXAPOD_PROTOCOL_H
#define HEXAPOD_PROTOCOL_H

#include <unistd.h>
#include <stdbool.h>
#include "spi.h"

// Hardware Controller Hexapod Communication Protocol
// File: hexapod_protocol.h
// Version: 1.0
// Authors: Hexapod Bionik Team

// Message lengths
#define MESSAGE_MAX_LEN         64

static const uint8_t MAJOR_VERSION = 2;
static const uint8_t MINOR_VERSION = 0;
static const uint8_t PATCH_VERSION = 0;

static const uint8_t INFO_FIRST_CHECK_BYTE = 21;
static const uint8_t SECOND_CHECK_BYTE = 87;

#define HEXAPOD_RECEIVE_TIMEOUT     1000
#define HEXAPOD_TRANSMIT_TIMEOUT    1000

// Enumeration defining message types
typedef enum {
    ONE_LEG = 1,
    ONE_SERVO = 2,
    INFO = 3,
    ADC_READ = 4
} TYPE;

typedef enum{
    ONE_LEG_TRANSMIT = 14,
    ONE_SERVO_TRANSMIT = 6,
    INFO_TRANSMIT = 2,
    ADC_TRANSMIT = 2
} FRAME_TRANSMIT_LEN;

typedef enum{
    INFO_RECEIVE = 7,
    ADC_RECEIVE = 7
} FRAME_RECEIVE_LEN;

// Structure representing a raw SPI message
typedef struct {
    uint8_t pData[MESSAGE_MAX_LEN];  // Data array to store the message
    uint8_t dataLength;               // Length of the message data
} RAW_SPI_Message;

/**
 * @brief Sends a Hexapod SPI message in blocking mode
 *
 * @param hspi: Pointer to the SPI Handle structure
 * @param message: Pointer to the SPI message structure to send
 */
void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message);

/**
 * @brief Receives a Hexapod SPI message in blocking mode
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
void interpretMessage(RAW_SPI_Message* message, bool* receive, RAW_SPI_Message* transmit_message);

#endif // HEXAPOD_PROTOCOL_H