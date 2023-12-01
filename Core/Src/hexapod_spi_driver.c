#include "hexapod_spi_driver.h"
#include "spi.h"
#include <stdbool.h>

static bool isFrameType(uint8_t frame_length, uint8_t suspected_frame_length){
    if(frame_length == suspected_frame_length){
        return true;
    }
    return false;
}


void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    // First send data lenth
    HAL_SPI_Transmit_IT(hspi, &message->dataLength, 1);

    HAL_SPI_Transmit_IT(hspi, message->pData, message->dataLength);
}


void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    HAL_StatusTypeDef status;

    // Get message length
    status = HAL_SPI_Receive(hspi, &message->dataLength, 1, HAL_MAX_DELAY);

    if(status == HAL_OK){
        HAL_SPI_Receive(hspi, message->pData, message->dataLength, HAL_MAX_DELAY);
    }
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}


void analyzeRawMessage(RAW_SPI_Message* message){
    uint8_t type = message->pData[0];

    switch (type) {
        case ALL_SERVO:
            if(isFrameType(message->dataLength, ALL_SERVO_TYPE_LEN)){

            }
            break;
        case ONE_LEG:
            if(isFrameType(message->dataLength, ONE_LEG_TYPE_LEN)){

            }
            break;
        case ONE_SERVO:
            if(isFrameType(message->dataLength, ONE_SERVO_LEN)){

            }
            break;
        case READ_ADC:
            // TODO To be completed in the future
            break;
        default:
            break;
    }
}