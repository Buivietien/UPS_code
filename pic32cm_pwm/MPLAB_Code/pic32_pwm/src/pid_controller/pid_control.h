#pragma once
#ifndef PID_CONTROL_H
#define PID_CONTROL_H
#include <arm_math.h>
typedef struct pid_control_params{
  // Gain coefficients
  float kp;  // proportional
  float ki;  // integral
  float kd;  // derivative

  //Anti-windup variables
  float windup_error_thres;
  // Configuration and state variables
  float setpoint;
  float input;
  float output;
  float min_output;
  float max_output;
  float error;
  float error_sum;
} pid_control_t;

//The number can only be from -1 to 1
#define Q15_custom_max_range 4096 //This is the max 12bit value
typedef struct pid_control_q15 {
  int16_t normalizing_val;
  // Gain coefficients
  q15_t kp;  // proportional
  q15_t ki;  // integral
  q15_t kd;  // derivative

  //Anti-windup variables
  q15_t windup_error_thres;
  // Configuration and state variables
  q15_t setpoint;
  q15_t input;
  volatile q15_t output_q15;
  volatile float output_float;
  volatile int16_t output_int16;
  volatile q15_t min_output;
  volatile q15_t max_output;
  volatile q15_t error;
  volatile q15_t error_sum;
} pid_control_q15_t;


typedef enum pid_param_number {
  pid_Kp,
  pid_Ki, 
  pid_Kd,
  pid_windup_error_thres,
  pid_setpoint, 
  pid_input, 
  pid_output, 
  pid_min_output, 
  pid_max_output,
  pid_error,
  pid_error_sum, 
} pid_param_number_t;

// Return a <= x <= b
float clip(const float x, const float a, const float b);

q15_t convert_float_q15(float input, int16_t max_value);

float convert_q15_float(q15_t input, int16_t max_value);

q15_t convert_in16t_q15(int16_t input, int16_t max_value);

int16_t convert_q15_int16t(q15_t input, int16_t max_value);

q15_t q15_add(q15_t addend, q15_t adder);

volatile q15_t q15_mul(q15_t multiplicand, q15_t multiplier);

volatile q15_t q15_div(q15_t dividend, q15_t divisor);

// Compute PID control output from input, a feed-forward value ff, and a
// timestep dt. The pid struct is modified with the results.
// If an error derivative de/dt is supplied (i.e. not NULL), it will be used
// in place of the internal calculation. Note that user-provided de/dt values
// are not modified here (no filtering, no negation, etc.). The expected
// definition is de/dt = d(setpoint)/dt - d(input)/dt.
void pid_update(const float input, const float ff, const float dt,
                pid_control_t* pid, const float* derivative);

void pid_update_Q15(const q15_t input, const q15_t ff, const q15_t dt, 
                pid_control_q15_t *pid, const q15_t *derivative);

#endif /* PID_CONTROL_H */
