#include "hexapod_spi_driver.h"
#include "spi.h"
#include <stdbool.h>
#include "servo_control.h"

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
                uint8_t servo_id = message->pData[1];
                uint8_t servo_operation_type = message->pData[2];
                //float angle = (float)message->pData[3] + (float)message->pData[4] / 100.f;
                float angle = 0;

                // mockup
                if(servo_operation_type == 0){
                    // Start servo PWW with given angle
                    startPWMServo(&htim1, TIM_CHANNEL_1);
                    setServoAngle(&htim1, TIM_CHANNEL_1, angle);
                    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
                }
                else if(servo_operation_type == 1) {
                    // Stop servo PWM
                    disablePWMServo(&htim1, TIM_CHANNEL_1);
                }
                else {
                    setServoAngle(&htim1, TIM_CHANNEL_1, angle);
                }
            }
            break;
        case READ_ADC:
            // TODO To be completed in the future
            break;
        default:
            break;
    }
}