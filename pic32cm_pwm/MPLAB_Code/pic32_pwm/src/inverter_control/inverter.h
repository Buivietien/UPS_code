#pragma once
#include <inverter_control/relay.h>
#include <inverter_control/adc.h>
#include <printf_custom/printf.h>
#include <pid_controller/pid_control.h>
#include "definitions.h"

typedef enum spwm_output_mode{
    spwm_output_sine = 0,
    spwm_output_duty,
} spwm_output_mode_t;

typedef struct sogi_pll {
    q15_t v_alpha[2];
    q15_t mock_v_alpha[2];
    q15_t error[2];
    q15_t v_beta[2];
    q15_t delta_omega_intergral_hat[2];
    q31_t delta_omega_hat[2];
    q31_t estimated_omega;
    q15_t theta_hat[2]; //Theta goes from 0 to 32000. Scaled backdown to 200 to use as phase index
    uint8_t theta_scaled;
    uint8_t theta_sine_scaled;
    q15_t v_q[2];
    q15_t v_d[2];
} sogi_pll_t;

typedef struct offset_calc {
    bool valid_flag;
    q31_t sum;
    int16_t offset_val[2];
    uint8_t head_index;
    int16_t ring_buffer[110];
    int16_t min_value;
    int16_t max_value;
} offset_calc_t;

extern volatile q15_t sineLookupTable_q15[52];

bool inv_gate_driver_turn_on_reset();
void inv_gate_driver_turn_off();
uint8_t gate_driver_status();
void spwm_manual_change_duty_cycle(uint8_t duty_cycle);
void spwm_change_output_mode(spwm_output_mode_t mode);
void inv_spwm_start();
void inv_spwm_stop();
void inv_spwm_init();
void inv_spwm_manual_start();
void inv_spwm_manual_stop();

void inv_set_deadtime(float nanosec);
void inv_set_freq(uint8_t ac_freq);
void inv_set_ma(float ma_factor);
void set_spwm_rejection_duty_cycle(uint8_t reject_duty);

// void calculate_main_ac();

// float calculate_RMS_value();

void test_ups(uint8_t skip_phase, bool mock_main_status, bool restart_sine);
int sine_wave_base(int16_t index);
int sine_wave(int16_t index);
int inv_sine_wave(int16_t index);
void inverter_state_machine();

void update_compare_channel( uint32_t status, uintptr_t context );

void inverter_fault_isr(uint32_t status, uintptr_t context);

//SOGI_PLL
extern volatile sogi_pll_t sogi_pll_strct;
extern volatile offset_calc_t offset_calc_strct;
void sogi_pll();
void sogi_pll_2(int16_t v_a_input, sogi_pll_t * sogi_strct, offset_calc_t* calc_strct);
int16_t dc_offset_calc_2(int16_t new_val, offset_calc_t* calc_strct);
int16_t dc_offset_calc(int16_t new_val);
q15_t sine_value_q15(uint16_t index);
q15_t cos_value_q15(uint8_t index);