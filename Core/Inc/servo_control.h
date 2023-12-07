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
#define SERVO_11_TIMER                          &htim1
#define SERVO_12_TIMER                          &htim1
#define SERVO_13_TIMER                          &htim1

#define SERVO_21_TIMER                          &htim2
#define SERVO_22_TIMER                          &htim2
#define SERVO_23_TIMER                          &htim2

#define SERVO_31_TIMER                          &htim3
#define SERVO_32_TIMER                          &htim3
#define SERVO_33_TIMER                          &htim3

#define SERVO_41_TIMER                          &htim4
#define SERVO_42_TIMER                          &htim4
#define SERVO_43_TIMER                          &htim4

#define SERVO_51_TIMER                          &htim5
#define SERVO_52_TIMER                          &htim5
#define SERVO_53_TIMER                          &htim8

#define SERVO_61_TIMER                          &htim12
#define SERVO_62_TIMER                          &htim12
#define SERVO_63_TIMER                          &htim13

// Define channels assigned for each servo
#define SERVO_11_CHANNEL                        TIM_CHANNEL_1
#define SERVO_12_CHANNEL                        TIM_CHANNEL_2
#define SERVO_13_CHANNEL                        TIM_CHANNEL_3

#define SERVO_21_CHANNEL                        TIM_CHANNEL_1
#define SERVO_22_CHANNEL                        TIM_CHANNEL_2
#define SERVO_23_CHANNEL                        TIM_CHANNEL_3

#define SERVO_31_CHANNEL                        TIM_CHANNEL_1
#define SERVO_32_CHANNEL                        TIM_CHANNEL_2
#define SERVO_33_CHANNEL                        TIM_CHANNEL_3

#define SERVO_41_CHANNEL                        TIM_CHANNEL_1
#define SERVO_42_CHANNEL                        TIM_CHANNEL_2
#define SERVO_43_CHANNEL                        TIM_CHANNEL_3

#define SERVO_51_CHANNEL                        TIM_CHANNEL_1
#define SERVO_52_CHANNEL                        TIM_CHANNEL_2
#define SERVO_53_CHANNEL                        TIM_CHANNEL_1

#define SERVO_61_CHANNEL                        TIM_CHANNEL_1
#define SERVO_62_CHANNEL                        TIM_CHANNEL_2
#define SERVO_63_CHANNEL                        TIM_CHANNEL_1

void startPWMServo(TIM_HandleTypeDef* tim, uint8_t channel);
void disablePWMServo(TIM_HandleTypeDef* tim, uint8_t channel);

void setPWMPulseValue(TIM_HandleTypeDef* tim, uint8_t channel, uint16_t pulse_value);
void setServoAngle(TIM_HandleTypeDef* tim, uint8_t channel, float angle);

uint16_t calculateCCRValue(float min_angle, float max_angle, float angle, uint16_t min_ms, uint16_t max_ms);


#endif
