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
 *  So generally duty cycle will range from 10% - 20% of the whole period
 *
 * */

#include "tim.h"

// General servo variables
#define MIN_ANGLE                               0.f
#define MAX_ANGLE                               180.f

#define MIN_ANGLE_PULSE_MS                      0.544f
#define MAX_ANGLE_PULSE_MS                      2.55f

// Define servo timers
#define SERVO_11_TIMER                          &htim3
#define SERVO_12_TIMER                          &htim3
#define SERVO_13_TIMER                          &htim3


// Define channels assigned for each servo
#define SERVO_11_CHANNEL                        TIM_CHANNEL_1
#define SERVO_12_CHANNEL                        TIM_CHANNEL_2
#define SERVO_13_CHANNEL                        TIM_CHANNEL_3

/**
 * @brief Starts PWM for a servo channel using the specified timer
 *
 * @param tim: Pointer to the Timer Handle structure
 * @param channel: Servo channel to start PWM for
 */
void startPWMServo(TIM_HandleTypeDef* tim, uint8_t channel);

/**
 * @brief Disables PWM for a servo channel using the specified timer
 *
 * @param tim: Pointer to the Timer Handle structure
 * @param channel: Servo channel to disable PWM for
 */
void disablePWMServo(TIM_HandleTypeDef* tim, uint8_t channel);

/**
 * @brief Sets the PWM pulse value for a servo channel using the specified timer
 *
 * @param tim: Pointer to the Timer Handle structure
 * @param channel: Servo channel to set the PWM pulse value for
 * @param pulse_value: The PWM pulse value to set
 */
void setPWMPulseValue(TIM_HandleTypeDef* tim, uint8_t channel, uint16_t pulse_value);

/**
 * @brief Sets the servo angle for a servo channel using the specified timer
 *
 * @param tim: Pointer to the Timer Handle structure
 * @param channel: Servo channel to set the angle for
 * @param angle: The angle to set for the servo
 */
void setServoAngle(TIM_HandleTypeDef* tim, uint8_t channel, float angle);

/**
 * @brief Calculates the CCR (Capture/Compare Register) value for a given angle
 *
 * @param min_angle: Minimum angle supported by the servo
 * @param max_angle: Maximum angle supported by the servo
 * @param angle: Target angle to calculate CCR value for
 * @param min_ms: Minimum pulse width in milliseconds
 * @param max_ms: Maximum pulse width in milliseconds
 * @return The calculated CCR value for the given angle
 */
uint16_t calculateCCRValue(float min_angle, float max_angle, float angle, float min_ms, float max_ms);

#endif