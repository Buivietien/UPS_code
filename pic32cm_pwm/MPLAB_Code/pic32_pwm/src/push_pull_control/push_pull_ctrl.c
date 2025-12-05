//This file is for push pull control source code
#include "push_pull_ctrl.h"
#include <pid_controller/pid_control.h>
// #include <arm_math.h>

typedef enum push_pull_state {
    push_pull_off,
    push_pull_manual_mode,
    push_pull_softstart,
    push_pull_freq_pid_mode,
    push_pull_duty_pid_mode,
    push_pull_burst_mode,
    push_pull_outputting,
    push_pull_error,
} push_pull_state_t;
push_pull_state_t push_pull_status = push_pull_off;

typedef enum push_pull_softstart_state {
    push_pull_starting,
    push_pull_keep_1mhz,
    push_pull_ramping_down_freq,
    push_pull_softstart_exit,
} push_pull_softstart_state_t;
push_pull_softstart_state_t push_pull_softstart_status = push_pull_freq_pid_mode;

typedef enum tc4_interrupt_routine_state {
    tc4_burst_mode,
    tc4_reset,
    tc4_hold,
} tc4_interrupt_routine_state_t;


#define push_pull_freq_ramp_rate_ms 480  //48kHz per 1mS (The Unit is 0.1kHz/1mS)
#define push_pull_lower_softstart_lower_limit 2000 //The unit is kHz
#define high_freq_duration 1 //Set the high freq duration to be 5mS, could set to be lower. 
struct {
    uint16_t current_frequency;
    uint8_t freq_ramp_rate;
    uint8_t high_freq_startup_count; //This is to ensure the hihg frequency is kept running for 5mS and then switch to freq decay
} push_pull_softstart_strc;

#define burst_mode_max_period 10
#define burst_mode_switch_over_freq 3000
#define burst_mode_off_thres 200
#define burst_mode_on_thres 200
#define burst_mode_working_freq 2000
#define burst_low_power_timestamp 10
#define default_burst_hold_time 5
#define default_on_per_burst_value 2
#define burst_low_power_cycle 1
#define burst_max_hold_time 1000
struct {
    volatile uint8_t tc_isr_cnt;
    volatile uint8_t tc_low_pwr_timestamp;
    volatile uint8_t tc_hold_timestamp;
    volatile uint8_t tc_low_pwr_cnt;
    volatile uint8_t tc_low_pwr_cycle_sp;
    volatile uint16_t tc_per_val;
    volatile uint8_t burst_hold_time;
    volatile uint8_t on_per_burst;
    volatile tc4_interrupt_routine_state_t tc4_state;
    volatile uint8_t tcc2_low_pwr_cnt;
    volatile bool single_shot;
    volatile bool pid_mode;
    uint16_t input;
    uint8_t period_cnt;
    uint8_t current_per;
    int8_t on_per;
    uint16_t set_point; 
    uint16_t burst_mode_freq;
} push_pull_burst_mode_strc;

typedef enum push_pull_burst_mode_params{
    push_pull_tc_low_pwr_cycle_cnt,
    
} push_pull_burst_mode_params_t;

pid_control_q15_t burst_mode_pid; //This PID control the hold time of burst mode to adjust the output voltage

volatile uint8_t turn_count = 0;
bool tcc2_pwm_state = false;
uint16_t calculated_CC_count = 0;
uint16_t current_PER_count;
uint8_t current_duty_cycle = 48;
uint16_t current_frequency = 5000; //The unit is 0.1kHz
uint16_t calculated_PER = 0;

pid_control_t push_pull_freq_pid;

pid_control_q15_t push_pull_freq_q15_pid;

pid_control_t push_pull_duty_pid;

pid_control_q15_t push_pull_duty_q15_pid;


push_pull_protection_t push_pull_protection_strc;

