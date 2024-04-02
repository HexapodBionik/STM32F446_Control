#include "hexapod_protocol_execute.h"
#include "servo_control.h"
#include "hexapod_protocol.h"
#include <malloc.h>
#include <memory.h>

static TIM_HandleTypeDef* servo_timers[] = {
        SERVO_11_TIMER,
        SERVO_12_TIMER,
        SERVO_13_TIMER,
};

static uint8_t servo_channels[] = {
        SERVO_11_CHANNEL,
        SERVO_12_CHANNEL,
        SERVO_13_CHANNEL,
};

void interpretOneServoData(const uint8_t* data){
    uint8_t servo_id = data[0];
    if(servo_id / 10 == 1){
        uint8_t servo_tables_index = ((servo_id / 10) - 1)*3 + ((servo_id % 10) - 1);
        uint8_t servo_operation_type = data[1];

        float angle = (float)data[2] + (float)data[3] / 100.f;
        //float angle = 0;

        if(servo_operation_type == 1){
            // Start servo PWW with given angle
            startPWMServo(servo_timers[servo_tables_index], servo_channels[servo_tables_index]);
            setServoAngle(servo_timers[servo_tables_index], servo_channels[servo_tables_index], angle);
        }
        else if(servo_operation_type == 2) {
            // Stop servo PWM
            disablePWMServo(servo_timers[servo_tables_index], servo_channels[servo_tables_index]);
        }
        else if(servo_operation_type == 3) {
            setServoAngle(servo_timers[servo_tables_index], servo_channels[servo_tables_index], angle);
        }
    }
}

void executeOneServo(const uint8_t* data){
    uint8_t* one_servo_data = malloc(4);
    memcpy(one_servo_data,  data+2, 4);

    interpretOneServoData(one_servo_data);

    free(one_servo_data);
}

void executeOneLeg(const uint8_t* data){
    for(int i = 0; i < 3; i++){
        uint8_t* one_servo_data = malloc(4);
        memcpy(one_servo_data,  data+2+i*(ONE_SERVO_TRANSMIT-2), 4);

        interpretOneServoData(one_servo_data);

        free(one_servo_data);
    }
}