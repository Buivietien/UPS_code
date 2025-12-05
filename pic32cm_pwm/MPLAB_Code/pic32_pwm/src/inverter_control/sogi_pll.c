#include <inverter_control/inverter.h>
#include "definitions.h"

//Define max parameter
#define max_voltage 350         //volts
#define max_frequency 51    //Hz
#define pi  3.14
#define max_radial_velocity 320.28 // Unit rad/s
#define max_output_angle 6.28 // 2*pi
#define max_sin_cos 1

//define sogi_pll q15 constant
#define Kp 9830
#define Ki 1
#define w0_Ts 1028
#define Ki_Ts 100
#define omega_0  32111
#define Theta_comp_Ts 180

#define SOGI_comp_Ts 1028
#define SOGI_k_factor 1
#define theta_max_val 32000

volatile sogi_pll_t sogi_pll_strct;

volatile offset_calc_t offset_calc_strct;

//Two hundred value in quarter cylce of sine in 16bit format


void sogi_pll(){
    //Utilize the offset elimination program:
    
    //Grabing input from ADC, this run continuously until the offset calc has gathered enough data
    if (true){
        sogi_pll_strct.v_alpha[0] = convert_in16t_q15(dc_offset_calc(read_adc_int(ACI_MCU_channel)), 4096);
    } else {
        sogi_pll_strct.v_alpha[0] = convert_in16t_q15(read_adc_int(ACI_MCU_channel) - 1962, 4096);
        // dc_offset_calc(read_adc_int(ACI_MCU_channel));
    }
    //For debugging 
    sogi_pll_strct.error[0] = sogi_pll_strct.v_alpha[0] - sogi_pll_strct.v_alpha[1];
    sogi_pll_strct.mock_v_alpha[0] = sogi_pll_strct.v_alpha[0];

    sogi_pll_strct.v_alpha[0] = sogi_pll_strct.v_alpha[1] + q15_mul(w0_Ts, (SOGI_k_factor * sogi_pll_strct.error[0] - sogi_pll_strct.v_beta[1]));
    sogi_pll_strct.v_beta[0] = sogi_pll_strct.v_beta[1] + q15_mul(w0_Ts, sogi_pll_strct.v_alpha[0]);

    sogi_pll_strct.delta_omega_intergral_hat[0] = sogi_pll_strct.delta_omega_intergral_hat[1] + q15_mul(Ki_Ts, sogi_pll_strct.v_q[0]);
    sogi_pll_strct.delta_omega_hat[0] = sogi_pll_strct.delta_omega_intergral_hat[0] + q15_mul(Kp, sogi_pll_strct.v_q[0]);

    //Limit the delta_omega_hat value so that it would not overflow the q15 value
    if (sogi_pll_strct.delta_omega_hat[0] < - omega_0){
        sogi_pll_strct.delta_omega_hat[0] = - omega_0; 
    } else if (sogi_pll_strct.delta_omega_hat[0] > omega_0){
        sogi_pll_strct.delta_omega_hat[0] = omega_0; 
    }
    
    //Calculate the estimated omega value, limit the estimated omega value to prevent overflowing in both positive and negative direction
    sogi_pll_strct.estimated_omega = sogi_pll_strct.delta_omega_hat[0] + omega_0;
    if (sogi_pll_strct.estimated_omega > 32765 ){   //This value need to revise later
        sogi_pll_strct.estimated_omega = 32765;
    } else if (sogi_pll_strct.estimated_omega < 0){
        sogi_pll_strct.estimated_omega = 0;
    }

    sogi_pll_strct.theta_hat[0] = sogi_pll_strct.theta_hat[1] + q15_mul(Theta_comp_Ts, ((q15_t)sogi_pll_strct.estimated_omega));

    //Calculated the scaled theta value and limit them:
    sogi_pll_strct.theta_scaled = sogi_pll_strct.theta_hat[0] / 160;
    
    sogi_pll_strct.v_q[0] = - q15_mul(sine_value_q15(sogi_pll_strct.theta_scaled), sogi_pll_strct.v_alpha[0]) + q15_mul(cos_value_q15(sogi_pll_strct.theta_scaled), sogi_pll_strct.v_beta[0]);
    sogi_pll_strct.v_d[0] =   q15_mul(cos_value_q15(sogi_pll_strct.theta_scaled), sogi_pll_strct.v_alpha[0]) + q15_mul(sine_value_q15(sogi_pll_strct.theta_scaled), sogi_pll_strct.v_beta[0]);
        
    //Update variables
    sogi_pll_strct.error[1] = sogi_pll_strct.error[0];
    sogi_pll_strct.v_alpha[1] = sogi_pll_strct.v_alpha[0];
    sogi_pll_strct.v_beta[1] = sogi_pll_strct.v_beta[0];
    sogi_pll_strct.delta_omega_intergral_hat[1] = sogi_pll_strct.delta_omega_intergral_hat[0];
    sogi_pll_strct.delta_omega_hat[1] = sogi_pll_strct.delta_omega_hat[0];

    //Theta overflow
    if ((sogi_pll_strct.theta_hat[0] >= theta_max_val) || (sogi_pll_strct.theta_hat[0] < 0))
    {
        sogi_pll_strct.theta_hat[0] = 0;
    }

    //Calculated the scaled theta value and limit them:
    sogi_pll_strct.theta_scaled = sogi_pll_strct.theta_hat[0] / 160;

    //Calculate the sine value of the theta
    if (sogi_pll_strct.theta_scaled >= 150){
        sogi_pll_strct.theta_sine_scaled = sogi_pll_strct.theta_scaled - 150;
    } else {
        sogi_pll_strct.theta_sine_scaled = sogi_pll_strct.theta_scaled + 50;
    }

    sogi_pll_strct.theta_hat[1] = sogi_pll_strct.theta_hat[0];
    sogi_pll_strct.v_q[1] = sogi_pll_strct.v_q[0];
    sogi_pll_strct.v_d[1] = sogi_pll_strct.v_q[0];

    

    //Output the data to DAC for mornitoring
    if (DAC_IsReady()){
        DAC_DataWrite(sogi_pll_strct.theta_hat[0] / 31);
    }

}