void push_pull_ctrl_init(){
    //Reset Compare channel value to 0
    TCC2_REGS->TCC_CC[0] = 0U; 
    TCC2_REGS->TCC_CC[1] = 0U; 

    // Register the update_compare ISR 
    TCC2_PWMCallbackRegister(push_pull_tcc2_isr, 0);
    
    //Disable the tcc2 interrupt routine
    TCC2_PWMPeriodInterruptDisable();

    //This is for compare match 0 interrupt, turn off
    // TCC2_REGS->TCC_INTENCLR |= TCC_INTENSET_MC0_Msk;

    //Set pid working parameters for frequency pid controller
    push_pull_freq_pid.setpoint = 3300; //Output voltage of the controller, read form 12bit adc then 890 equals 350V (4096 = 400V)
    push_pull_freq_pid.min_output = 0;   //This is the max frequency value (500kHz). The unit is 0.1kHz
    push_pull_freq_pid.max_output = 2700; //This is the resonant frequency (130khz). The unit is 0.1kHz
    push_pull_freq_pid.windup_error_thres = 1000; //This is the anti-windup up threshold, if the error is outside of this bound, the sum is reset
    push_pull_freq_pid.kp = 1; //Intial value, might update later.
    push_pull_freq_pid.ki = 0.5;
    //Dont use deriative terms

    //Set pid working parameters for frequency q15 pid controller
    push_pull_freq_q15_pid.normalizing_val = 4096; //Normalizing value for Q15 math, this is taken from max ADC value
    push_pull_freq_q15_pid.setpoint = convert_in16t_q15(3300, push_pull_freq_q15_pid.normalizing_val); //Output voltage of the controller, read form 12bit adc then 890 equals 350V (1023 = 400V)
    push_pull_freq_q15_pid.min_output = 0;   //This is the max frequency value (300kHz). The unit is 0.1kHz
    push_pull_freq_q15_pid.max_output = convert_in16t_q15(1300, push_pull_freq_q15_pid.normalizing_val); //This is the resonant frequency (300kHz - 120khz = 180khz). The unit is 0.1kHz
    push_pull_freq_q15_pid.windup_error_thres = convert_in16t_q15(1000, push_pull_freq_q15_pid.normalizing_val); //This is the anti-windup up threshold, if the error is outside of this bound, the sum is reset
    push_pull_freq_q15_pid.kp = convert_float_q15(1600, push_pull_freq_q15_pid.normalizing_val); //Intial value, might update later.
    push_pull_freq_q15_pid.ki = 0; //Dont use Ki value for now.

    //Establish the pid working parameter for duty cycle control here:
    push_pull_duty_pid.setpoint = 3100; //Output voltage of the controller, read form 12bit adc then 3100 equals 310V (4096 = 400V)
    push_pull_duty_pid.min_output = 0;   //This is the min duty cycle, can set at 0%
    push_pull_duty_pid.max_output = 48; //This is the max duty cycle at 48%
    push_pull_duty_pid.windup_error_thres = 1000; //This is the anti-windup up threshold, if the error is outside of this bound, the sum is reset
    push_pull_duty_pid.kp = 0.5; //Intial value, might update later.
    push_pull_duty_pid.ki = 0; //Don't use the Ki param for now

    //Establish the pid q15 working parameter for duty cycle control here:
    push_pull_duty_q15_pid.normalizing_val = 4096; //Normalizing value for Q15 math
    push_pull_duty_q15_pid.setpoint = convert_in16t_q15(3100, push_pull_duty_q15_pid.normalizing_val); //Output voltage of the controller, read form 12bit adc then 3100 equals 310V (4096 = 400V)
    push_pull_duty_q15_pid.min_output = 0;   //This is the min duty cycle, can set at 0%
    push_pull_duty_q15_pid.max_output = convert_in16t_q15(48, push_pull_duty_q15_pid.normalizing_val); //This is the max duty cycle at 48%
    push_pull_duty_q15_pid.windup_error_thres = convert_in16t_q15(1000, push_pull_duty_q15_pid.normalizing_val); //This is the anti-windup up threshold, if the error is outside of this bound, the sum is reset
    push_pull_duty_q15_pid.kp = convert_float_q15(700, push_pull_duty_q15_pid.normalizing_val); //After experimenting, Kp(scaled by 4096) = 700 seems fine. 
    push_pull_duty_q15_pid.ki = 0; //Don't use the Ki param for now

    //Initialize push pull protection value
    push_pull_protection_strc.max_adc_voltage = 4000; //Set the max output voltage is around 400V
    push_pull_protection_strc.max_adc_voltage = 1000; //This value is currently arbitrary. 


    //Init tc4 for burst mode operation, current the frequency is set at 30kHz, welll outside of audible range.
    TC4_TimerInitialize();
    // TC4_TimerCallbackRegister(tc4_burst_mode_isr, 0);
    TC4_TimerCallbackRegister(tc4_duty_pid_control, 0);

    //Set up the default state for burst mode single shot
    push_pull_burst_mode_strc.single_shot = false;
    push_pull_burst_mode_strc.pid_mode = false;

    //Set up the default pin state for push pull external UCC2560 IC
    PP_ENB_OutputEnable();
    PP_ENB_Clear(); //Default is keep the pin shutdown
}

