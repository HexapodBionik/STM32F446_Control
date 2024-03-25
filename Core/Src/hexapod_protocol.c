#include "hexapod_protocol.h"
#include "spi.h"
#include "hexapod_protocol_execute.h"
#include <memory.h>

static const uint8_t INFO_array[] = {0x07, 0x03, 0x15, 0x57, 0x00, 0x00, 0x01};


static void convert_to_uint8_t(const uint32_t* data, uint8_t* data_table){
    data_table[0] = (uint8_t)(*data >> 24);
    data_table[1] = (uint8_t)((*data & 0xffffff) >> 16);
    data_table[2] = (uint8_t)((*data & 0xffff) >> 8);
    data_table[3] = (uint8_t)(*data & 0xff);
}

static void convert_to_uint32_t(uint32_t* data, const uint8_t* data_table){
    for(int i = 0; i < 4; i++){
        *data |= data_table[i] << (3-i)*8;
    }
}

static void assign_to_transmit_message(RAW_SPI_Message* transmit_message, const uint8_t message_length,
                                       const uint8_t start_index, const uint8_t copy_length,
                                       const uint8_t* data_table){
    // Clear transmit message table
    transmit_message->dataLength = 0;
    memset(transmit_message->pData, 0, MESSAGE_MAX_LEN);

    // Assign message length and copy data
    transmit_message->dataLength=message_length;
    memcpy(transmit_message->pData, data_table+start_index, copy_length);
}

static bool isFrameType(uint8_t frame_length, uint8_t suspected_frame_length){
    return frame_length == suspected_frame_length;
}


void sendSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    // First send data lenth
    HAL_SPI_Transmit(hspi, message->pData, message->dataLength, HEXAPOD_RECEIVE_TIMEOUT);
}


void receiveSPIBlocking(SPI_HandleTypeDef* hspi, RAW_SPI_Message* message){
    HAL_StatusTypeDef status;

    // Get message length
    status = HAL_SPI_Receive(hspi, &message->dataLength, 1, HEXAPOD_RECEIVE_TIMEOUT);

    if(status == HAL_OK){
        HAL_SPI_Receive(hspi, message->pData, message->dataLength, HEXAPOD_RECEIVE_TIMEOUT);
    }
}


void interpretMessage(RAW_SPI_Message* message, bool* receive, RAW_SPI_Message* transmit_message){
    uint8_t type = message->pData[1];

    switch (type) {
        case ONE_LEG:
            if(isFrameType(message->dataLength, ONE_LEG_LEN)){
                executeOneLeg(message->pData);
                *receive = true;
            }
            break;
        case ONE_SERVO:
            if(isFrameType(message->dataLength, ONE_SERVO_LEN)){
                executeOneServo(message->pData);
                *receive = true;
            }
            break;
        case INFO:
            {
                assign_to_transmit_message(transmit_message, INFO_LEN, 0, INFO_LEN, INFO_array);
                *receive = false;
                break;
            }
        case ADC_READ:
            {

                HAL_ADC_Start(&hadc1);
                HAL_ADC_PollForConversion(&hadc1, 1);
                const uint32_t ADC_DATA = HAL_ADC_GetValue(&hadc1);
                uint8_t data_table[4];
                convert_to_uint8_t(&ADC_DATA, data_table);

                transmit_message->pData[0] = 0x07; // data length
                transmit_message->pData[1] = 0x01; // adc number
                transmit_message->pData[2] = 0x04; // adc channel

                assign_to_transmit_message(transmit_message,ADC_LEN, 3, 4, data_table);
                *receive = false;
                break;
            }
        default:
            break;
    }

    message->dataLength = 0;
    memset(message->pData, 0, MESSAGE_MAX_LEN);
}