void sogi_pll_2(int16_t v_a_input, sogi_pll_t * sogi_strct, offset_calc_t* calc_strct){
    //Utilize the offset elimination program:
    
    //Grabing input from ADC, this run continuously until the offset calc has gathered enough data
    sogi_strct->v_alpha[0] = convert_in16t_q15(dc_offset_calc_2(v_a_input, calc_strct), 4096);

    //For debugging 
    sogi_strct->error[0] = sogi_strct->v_alpha[0] - sogi_strct->v_alpha[1];
    sogi_strct->mock_v_alpha[0] = sogi_strct->v_alpha[0];

    sogi_strct->v_alpha[0] = sogi_strct->v_alpha[1] + q15_mul(w0_Ts, (SOGI_k_factor * sogi_strct->error[0] - sogi_strct->v_beta[1]));
    sogi_strct->v_beta[0] = sogi_strct->v_beta[1] + q15_mul(w0_Ts, sogi_strct->v_alpha[0]);

    sogi_strct->delta_omega_intergral_hat[0] = sogi_strct->delta_omega_intergral_hat[1] + q15_mul(Ki_Ts, sogi_strct->v_q[0]);
    sogi_strct->delta_omega_hat[0] = sogi_strct->delta_omega_intergral_hat[0] + q15_mul(Kp, sogi_strct->v_q[0]);

    //Limit the delta_omega_hat value so that it would not overflow the q15 value
    if (sogi_strct->delta_omega_hat[0] < - omega_0){
        sogi_strct->delta_omega_hat[0] = - omega_0; 
    } else if (sogi_strct->delta_omega_hat[0] > omega_0){
        sogi_strct->delta_omega_hat[0] = omega_0; 
    }
    
    //Calculate the estimated omega value, limit the estimated omega value to prevent overflowing in both positive and negative direction
    sogi_strct->estimated_omega = sogi_strct->delta_omega_hat[0] + omega_0;
    if (sogi_strct->estimated_omega > 32765 ){   //This value need to revise later
        sogi_strct->estimated_omega = 32765;
    } else if (sogi_strct->estimated_omega < 0){
        sogi_strct->estimated_omega = 0;
    }

    sogi_strct->theta_hat[0] = sogi_strct->theta_hat[1] + q15_mul(Theta_comp_Ts, ((q15_t)sogi_strct->estimated_omega));

    //Calculated the scaled theta value and limit them:
    sogi_strct->theta_scaled = sogi_strct->theta_hat[0] / 160;
    
    sogi_strct->v_q[0] = - q15_mul(sine_value_q15(sogi_strct->theta_scaled), sogi_strct->v_alpha[0]) + q15_mul(cos_value_q15(sogi_strct->theta_scaled), sogi_strct->v_beta[0]);
    sogi_strct->v_d[0] =   q15_mul(cos_value_q15(sogi_strct->theta_scaled), sogi_strct->v_alpha[0]) + q15_mul(sine_value_q15(sogi_strct->theta_scaled), sogi_strct->v_beta[0]);
        
    //Update variables
    sogi_strct->error[1] = sogi_strct->error[0];
    sogi_strct->v_alpha[1] = sogi_strct->v_alpha[0];
    sogi_strct->v_beta[1] = sogi_strct->v_beta[0];
    sogi_strct->delta_omega_intergral_hat[1] = sogi_strct->delta_omega_intergral_hat[0];
    sogi_strct->delta_omega_hat[1] = sogi_strct->delta_omega_hat[0];

    //Theta overflow
    if ((sogi_strct->theta_hat[0] >= theta_max_val) || (sogi_strct->theta_hat[0] < 0))
    {
        sogi_strct->theta_hat[0] = 0;
    }

    //Calculated the scaled theta value and limit them:
    sogi_strct->theta_scaled = sogi_strct->theta_hat[0] / 160;

    //Calculate the sine value of the theta
    if (sogi_strct->theta_scaled >= 150){
        sogi_strct->theta_sine_scaled = sogi_strct->theta_scaled - 150;
    } else {
        sogi_strct->theta_sine_scaled = sogi_strct->theta_scaled + 50;
    }

    sogi_strct->theta_hat[1] = sogi_strct->theta_hat[0];
    sogi_strct->v_q[1] = sogi_strct->v_q[0];
    sogi_strct->v_d[1] = sogi_strct->v_q[0];

    

    //Output the data to DAC for mornitoring
    // if (DAC_IsReady()){
    //     DAC_DataWrite(sogi_pll_strct.theta_hat[0] / 31);
    // }

}