void push_pull_pwm_start(){
    tcc2_pwm_state = true;
    update_tcc2_parameters();
    // printf("push pull pwm on\n");
}

void push_pull_pwm_stop(){
    tcc2_pwm_state = false;
    TCC2_PWMStop();
    update_tcc2_parameters();
    // printf("push pull pwm off\n");

}

void update_tcc2_parameters(){
    // TCC2_PWMStop();
    //Update frequency
    calculated_PER = 48e4 / (current_frequency); //This formula is 48MHz / current_frequency * 0.1kHz. 
    TCC2_PWM16bitPeriodSet(calculated_PER);
    
    //Update duty cycle, add deadtime calculation here, deadtime is 100nS, equals count ~ 5.
    calculated_CC_count = calculated_PER - (calculated_PER * current_duty_cycle * 2) / 100;
    //Maintain the deadtime by setting the minimum cc_count value is 5. Set the hard value here too, since to breach this value, the frequency has to to up to 2MHz. Which is impossible!
    if (calculated_CC_count < 5) {
        calculated_CC_count = 5;
        current_duty_cycle = 100 * calculated_PER / calculated_CC_count * 2; //Recalculate the current duty cycle value
    }

    TCC2_REGS->TCC_CC[0] = calculated_CC_count;
    if (tcc2_pwm_state == true){
        // TCC2_PWMStart(); //Don use TCC2_IC
        PP_ENB_InputEnable(); //Turn the pin into high impendance mode for the module resister to activate the IC
    } else {
        PP_ENB_OutputEnable(); //Turn off the IC by pulling this pin LOW.
        PP_ENB_Clear();
    }
}

//Set duty cylce for the TCC2, the number run from 0 to 49
uint8_t push_pull_duty_change(uint8_t duty_cycle){
    //Default duty cycle is 50%
    //Reject the input value if it is outside 0 - 49
    if (duty_cycle > 49 || duty_cycle < 0){
        // printf("pp_duty Invalid input value\n");
        return current_duty_cycle;
    }
    current_duty_cycle = duty_cycle;
    // printf("Set duty cycle: %d\n", current_duty_cycle);
    update_tcc2_parameters();
    return current_duty_cycle;
}

uint16_t push_pull_frequency_change(uint16_t frequency){
    //Reject invalid values
    if (frequency > 12000 || frequency < 500){
        // printf("pp_freq Invalid input value\n");
        return current_frequency; 
    }
    current_frequency = frequency;
    
    // printf("Set frequency (per 0.1kHz): %d\n", current_frequency);
    update_tcc2_parameters();
    return current_frequency; 
}

