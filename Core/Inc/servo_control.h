#ifndef STM32F446_CONTROL_SERVO_CONTROL_H
#define STM32F446_CONTROL_SERVO_CONTROL_H

/*  PWM Servo Parameters
 *  PWM Period:             20ms
 *  PWM Frequency:          50 Hz
 *
 *  Position -90 deg:       1ms
 *  Position 0 deg:         1.5ms
 *  Position 90 deg:        2ms
 *
 *  Or
 *
 *  Position 0 deg:         1ms
 *  Position 90 deg:        1.5ms
 *  Position 180 deg:       2ms
 *
 *  So generally duty cycle will range from 10% - 20% of whole period
 *
 * */

#include "tim.h"

// General servo variables
#define MIN_ANGLE                               (-90.f)
#define MAX_ANGLE                               90.f

#define MIN_ANGLE_PULSE_MS                      1
#define MAX_ANGLE_PULSE_MS                      2

// Define servo timers
#define SERVO_11_TIMER                          TIM1
#define SERVO_12_TIMER                          TIM1
#define SERVO_13_TIMER                          TIM1

// Define channels assigned for each servo
#define SERVO_11_CHANNEL                        TIM_CHANNEL_1
#define SERVO_12_CHANNEL                        TIM_CHANNEL_2
#define SERVO_13_CHANNEL                        TIM_CHANNEL_3


void startPWMServo(TIM_HandleTypeDef* tim, uint8_t channel);
void disablePWMServo(TIM_HandleTypeDef* tim, uint8_t channel);

void setPWMPulseValue(TIM_HandleTypeDef* tim, uint8_t channel, uint16_t pulse_value);
void setServoAngle(TIM_HandleTypeDef* tim, uint8_t channel, float angle);

uint16_t calculateCCRValue(float min_angle, float max_angle, float angle, uint16_t min_ms, uint16_t max_ms);


#endif
