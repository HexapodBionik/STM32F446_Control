#include "hexapod_protocol.h"
#include "spi.h"
#include <stdbool.h>
#include "hexapod_protocol_execute.h"
#include <memory.h>


static bool isFrameType(uint8_t frame_length, uint8_t suspected_frame_length){
    return frame_length == suspected_frame_length;
}


void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    // First send data lenth
    HAL_SPI_Transmit_IT(hspi, &message->dataLength, 1);

    HAL_SPI_Transmit_IT(hspi, message->pData, message->dataLength);
}


void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    HAL_StatusTypeDef status;

    // Get message length
    status = HAL_SPI_Receive(hspi, &message->dataLength, 1, HEXAPOD_RECEIVE_TIMEOUT);

    if(status == HAL_OK){
        HAL_SPI_Receive(hspi, message->pData, message->dataLength, HEXAPOD_RECEIVE_TIMEOUT);
    }
}


void interpretMessage(RAW_SPI_Message* message){
    uint8_t type = message->pData[1];

    switch (type) {
        case ONE_LEG:
            if(isFrameType(message->dataLength, ONE_LEG_LEN)){
                executeOneLeg(message->pData);
            }
            break;
        case ONE_SERVO:
            if(isFrameType(message->dataLength, ONE_SERVO_LEN)){
                executeOneServo(message->pData);
            }
            break;
        default:
            break;
    }

    message->dataLength = 0;
    memset(message->pData, 0, MESSAGE_MAX_LEN);
}