//Set up the parameter for PUSH-PULL PID controller, for Kp, Ki, negative is error value, for voltage, zero is error value
float push_pull_set_freq_pid_params(pid_param_number_t select, float val){
   if (val > 0){
        switch (select)
        {
        case pid_Kp:
            push_pull_freq_pid.kp = val;
            //Update the q15 value here too!
            push_pull_freq_q15_pid.kp = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;

        case pid_Ki:
            push_pull_freq_pid.ki = val;
            //Update the q15 value here too!
            push_pull_freq_q15_pid.ki = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;

        case pid_setpoint:
            push_pull_freq_pid.setpoint = val;
            //Update the q15 value here too!
            push_pull_freq_q15_pid.setpoint = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;

        case pid_min_output:
            push_pull_freq_pid.min_output = val;
            //Update the q15 value here too
            push_pull_freq_q15_pid.min_output = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;
        
        case pid_max_output:
            push_pull_freq_pid.max_output = val;
            //Update the q15 value here too
            push_pull_freq_q15_pid.max_output = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;
            
        case pid_windup_error_thres:
            push_pull_freq_pid.windup_error_thres = val;
            //Update the q15 value here too!
            push_pull_freq_q15_pid.windup_error_thres = convert_float_q15(val, push_pull_freq_q15_pid.normalizing_val);
            break;

        
        }
    } else {
        switch (select)
        {
        case pid_Kp:
            return convert_q15_float(push_pull_freq_q15_pid.kp, push_pull_freq_q15_pid.normalizing_val);

        case pid_Ki:
            return convert_q15_float(push_pull_freq_q15_pid.ki, push_pull_freq_q15_pid.normalizing_val);

        case pid_setpoint:
            return convert_q15_float(push_pull_freq_q15_pid.setpoint, push_pull_freq_q15_pid.normalizing_val);

        case pid_input:
            return convert_q15_float(push_pull_freq_q15_pid.input, push_pull_freq_q15_pid.normalizing_val);

        case pid_output:
            return push_pull_freq_q15_pid.output_int16;
        
        case pid_error:
            return convert_q15_float(push_pull_freq_q15_pid.error, push_pull_freq_q15_pid.normalizing_val);

        case pid_windup_error_thres:
            return convert_q15_float(push_pull_freq_q15_pid.windup_error_thres, push_pull_freq_q15_pid.normalizing_val);
            
        case pid_error_sum:
            return convert_q15_float(push_pull_freq_q15_pid.error_sum, push_pull_freq_q15_pid.normalizing_val);
        }
    }
}

float push_pull_set_duty_pid_params(pid_param_number_t select, float val){
//Use this same function to update the pid parameters both in float and q15 format
    if (val > 0){
        switch (select)
        {
        case pid_Kp:
            push_pull_duty_pid.kp = val;
            //Update the q15 here too
            push_pull_duty_q15_pid.kp = convert_float_q15(val, push_pull_duty_q15_pid.normalizing_val);
            break;

        case pid_Ki:
            push_pull_duty_pid.ki = val;
            //Update the q15 here too
            push_pull_duty_q15_pid.ki = convert_float_q15(val, push_pull_duty_q15_pid.normalizing_val);
            break;

        case pid_setpoint:
            push_pull_duty_pid.setpoint = val;
            //Update the q15 here too
            push_pull_duty_q15_pid.setpoint = convert_float_q15(val, push_pull_duty_q15_pid.normalizing_val);
            break;
    
        case pid_max_output:
            push_pull_duty_pid.max_output = val;
            //Update the q15 here too
            push_pull_duty_q15_pid.max_output = convert_float_q15(val, push_pull_duty_q15_pid.normalizing_val);
            break;
             
         case pid_windup_error_thres:
            push_pull_duty_pid.windup_error_thres = val;
            //Update the q15 here too
            push_pull_duty_q15_pid.windup_error_thres = convert_float_q15(val, push_pull_duty_q15_pid.normalizing_val);
             break;
 
         
         }
     } else {
        switch (select)
        {
        case pid_Kp:
            return push_pull_duty_pid.kp;

        case pid_Ki:
            return push_pull_duty_pid.ki;

        case pid_setpoint:
            return push_pull_duty_pid.setpoint;

        case pid_input:
            return push_pull_duty_pid.input;

        case pid_output:
            return push_pull_duty_pid.output;
        
        case pid_error:
            return push_pull_duty_pid.error;

        case pid_windup_error_thres:
            return push_pull_duty_pid.windup_error_thres;
            
        case pid_error_sum:
            return push_pull_duty_pid.error_sum;
        
        case pid_max_output:
            return push_pull_duty_pid.max_output;
         }
     }
 }

