#include "hexapod_spi_driver.h"
#include "spi.h"


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