//DC offset elimination algorithm
int16_t dc_offset_calc(int16_t new_val){
    //Add new value into the sum
    // offset_calc_strct.sum =+ new_val;
    offset_calc_strct.ring_buffer[offset_calc_strct.head_index] = new_val;
    
    //Incre or update the head index:
    offset_calc_strct.head_index++;
    if (offset_calc_strct.head_index >= 110){
        offset_calc_strct.head_index = 0;
        // offset_calc_strct.valid_flag = true;
        offset_calc_strct.min_value = 32000;
        offset_calc_strct.max_value = 0;
        for (int i = 0; i < 110; i++){
            if (offset_calc_strct.ring_buffer[i] > offset_calc_strct.max_value){
                offset_calc_strct.max_value = offset_calc_strct.ring_buffer[i];
            }
            if (offset_calc_strct.ring_buffer[i] < offset_calc_strct.min_value){
                offset_calc_strct.min_value = offset_calc_strct.ring_buffer[i];
            }
        }
        offset_calc_strct.offset_val[1] = (offset_calc_strct.max_value + offset_calc_strct.min_value) / 2;
        offset_calc_strct.offset_val[0] = (offset_calc_strct.offset_val[0] * 900 + offset_calc_strct.offset_val[1] * 100) / 1000;
    }

    //Remove the old val
    // offset_calc_strct.sum =- offset_calc_strct.ring_buffer[offset_calc_strct.head_index];

    //Calulate the offset value
    return new_val - offset_calc_strct.offset_val[0];
}

int16_t dc_offset_calc_2(int16_t new_val, offset_calc_t* calc_strct){

    calc_strct->ring_buffer[calc_strct->head_index] = new_val;
    
    //Incre or update the head index:
    calc_strct->head_index++;
    if (calc_strct->head_index >= 110){
        calc_strct->head_index = 0;
        // calc_strct->valid_flag = true;
        calc_strct->min_value = 32000;
        calc_strct->max_value = 0;
        for (int i = 0; i < 110; i++){
            if (calc_strct->ring_buffer[i] > calc_strct->max_value){
                calc_strct->max_value = calc_strct->ring_buffer[i];
            }
            if (calc_strct->ring_buffer[i] < calc_strct->min_value){
                calc_strct->min_value = calc_strct->ring_buffer[i];
            }
        }
        calc_strct->offset_val[1] = (calc_strct->max_value + calc_strct->min_value) / 2;
        calc_strct->offset_val[0] = (calc_strct->offset_val[0] * 900 + calc_strct->offset_val[1] * 100) / 1000;
    }

    //Calulate the offset value
    return new_val - calc_strct->offset_val[0];
}

q15_t sine_value_q15(uint16_t index){
    uint8_t quadrant = index / 50;
    quadrant = quadrant % 4; //Ensure there are only 4 quadrant: 0, 1, 2, 3
    index = index % 50;
    switch (quadrant){
        case 0:
            return sineLookupTable_q15[index];
        case 1:
            return sineLookupTable_q15[50 - index];
        case 2:
            return - sineLookupTable_q15[index];
        case 3:
            return - sineLookupTable_q15[50 - index];
    }
    return 0;
}

q15_t cos_value_q15(uint8_t index){
    return sine_value_q15(index + 50); //Because cosine is 90 degree phase lead vs sine
}