uint16_t push_pull_set_burst_mode_param(pid_param_number_t select, uint16_t val){
    if (val > 0){
            switch (select)
            {
            case pp_burst_setpoint:
                //Need to be convert to Q15 before putting it into the PID params group.
                push_pull_burst_mode_strc.set_point = val;
                break;
    
            case pp_burst_holdtime:
                push_pull_burst_mode_strc.burst_hold_time = val;
                break;
    
            case pp_burst_number_of_burst:
                push_pull_burst_mode_strc.on_per_burst = val;
                break;
                
            }
        } else {
            switch (select)
            {
            case pp_burst_setpoint:
                return push_pull_burst_mode_strc.set_point;
    
            case pp_burst_holdtime:
                return push_pull_burst_mode_strc.burst_hold_time;
    
            case pp_burst_number_of_burst:
                return push_pull_burst_mode_strc.on_per_burst;
            }
        }
}

void push_pull_set_deadtime(){
    //Currently, I dont set this because the duty max is 49%
}


//Should I use type Q15 to do the control law here? Ok, I think I should, but first, I will implement the control via float.
//The value here should be in accordane with the ADC input value (12bit = 1024). The maximum input value is 400V -> 1024. Maybe Q15 math should be based on this.
//This function is run every 1mS in the 
void push_pull_control_law(){
    
}

void push_pull_test_softstart(){
    push_pull_status = push_pull_softstart;
    push_pull_softstart_status = push_pull_starting;
}

void push_pull_enter_freq_pid_mode(){
    push_pull_status = push_pull_freq_pid_mode;
    //Turn on tc4 
    TC4_TimerStart();
}

void push_pull_enter_duty_pid_mode(){
    push_pull_status = push_pull_duty_pid_mode;
    //Turn on tc4 here
    TC4_TimerStart();
}

void push_pull_exit_duty_pid_mode(){    
    //Turn off tc4 here
    TC4_TimerStop();
}

void push_pull_enter_burst_mode(bool single_shot, bool pid_mode){
    //Initialize states and data
    push_pull_status = push_pull_burst_mode;
    push_pull_burst_mode_strc.tc4_state = tc4_burst_mode;
    push_pull_burst_mode_strc.burst_hold_time = default_burst_hold_time;
    push_pull_burst_mode_strc.tc_low_pwr_cycle_sp = burst_low_power_cycle;
    push_pull_burst_mode_strc.on_per_burst = default_on_per_burst_value;

    //Reset process variables 
    push_pull_burst_mode_strc.tc_low_pwr_cnt = 0;
    push_pull_burst_mode_strc.tc_isr_cnt = 0;

    //Set up PID parameters:
    burst_mode_pid.normalizing_val = 4096;
    burst_mode_pid.kp =  ( 10 / burst_mode_pid.normalizing_val ) * 2^15;
    burst_mode_pid.ki = ( 1 / burst_mode_pid.normalizing_val ) * 2^15;
    burst_mode_pid.setpoint = ( 3300 / burst_mode_pid.normalizing_val ) * 2^15;

    //Enable TCC2 period interrupt
    TCC2_PWMPeriodInterruptEnable();

    //Start TC4 timer
    TC4_TimerStart();

    //Start push pull pwm here so I don't have to turn on manually. 
    push_pull_pwm_start();

    //Enable the single shot mode here:
    push_pull_burst_mode_strc.single_shot = single_shot;

    //Enable the PID burst mode here:
    push_pull_burst_mode_strc.pid_mode = pid_mode;
    
}

void push_pull_error_handler(push_pull_error_id_t error_id, push_pull_error_caller_id_t caller_id){
    switch (error_id)
    {
        case push_pull_overvoltage:
        //Turn off push_pull output here to protect the circuit
            push_pull_pwm_stop();
        break;
    
        case push_pull_no_output:
            push_pull_pwm_stop();
        break;
    }
    //Flash the indicating led
    led_show_signal(led_push_pull_error_flash, 0, 1);
    //Report the error and caller here:
    printf("Push pull error code: %d from %d\n", error_id, caller_id);
}

void push_pull_exit_burst_mode(){
    //Disable TCC2 period interrupt
    TCC2_PWMPeriodInterruptDisable();

    //Stop TC4 timer
    TC4_TimerStop();
}

