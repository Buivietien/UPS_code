#include "pid_control.h"


volatile float clip(const float x, const float a, const float b) {
  return x < a ? a : x > b ? b : x;
}

volatile q15_t convert_float_q15(float input, int16_t max_value){
  int32_t result = (input * 32767.0f / max_value);
  return (q15_t)result;
}

volatile float convert_q15_float(q15_t input, int16_t max_value){
  float result = (input * max_value) / 32767.0f;
  return result;
}

volatile q15_t convert_in16t_q15(int16_t input, int16_t max_value){
  int32_t result = (input * 32767 / max_value);
  return (q15_t)result;
}

volatile int16_t convert_q15_int16t(q15_t input, int16_t max_value){
  int32_t result = (input * max_value/ 32767);
  return (int16_t)result;
}

volatile q15_t clip_q15(const q15_t x, const q15_t a, const q15_t b) {
  return x < a ? a : x > b ? b : x;
}

volatile q15_t q15_abs(q15_t num){
  q15_t value = num;

  if(value < 0){
      if(value < -32767)  value = 32767;
      else                value = -value;
  }

  return value;
}

volatile int16_t q15_to_int(q15_t num){
  int16_t value = 0;

  if(num > 16383)
      value = 1;
  else if(num < -16383)
      value = -1;

  return value;
}

q15_t q15_add(q15_t addend, q15_t adder){
  int32_t result = (uint32_t)addend + (uint32_t)adder;

  if(result > 32767)          result = 32767;
  else if(result < -32768)    result = -32768;

  return (q15_t)result;
}

q15_t q15_sub(q15_t minuend, q15_t subtrachend){
  int32_t result = (uint32_t)minuend - (uint32_t)subtrachend;

  if(result > 32767)          result = 32767;
  else if(result < -32768)    result = -32768;

  return (q15_t)result;
}

volatile q15_t q15_mul(q15_t multiplicand, q15_t multiplier){
  int32_t product = ((int32_t)multiplicand * (int32_t)multiplier) / 32768;
  return (q15_t)product;
}

volatile q15_t q15_div(q15_t dividend, q15_t divisor){
  q15_t quotient;

  /* check to ensure dividend is smaller in magnitude
  * than the divisor */
  if((q15_abs(divisor) < q15_abs(dividend)) || (divisor == 0)){
      /* saturation: if signs are different,
      * then saturate negative */
  if((divisor & 0x8000) ^ (dividend & 0x8000)){
      quotient = -32768;
  } else {
      quotient = 32767;
  }
    } else {
        quotient = 32768 * dividend/divisor;
    }

    return quotient;
}

volatile void pid_update(const float input, const float ff, const float dt,
                pid_control_t* pid, const float* derivative) {
  // Update control error
  pid->error = pid->setpoint - input;

  if (abs(pid->error) > pid->windup_error_thres){ //Reset the error sum if the error is too large
    pid->error_sum = 0;
  }
  // Contribution from error derivative de/dt.
  // This is intended to add stabilization or damping by countering high
  // rates of change in the measured system behavior. This generally only works
  // well if d(setpoint)/dt is small, otherwise including it can cause the
  // output to spike. So we approximate de/dt as (0 - d(input)/dt). However, it
  // is up to the user whether to include d(setpoint)/dt or omit it.
  // User-provided de/dt values are not modified here.
  float derivative_term = 0.;
  if (derivative) {
    derivative_term = pid->kd * (*derivative);
  } else {
    derivative_term = -pid->kd * (input - pid->input) / dt;
  }

  // Update integrator with accumulated error and keep it bounded
  pid->error_sum += pid->ki * pid->error * dt;
  pid->error_sum = clip(pid->error_sum, pid->min_output, pid->max_output);

  // Compute output and keep it bounded.
  pid->output = ff + pid->kp * pid->error + pid->error_sum + derivative_term;
  pid->output = clip(pid->output, pid->min_output, pid->max_output);

  pid->input = input;
}


volatile void pid_update_Q15(const q15_t input, const q15_t ff, const q15_t dt,
                    pid_control_q15_t* pid, const q15_t* derivative) {
  
                      // Update control error
  pid->error = q15_sub(pid->setpoint , input);

  if (q15_abs(pid->error) > pid->windup_error_thres){ //Reset the error sum if the error is too large
    pid->error_sum = 0;
  }
  // Contribution from error derivative de/dt.
  // This is intended to add stabilization or damping by countering high
  // rates of change in the measured system behavior. This generally only works
  // well if d(setpoint)/dt is small, otherwise including it can cause the
  // output to spike. So we approximate de/dt as (0 - d(input)/dt). However, it
  // is up to the user whether to include d(setpoint)/dt or omit it.
  // User-provided de/dt values are not modified here.
  q15_t derivative_term = 0.;
  if (derivative) {
    derivative_term = pid->kd * (*derivative);
  } else {
    derivative_term = -pid->kd * (input - pid->input) / dt;
  }

  // Update integrator with accumulated error and keep it bounded
  pid->error_sum += q15_mul(pid->ki, q15_mul(pid->error, dt));
  pid->error_sum = clip_q15(pid->error_sum, pid->min_output, pid->max_output);

  // Compute output and keep it bounded.
  // q15_t intermediate = pid->error + pid->error_sum + derivative_term;
  volatile q15_t intermediate = pid->error;
  pid->output_q15 = ff + q15_mul(pid->kp, intermediate) + pid->error_sum + derivative_term;
  pid->output_q15 = clip_q15(pid->output_q15, pid->min_output, pid->max_output);

  //Convert this to output per max output val: Basically convert q15 back to int16
  pid->output_int16 = convert_q15_int16t(pid->output_q15, pid->normalizing_val);
  pid->input = input;

}
