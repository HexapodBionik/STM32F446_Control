#include "servo_control.h"

static uint16_t map_value(float x, float in_min, float in_max, float out_min, float out_max){
    float scaled_value = ((x - in_min) * (out_max - out_min) / (in_max - in_min) +
                          out_min);
    return (uint16_t)scaled_value;
}

void startPWMServo(TIM_HandleTypeDef* tim, uint8_t channel){
    HAL_TIM_PWM_Start(tim, channel);
}

void disablePWMServo(TIM_HandleTypeDef* tim, uint8_t channel){
    HAL_TIM_PWM_Stop(tim, channel);
}

void setPWMPulseValue(TIM_HandleTypeDef* tim, uint8_t channel, uint16_t pulse_value_us){
    __HAL_TIM_SET_COMPARE(tim, channel, pulse_value_us);
}

uint16_t calculateCCRValue(float min_angle, float max_angle, float angle, uint16_t min_ms, uint16_t max_ms){
    // Broaden the resolution
    uint16_t min_us = min_ms * 1000;
    uint16_t max_us = max_ms * 1000;

    return map_value(angle, min_angle, max_angle, min_us, max_us);
}

void setServoAngle(TIM_HandleTypeDef* tim, uint8_t channel, float angle){
    uint16_t new_CCR_value = calculateCCRValue(MIN_ANGLE, MAX_ANGLE, angle, MIN_ANGLE_PULSE_MS, MAX_ANGLE_PULSE_MS);
    setPWMPulseValue(tim, channel, new_CCR_value);
}