void push_pull_run_mode(const push_pull_state_t run_mode){
    switch (run_mode)
    {
        case push_pull_freq_pid_mode: case push_pull_burst_mode:
        push_pull_status = run_mode;
        break;
    }
}


void push_pull_state_machine(){
    //Grad the ADC value, Calculate 10 samples average
    
    //Control the push pull via simple PID controller
    switch (push_pull_status)
    {
        case push_pull_off:
        push_pull_softstart_status = push_pull_starting;
        break;
        
        case push_pull_softstart:
        push_pull_soft_start();
        break;
        
        case push_pull_freq_pid_mode:
            push_pull_freq_q15_pid.input = convert_in16t_q15(read_adc_int(PP_Vol_MCU_channel), push_pull_freq_q15_pid.normalizing_val); //Grab the ADC value. This value varies from 0 to 4096
        //The PID would output from 200 to 800kHz frequency, but the power follows inverse relation. So I need to inverse the output value
            pid_update_Q15(push_pull_freq_q15_pid.input, 0, 1, &push_pull_freq_q15_pid, 0); //Well this is kinda crude, need to improve later.         
            push_pull_frequency_change(3000 - push_pull_freq_q15_pid.output_int16);
            if (3000 - push_pull_freq_pid.output > 2800){
                //Switch to duty pid to further reduce outputing power
                // push_pull_status = push_pull_duty_pid_mode;
                // push_pull_burst_mode_strc.set_point = push_pull_pid.setpoint;
                // push_pull_frequency_change(burst_mode_working_freq);
            }
        break;

        case push_pull_duty_pid_mode:
            push_pull_duty_q15_pid.input = convert_in16t_q15(read_adc_int(PP_Vol_MCU_channel), push_pull_duty_q15_pid.normalizing_val);
            pid_update_Q15(push_pull_duty_q15_pid.input, 0, 1, &push_pull_duty_q15_pid, 0);
            push_pull_duty_change(convert_q15_int16t(push_pull_duty_q15_pid.output_q15, push_pull_duty_q15_pid.normalizing_val));
            if (current_duty_cycle > 47){
                //If the duty cycle is almost at maximum value, change the control scheme to frequency
                push_pull_status = push_pull_freq_pid_mode;
            }
        
        break;
        
        case push_pull_burst_mode:
            //Only do the calculation for push pull burst mode here
            //Grab the ADC value. 
            push_pull_burst_mode_strc.input = read_adc_int(PP_Vol_MCU_channel);
            break;
        
        case push_pull_error:
        
        break;
        
        default:
        break;
    }   
}

//Return true if the softstart sequence is completed, false if the sequence is on-going.
bool push_pull_soft_start(){
    switch (push_pull_softstart_status)
    {
        case push_pull_starting:
        //Start at 1MHz
        push_pull_frequency_change(10000); //Start the frequency at 1Mhz, and step down to 200kHz
        //Set duty cycle at 48%
            push_pull_duty_change(48);
            push_pull_softstart_strc.current_frequency = push_pull_frequency_change(0); //Grab the current frequency of the push pull converter
            push_pull_softstart_strc.high_freq_startup_count = 0;
            push_pull_softstart_status = push_pull_keep_1mhz;
            push_pull_pwm_start();
            break;

        case push_pull_keep_1mhz:
            //Keep the high freq for a specified time to reduce start up time;
            push_pull_softstart_strc.high_freq_startup_count++;
            if (push_pull_softstart_strc.high_freq_startup_count > high_freq_duration){
                push_pull_softstart_status = push_pull_ramping_down_freq; 
            }
            break;
            
            case push_pull_ramping_down_freq:
            push_pull_softstart_strc.current_frequency -= push_pull_freq_ramp_rate_ms;
            if (push_pull_softstart_strc.current_frequency < push_pull_lower_softstart_lower_limit){
                push_pull_softstart_status = push_pull_freq_pid_mode;
            }
            push_pull_frequency_change(push_pull_softstart_strc.current_frequency);
            break;
            
        case push_pull_softstart_exit:
            //Set up the PID with the current running frequency:
            push_pull_freq_pid.output = push_pull_softstart_strc.current_frequency;
            return true;
            break;
            
            default:
            break;
        }
        return false;
    }
    
    
