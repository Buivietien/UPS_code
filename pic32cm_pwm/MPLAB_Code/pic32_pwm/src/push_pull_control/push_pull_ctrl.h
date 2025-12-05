#pragma once
#include "definitions.h"
#include <printf_custom\printf.h>
#include <inverter_control/inverter.h>
#include <pid_controller/pid_control.h>
#include <system_mornitor_n_leds/system_mornitor.h>

typedef enum burst_mode_strct_param_num {
    pp_burst_setpoint,
    pp_burst_holdtime,
    pp_burst_number_of_burst,
} burst_mode_strct_param_num_t;

typedef enum push_pull_error_id {
    push_pull_overvoltage, 
    push_pull_no_output,
    push_pull_over_current,
    push_pull_low_freq,
    push_pull_high_freq
} push_pull_error_id_t;

typedef enum push_pull_error_caller_id {
    from_push_pull,
    from_inverter,
    from_system_mornitor,
    from_adc,
} push_pull_error_caller_id_t;

typedef struct push_pull_protection{
    volatile uint16_t max_adc_voltage;
    volatile uint16_t max_adc_current;
} push_pull_protection_t;

extern push_pull_protection_t push_pull_protection_strc;

void push_pull_ctrl_init();

void push_pull_pwm_start();

void push_pull_pwm_stop();

void update_tcc2_parameters();

uint8_t push_pull_duty_change(uint8_t duty_cycle);

uint16_t push_pull_frequency_change(uint16_t frequency);

float push_pull_set_freq_pid_params(pid_param_number_t select, float val);

float push_pull_set_duty_pid_params(pid_param_number_t select, float val);

uint16_t push_pull_set_burst_mode_param(pid_param_number_t select, uint16_t val);

void push_pull_set_deadtime();

void tc4_burst_mode_isr();

void tc4_duty_pid_control();

void push_pull_tcc2_isr();

void push_pull_test_softstart();

void push_pull_enter_freq_pid_mode();

void push_pull_exit_duty_pid_mode();

void push_pull_enter_burst_mode(bool single_shot, bool pid_mode);

void push_pull_error_handler(push_pull_error_id_t error_id, push_pull_error_caller_id_t caller_id);

void push_pull_exit_burst_mode();

void push_pull_state_machine();

bool push_pull_soft_start();