//This isr is used to control the push-pull burst mode. 
void tc4_burst_mode_isr(){  
    switch (push_pull_burst_mode_strc.tc4_state)
    {
    case tc4_burst_mode:
        push_pull_pwm_start();
        break;
    
    case tc4_reset:
        push_pull_burst_mode_strc.tc_low_pwr_cnt = 0;
        push_pull_burst_mode_strc.tc_isr_cnt = 0;
        push_pull_burst_mode_strc.tc4_state = tc4_hold;
        push_pull_pwm_stop();
        push_pull_burst_mode_strc.tcc2_low_pwr_cnt = 0;
        //Turn off Oneshot mode here:
        TCC2_REGS->TCC_CTRLBCLR |= TCC_CTRLBCLR_ONESHOT_Msk;
        while(TCC2_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB_Msk){
            //Do nothing, wait for CTRLB to sync
        }

        //Single shot mode, only generate one pulse and turn off everything:
        if (push_pull_burst_mode_strc.single_shot){
            push_pull_pwm_stop();
            push_pull_exit_burst_mode();
        }
        TCC2_PWMPeriodInterruptEnable();
        break;

    case tc4_hold:
        push_pull_burst_mode_strc.tc_isr_cnt++;
        if (push_pull_burst_mode_strc.tc_isr_cnt > push_pull_burst_mode_strc.burst_hold_time){
            push_pull_burst_mode_strc.tc4_state = tc4_burst_mode;
        }
        break;
    }  

    //Should I do the calculation here?
    int16_t adc_input = read_adc_int(PP_Vol_MCU_channel);
    if (adc_input > 3800){
        //Turn off immediately to protect the circuit
        push_pull_pwm_stop();
        push_pull_exit_burst_mode();
    }
    if (push_pull_burst_mode_strc.pid_mode){
        pid_update_Q15((adc_input / burst_mode_pid.normalizing_val) * 2^15, 0, 1, &burst_mode_pid, 0);
        push_pull_burst_mode_strc.burst_hold_time = burst_max_hold_time - burst_mode_pid.output_q15;
    }
}

void tc4_duty_pid_control(){
    //Run the PID control mode for duty cycle control here!
    // push_pull_duty_pid.input = read_adc_int(PP_Vol_MCU_channel);
    // pid_update(push_pull_duty_pid.input, 0, 1, &push_pull_duty_pid, 0);
    // push_pull_duty_change(push_pull_duty_pid.output);
    
    //Do the PID calculation using Q15 math, moved into the push_pull_state_machine
    // push_pull_duty_q15_pid.input = convert_in16t_q15(read_adc_int(PP_Vol_MCU_channel), push_pull_duty_q15_pid.normalizing_val);
    // pid_update_Q15(push_pull_duty_q15_pid.input, 0, 1, &push_pull_duty_q15_pid, 0);
    // push_pull_duty_change(convert_q15_int16t(push_pull_duty_q15_pid.output_q15, push_pull_duty_q15_pid.normalizing_val));

    //Put the push pull state machine here
    push_pull_state_machine();
}

//This isr is used to count exactly 4 pulses and turn off tcc2
void push_pull_tcc2_isr(){
    push_pull_burst_mode_strc.tcc2_low_pwr_cnt++;
    if (push_pull_burst_mode_strc.tcc2_low_pwr_cnt >= push_pull_burst_mode_strc.on_per_burst){
        //This is for period interrupt, stop the TCC2 timer when enough pulse has passes.
        TCC2_PWMPeriodInterruptDisable();
        // push_pull_pwm_stop();

        //Turn on Oneshot mode here to finish the last period
        TCC2_REGS->TCC_CTRLBSET |= TCC_CTRLBSET_ONESHOT_Msk;
        while(TCC2_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB_Msk){
            //Do nothing, wait for CTRLB to sync
        }
        push_pull_burst_mode_strc.tc4_state = tc4_reset;
    }
}