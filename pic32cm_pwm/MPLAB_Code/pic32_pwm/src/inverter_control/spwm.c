#include <inverter_control/inverter.h>
#include "config/default/peripheral/tcc/plib_tcc0.h"
#include "definitions.h"
#include <math.h>
#include <stdlib.h>
#include "xc.h"
#include <pid_controller/pid_control.h>
#include <push_pull_control/push_pull_ctrl.h>

typedef enum {
    inv_off = 0,
    inv_starting_up,
    inv_relay_on_delay,
    inv_outputting,
    inv_grid_connecting,
    inv_error,
} inverter_status_enum_t;

typedef enum inv_gate_driver_status{
    inv_gate_driver_FAULT = 0,
    inv_gate_driver_FREEZE = 1,
    inv_gate_driver_SHUTDOWN = 2,
    inv_gate_driver_NORMAL = 3,
} inv_gate_driver_status_t;
struct inv_gate_driver{
    inv_gate_driver_status_t status; 
} inv_gate_driver_strc;


spwm_output_mode_t output_mode = spwm_output_sine;
struct {
    uint16_t cc0_val;
    uint16_t cc1_val;
    uint16_t per_val;
    uint8_t current_duty;
} spwm_duty_output_struct;

typedef enum {
    grid_loss,
    grid_stable,
    grid_unstable,
    main_collecting,
} main_AC_status_t;

#define number_of_sample 10
#define grid_data_sample_number 200
#define main_ac_buffer_number 5
struct spwm_control_variable_struct {
    int adc_aco_voltage[number_of_sample];
    int adc_current[number_of_sample];
    int aco_voltage_error[number_of_sample];
    int current_error[number_of_sample];
    int set_voltage;
    float set_current;
    float ma_factor;
    float P_voltage;
    float I_voltage;
    float P_current;
} spwm_control_variable;

struct ups_test{
    uint8_t sine_index;
    bool main_ok;
} mock_test_ups = {0, true};

struct grid_loss{
    uint8_t grid_on_delay_time;
} grid_loss_strct;

struct main_collecting{
    int16_t voltage_ratio_data[grid_data_sample_number];
    uint8_t theta_0_count;
    uint8_t collecting_index;
    uint32_t sum;
    int16_t current_sine;
    q15_t voltage_ratio;
    q15_t voltage_ratio_average;
    int16_t intemediate_val;
    int16_t intemediate_val_2;
    int16_t regen_ref_sine;
} main_collecting_strct;

struct grid_stable {
    int16_t regen_ref_sine;
    int16_t error;
    int16_t grid_voltage;
    uint8_t grid_loss_index;
    uint16_t loss_counter;
    uint16_t gridloss_blanking_time;
} grid_stable_strct;

struct inv_relay_on_delay {
    uint32_t time;
    bool gate_driver_switch;
} inv_relay_on_delay_trct;

struct inv_outputting {
    pid_control_q15_t pid_ma;
    sogi_pll_t sogi;
    offset_calc_t ac_offset;
    int16_t grid_voltage;
} inv_outputting_strct;

struct inv_grid_connecting {
    int16_t phase_difference;
    uint16_t correct_phase_counter;
    uint16_t min_runtime;
} inv_grid_connecting_strct;

struct inv_error {
    uint8_t error_count;
} inv_error_strct;

static volatile uint8_t sine_lookup_index = -1;
volatile uint8_t quadrant = 1;
volatile uint8_t inv_quadrant = 1;

// volatile uint8_t inverter_state = inverter_off;

bool inverter_enable = false;
uint8_t pwm_reject_cc_value = 1;
int16_t _main_AC_data_buffer_[main_ac_buffer_number][grid_data_sample_number];
uint8_t main_ac_data_buffer_index = 0;
bool main_ac_calculation_ready = false;
uint8_t aci_sample_index = 0; 
uint8_t main_AC_index = 0;
uint8_t main_AC_sample_round = 0; 
uint8_t zero_cross_index = 0;

struct AC_grid_state{
    bool auto_switch;
    main_AC_status_t AC_grid_main_status;
} AC_grid_state_strc;



int16_t probe_variable = 0;
int16_t probe_variable_2 = 0;
int16_t probe_variable_3 = 0;
uint8_t AC_grid_time_period = 0;
float AC_grid_frequency = 0;

struct Inv_grid_state{
    bool auto_switch;
    inverter_status_enum_t inverter_status;  
} inv_state_strct;

uint32_t inv_runtime_count = 0;
int16_t phase_difference = 0;

bool inverter_manual_mode = false;

float grid_Vol_RMS_value = 0.0;
float grid_Cur_RMS_value = 0.0;

static volatile uint16_t base_sineLookupTable[52] = {
1200, 1238, 1275, 1313, 1350, 1388, 1425, 1462, 1498, 1535,
1571, 1606, 1642, 1677, 1711, 1745, 1778, 1811, 1843, 1875,
1905, 1935, 1965, 1994, 2021, 2049, 2075, 2100, 2125, 2148,
2171, 2192, 2213, 2233, 2252, 2269, 2286, 2301, 2316, 2329,
2341, 2352, 2362, 2371, 2379, 2385, 2391, 2395, 2398, 2399,
2399, 2400};

static volatile uint16_t sineLookupTable[52] = {
1200, 1238, 1275, 1313, 1350, 1388, 1425, 1462, 1498, 1535,
1571, 1606, 1642, 1677, 1711, 1745, 1778, 1811, 1843, 1875,
1905, 1935, 1965, 1994, 2021, 2049, 2075, 2100, 2125, 2148,
2171, 2192, 2213, 2233, 2252, 2269, 2286, 2301, 2316, 2329,
2341, 2352, 2362, 2371, 2379, 2385, 2391, 2395, 2398, 2399,
2399, 2400};

//The 50th is lowest, the 51st is the highest value
static volatile uint16_t mock_adc_sineLookupTable[52] = {
2048, 2112, 2177, 2241, 2305, 2368, 2432, 2495, 2557, 2619,
2681, 2742, 2802, 2861, 2920, 2978, 3035, 3091, 3145, 3199,
3252, 3303, 3353, 3402, 3450, 3496, 3541, 3584, 3626, 3666,
3705, 3742, 3777, 3811, 3843, 3873, 3901, 3928, 3952, 3975,
3996, 4015, 4032, 4047, 4060, 4071, 4080, 4087, 4092, 4095,
4096, 4096, 4096};

//q15 representation of sine table (From 0.0 to 1.0)
volatile q15_t sineLookupTable_q15[52] = {
    0, 1029, 2057, 3083, 4106, 5125, 6140, 7148, 8148, 9141,
    10125, 11099, 12062, 13013, 13951, 14876, 15785, 16680, 17557, 18418,
    19260, 20083, 20886, 21669, 22430, 23170, 23886, 24579, 25247, 25891,
    26509, 27101, 27666, 28204, 28714, 29196, 29648, 30072, 30466, 30830,
    31163, 31466, 31738, 31978, 32187, 32364, 32509, 32622, 32702, 32751,
    32766, 32767
};

struct sine_table_generation{
    q15_t sine_ma_factor;
    uint16_t tcc0_per_val;

} sine_table_generation_strct;

uint8_t deadtime_count = 48;
//volatile int temp_inv_sine_wave_val;
volatile int cc0_value = 0;
volatile int cc1_value = 0;


bool inv_gate_driver_turn_on_reset(){
    //Turn off the EIC Interrupt here to prevent push pull from inadvertedly turned off:
    // EIC_InterruptDisable(0);
    //Configure the fault/sd pin to be Output pin:
    // PORT_REGS->GROUP[0].PORT_PINCFG[16] &= ~0x1 << 0;

    // inv_nSYS_FLT_OutputEnable();
    // inv_nSYS_FLT_Set();
    inv_nSYS_FLT_InputEnable(); //Release the pin.
    
    // inv_FAULT_SD_OutputEnable();
    // inv_FAULT_SD_Set();
    inv_FAULT_SD_InputEnable();
    
    inv_FAULT_CLR_OutputEnable();
    inv_FAULT_CLR_Set(); //Well turns out you have to leave the CLR a little bit longer.
    SYSTICK_DelayMs(1); //Just leave it here before I figure out the async pin functions
    inv_FAULT_CLR_Clear();
    // inv_FAULT_CLR_InputEnable(); //High impedance mode to release the pin
    
    //Report back the status
    // gate_driver_status();

    //Configure the fault/sd pin to be EIC pin
    // PORT_REGS->GROUP[0].PORT_PINCFG[16] |= 0x1 << 0;
    //Turn on the EIC interrupt here
    // EIC_InterruptEnable(0); 
    
    //Return the gate driver FLT/CLR pin status (1 means ok, 0 means fault).
    return inv_FAULT_SD_Get();
}

void inv_gate_driver_turn_off(){
    //Turn off the EIC Interrupt here to prevent push pull from inadvertedly turned off:
    EIC_InterruptDisable(0);
    //Configure the fault/sd pin to be Output pin: (PORT functionality)
    PORT_REGS->GROUP[0].PORT_PINCFG[10] &= ~0x1 << 0;

    inv_FAULT_SD_OutputEnable();
    inv_nSYS_FLT_OutputEnable();
    inv_FAULT_SD_Clear();
    inv_nSYS_FLT_Clear();
    SYSTICK_DelayMs(1); //Just leave it here before I figure out the async pin functions
    // inv_nSYS_FLT_InputEnable(); //Commented these because I want to keep IR2214 disabled when not inused. 
    // inv_FAULT_SD_InputEnable();
    //Report back the status
    gate_driver_status();

    //Configure the fault/sd pin to be EIC pin (EIC Functionality). Note: Keep this pin as PORT functionality so IR2214 is not outputting.
    // PORT_REGS->GROUP[0].PORT_PINCFG[16] |= 0x1 << 0;
    //Turn on the EIC interrupt here
    EIC_InterruptEnable(0); 
}

uint8_t gate_driver_status(){
    //Configure the fault/sd pin to be Output pin: (PORT functionality)
    // PORT_REGS->GROUP[0].PORT_PINCFG[16] &= ~0x1 << 0;

    uint8_t FLT_sd = inv_FAULT_SD_Get();
    uint8_t SYS_flt = inv_nSYS_FLT_Get();
    inv_gate_driver_strc.status = FLT_sd | SYS_flt << 1;
    // switch (status)
    // {
    // case inv_gate_driver_NORMAL:
    //     printf("Gate driver normal\n");
    //     break;
    // case inv_gate_driver_SHUTDOWN:
    //     printf("Gate driver shutdown\n");
    //     break;
    // case inv_gate_driver_FREEZE:
    //     printf("Gate driver FREEZE\n");
    //     break;
    // case inv_gate_driver_FAULT:
    //     printf("Gate driver faulted\n");
    //     break;
    // default:
    //     printf("No data: %d \n", status);
    //     break;
    // }

    //Return the gate driver status
    return inv_gate_driver_strc.status;
    //Configure the fault/sd pin to be EIC pin (EIC Functionality)
    // PORT_REGS->GROUP[0].PORT_PINCFG[16] |= 0x1 << 0;

}

void inv_spwm_init(){
    //Reset Compare channel value to 0
    TCC0_REGS->TCC_CC[0] = 0U; 
    TCC0_REGS->TCC_CC[1] = 0U; 
    TCC0_REGS->TCC_CC[2] = 0U;
    TCC0_REGS->TCC_CC[3] = 0U;
    TCC1_REGS->TCC_CC[0] = 0U;
    TCC1_REGS->TCC_CC[1] = 0U;
    
    //Set up continous sampling for pin Fault/SD (PA16):
    PORT_REGS->GROUP[0].PORT_CTRL != 0x1 << 16;

    //Enable the input buffer for pin Fault/SD (PA16):
    PORT_REGS->GROUP[0].PORT_PINCFG[10] |= 0x1 << 1;

    //Register the fault pin isr to the EIC interrupt here:
    EIC_CallbackRegister(0, inverter_fault_isr, 0);
    EIC_InterruptEnable(0); //Enable the interrupt on EIC pin 0

    //Configure the fault/sd pin to be EIC pin
    PORT_REGS->GROUP[0].PORT_PINCFG[10] |= 0x1 << 0;

    //Initialize the AC output PID working params here:
    inv_outputting_strct.pid_ma.normalizing_val = 32767; //Set this as max of q15 because ma inself is also q15 value
    inv_outputting_strct.pid_ma.max_output = 32767;
    inv_outputting_strct.pid_ma.min_output = 0;
    inv_outputting_strct.pid_ma.windup_error_thres = 10000;
    inv_outputting_strct.pid_ma.kp = 10000; //This convert to kp = 0.3
    inv_outputting_strct.pid_ma.ki = 100; //Set the Ki value to be extremely small: Ki = 0.003
    inv_outputting_strct.pid_ma.setpoint = 10000; //This should be set equals to the norminal v_d value. At 310V AC input, this setpoint equals: 13635 (((310 / 149)) / 5 * 32768) (Because Vd also minus the dc offset)


    //Register the update_compare ISR 
    TCC0_PWMCallbackRegister(update_compare_channel, 0);
    TCC0_PWMPeriodInterruptEnable();
    //Enable the tcc0 timer to run continuously.
    inv_spwm_stop();
    TCC0_PWMStart();

    //Initialize the state machine initial states:
    inv_state_strct.auto_switch = true;
    inv_state_strct.inverter_status = inv_off;

    AC_grid_state_strc.auto_switch = true;
    AC_grid_state_strc.AC_grid_main_status = grid_stable;

    //Initial the SSR relay, default state is the Grid is connected
    grid_connect_relay_turn_on();

    //Turn on the bypass relay here to prevent the 15V VCC being pulled low by this relay:
    bypass_relay_turn_on();
}

void inv_spwm_manual_start(){
    //Start the PWM Generation manually
    set_inverter_status(inv_off); //Stop inverter auto from running. 
    inverter_manual_mode = true;
    inv_spwm_start();
}

void inv_spwm_manual_stop(){
    //Stop the PWM Generation manually
    inverter_manual_mode = false;
    set_inverter_status(inv_off); //This is to flush inverter pending actions, prevent trying to grid connect when go back to auto mode
    inv_spwm_stop();
}

//This function to manually set the duty cycle for IGBT to test varying load
void spwm_manual_change_duty_cycle(uint8_t duty_cycle){
    if (duty_cycle < 0 || duty_cycle > 100){
        printf("Wrong duty cycle value, exiting\n");
        return;
    }
    //Change the output mode to duty cycle 
    spwm_change_output_mode(spwm_output_duty);

    //Save the current duty cycle and calculate the count value for CC channels.
    spwm_duty_output_struct.current_duty = duty_cycle;
    spwm_duty_output_struct.per_val = TCC0_PWM24bitPeriodGet();
    spwm_duty_output_struct.cc0_val = (spwm_duty_output_struct.per_val * (spwm_duty_output_struct.current_duty)) / 100;
    spwm_duty_output_struct.cc1_val = (spwm_duty_output_struct.per_val * (spwm_duty_output_struct.current_duty)) / 100;
}

void spwm_change_output_mode(spwm_output_mode_t mode){
    switch (mode)
    {
        case spwm_output_duty:
            //Change the SWAP setting to turn off the opposite LOW SIDE IGBT to prevent capacitor discharge:
            //More specifically, S2 and S3 will swap, meaning the LOW SIDE will be off when CC1 output is High. (Because CC1 output is equals to LOW Side output)
            TCC0_REGS->TCC_WAVE |= TCC_WAVE_SWAP1_Msk;

            //Wait for WAVE register synchronization
            while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_WAVE_Msk != 0U){
                //Do nothing here
            }
        break;
        
        case spwm_output_sine:
            //Turn off the swap function so TCC0 can output sine normally:
            TCC0_REGS->TCC_WAVE &= ~TCC_WAVE_SWAP1_Msk;

            //Wait for WAVE register synchronization
            while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_WAVE_Msk != 0U){
                //Do nothing here
            }
        break;

    }
    output_mode = mode;
}

void inv_spwm_start(){
    //Start the PWM Generation
    TCC0_PWMStop();
    inverter_enable = true;
    TCC0_REGS->TCC_DRVCTRL &= ~TCC_DRVCTRL_INVEN4_Msk;
    TCC0_REGS->TCC_DRVCTRL &= ~TCC_DRVCTRL_INVEN5_Msk;
    // printf("SPWM Started\n");
    TCC0_PWMStart();
}

void inv_spwm_stop(){
    TCC0_PWMStop(); //Keep the tcc0 timer running continuously to mornitor the grid. 
    inverter_enable = false;
    //Invert the output of Output 4 and 5 to turn these off (LOW).
    TCC0_REGS->TCC_DRVCTRL |= TCC_DRVCTRL_INVEN4_Msk;
    TCC0_REGS->TCC_DRVCTRL |= TCC_DRVCTRL_INVEN5_Msk;
    // printf("SPWM Stopped\n");
    TCC0_PWMStart();
}

void inv_set_deadtime(float nanosec){
    //The deadtime bits are enable-protected, so I have to stop TCC, change the deadtime, and reenable it. NOT RESETTING!!
    //Implement deadtime via software
    deadtime_count = nanosec*24 / 500; //This is because at 4800 count = 100uS (The peripheral clock is 48 Mhz), therefore 1uS = 48 count and 500nS = 24 count.
    printf("Deadtime set: %f nS\n", nanosec); 
    printf("Deadtime period: %d count\n", deadtime_count); 
    TCC0_PWMStop();
    TCC0_PWMDeadTimeSet(deadtime_count, deadtime_count);
    if (deadtime_count < 24) { //Minimum 24 counts, equals: 500nS
        deadtime_count = 24;
        TCC0_PWMDeadTimeSet(deadtime_count, deadtime_count);
        printf("To low, Deadtime default: 500nS");
    }
    //Re-enable the TCC0 to load the new deadtime
    TCC0_PWMStart();
    return;
}

//Deprecated! Do not use this function to change output inverter frequency!
void inv_set_freq(uint8_t ac_freq){
    /* The frequency of the output AC is control by changing tcc0 PER value
    The PER is calculated as followed:
    clock / (ac_freq * 200)
    Explain: since there is 200 samples total in the sine_lookup_table
    This corresponds to each ramp cycle of tcc0_count
    So by changing the count, the frequency of tcc0 is changed and also the AC output frequency. 
    */
    uint32_t current_tcc0_per = (uint32_t)TCC0_PWM24bitPeriodGet;
    printf("Current PER: %l \n", current_tcc0_per);
    uint32_t new_tcco_0_per_val = (240000 / ac_freq) / 2;
    printf("New PER: %l \n", new_tcco_0_per_val);

    //Calculate the compensation for lookup table
    float ratio = current_tcc0_per / new_tcco_0_per_val;
    for (int i = 0; i < 51; i++){
        sineLookupTable[i] *= ratio;
        base_sineLookupTable[i] *= ratio;
    }
    //Put the new TCC0 PER value into the double buffer.
    TCC0_REGS->TCC_PERBUF = TCC_PERBUF_PERBUF(new_tcco_0_per_val);
    //Well, the datasheet recommend waiting for synchronization
    while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PER_Msk != 0U)
    {
        /* Wait for sync */
    } 
    return;
}

void update_sine_lookup_table(){
    sine_table_generation_strct.tcc0_per_val = TCC0_PWM24bitPeriodGet();

    //Update the sine table with the updated ma factor
    q15_t sine_with_ma;
    for (int i = 0; i < 52; i++){
        sine_with_ma = q15_mul(sine_table_generation_strct.sine_ma_factor, sineLookupTable_q15[i]);
        sineLookupTable[i] = ( sine_table_generation_strct.tcc0_per_val / 2 ) + convert_q15_int16t(sine_with_ma, sine_table_generation_strct.tcc0_per_val / 2); 
    }
}

void inv_set_ma(float ma_factor){
    //Set up the ma factor here and then update the sine_loopup_table with the new ma factor
    sine_table_generation_strct.sine_ma_factor = convert_float_q15(ma_factor, 1);
    
    //Update the sine lookup table here for efficiency.
    update_sine_lookup_table();
}
//Important: This is the control loop for calculating the ma value for the inverter and frequency matching.
void inv_control_loop(){
    //Record measured value from ADC to control varible:
    // for (int i = 0; i < number_of_sample; i++){
    //     spwm_control_variable.adc_current[i + 1] = spwm_control_variable.adc_current[i];
    //     spwm_control_variable.adc_aci_voltage[i + 1] = spwm_control_variable.adc_aci_voltage[i];
    //     spwm_control_variable.current_error[i + 1] = spwm_control_variable.current_error[i];
    //     spwm_control_variable.aco_voltage_error[i + 1] = spwm_control_variable.aco_voltage_error[i];
    // }
    // spwm_control_variable.adc_current[0] = read_adc(AC_Current_MCU_channel);
    // spwm_control_variable.adc_aci_voltage[0] = read_adc(ACI_MCU_channel);
    // spwm_control_variable.adc_aco_voltage[0] = read_adc(ACO_MCU_channel);
    

}

void set_inverter_status(inverter_status_enum_t status){
    // return; //Disable auto status switcher
    if (!inv_state_strct.auto_switch){
        return; //Disable the auto swich status
    }
    static uint8_t notify_once = 0;
    //Lock the status of the inverter due to manual mode
    if (inverter_manual_mode == true){
        if (notify_once < 1){
            printf("Inverter manual mode is active, turn off for auto\n");
            notify_once++;
        }
        return;
    } else {
        notify_once = 0;
    }
    // if (inv_runtime_count - set_runtime > 100){ //This is here so that spurious inverter control signal can not damage the system. Currently not implemented

    // }
    inv_state_strct.inverter_status = status;
    return;
}

void set_grid_main_status(main_AC_status_t status){
    // return; //Stop automatic state change
    if (!AC_grid_state_strc.auto_switch){
        return;
    }
    AC_grid_state_strc.AC_grid_main_status = status;
}

// float calculate_RMS_value(){
//     uint32_t sum_of_square = 0;
//     uint8_t num_sample = 100;
//     if (AC_grid_state_strc.AC_grid_main_status == grid_stable){
//         for (int i = 0; i < num_sample; i++){ //Only need half sine cycle, to save memories
//             sum_of_square += main_AC_data[i] * main_AC_data[i];           
//         }
//         grid_Vol_RMS_value = sqrt(sum_of_square / num_sample);
//         printf("RMS voltage val: %.2f\n", grid_Vol_RMS_value);
//         return grid_Vol_RMS_value;
//     } else {
//         printf("Error, grid data incomplete\n");
//         return 0.0;
//     }
// }

void test_ups(uint8_t skip_phase, bool mock_main_status, bool restart_sine){
    if (restart_sine == true){
        mock_test_ups.sine_index = 0;
    } else {
        mock_test_ups.sine_index += skip_phase;
    }
    mock_test_ups.main_ok = mock_main_status;
}

int16_t test_ups_sine_table(uint8_t index){
    uint8_t manual_quadrant = index / 50;
    if (manual_quadrant > 3) manual_quadrant = 0;
    index = index % 50;
    switch (manual_quadrant){
        case 0:
            return mock_adc_sineLookupTable[index];

        case 1:
            return mock_adc_sineLookupTable[49 - index];
            
        case 2:
            return mock_adc_sineLookupTable[51] - mock_adc_sineLookupTable[index];
          
        case 3:
            return mock_adc_sineLookupTable[51] - mock_adc_sineLookupTable[50 - index];
    }
    return 0;
}

//Generate sine value for index 0 to 200. Auto or Manual 
int sine_wave(int16_t index){
    uint8_t manual_quadrant = index / 50;
    manual_quadrant %= 4;
    index = index % 50;
    switch (manual_quadrant){
        case 0:
            return sineLookupTable[index];

        case 1:
            return sineLookupTable[50 - index];
            
        case 2:
            return sineLookupTable[51] - sineLookupTable[index];
          
        case 3:
            return sineLookupTable[51] - sineLookupTable[50 - index];
    }
    return 0;
}

int sine_wave_base(int16_t index){
    uint8_t manual_quadrant = index / 50;
    manual_quadrant %= 4;
    index = index % 50;
    switch (manual_quadrant){
        case 0:
            return base_sineLookupTable[index];

        case 1:
            return base_sineLookupTable[50 - index];
            
        case 2:
            return base_sineLookupTable[51] - base_sineLookupTable[index];
          
        case 3:
            return base_sineLookupTable[51] - base_sineLookupTable[50 - index];
    }
    return 0;
}


int inv_sine_wave(int16_t index){
    uint8_t manual_quadrant = index / 50;
    manual_quadrant %= 4;
    index = index % 50;
        switch (manual_quadrant){
            case 0:                
                return (sineLookupTable[51] - sineLookupTable[index]);               
            case 1:
                return sineLookupTable[51] - sineLookupTable[50 - index]; //Note: sineLookupTable[51] is the max value
            case 2:
                return sineLookupTable[index];
            case 3:
                return sineLookupTable[50 - index];
        }
    return 0;
}
void set_spwm_rejection_duty_cycle(uint8_t reject_duty){
    if (reject_duty >= 100){
        return;
    }
    pwm_reject_cc_value =  (2400 * reject_duty / 2) / 100;
    return;
}

// void calculate_main_ac(){
//     //Calculate the main_ac information here to relieve the adc interrupt line. 
//     if (main_ac_data_buffer_index >= main_ac_buffer_number - 1){
//         for (int i = 0; i < grid_data_sample_number; i++){
//             for (int j = 0; j < main_ac_buffer_number; j++){
//                 main_AC_data[i] = ( main_AC_data[i] + _main_AC_data_buffer_[j][i] ) / 2;
//             }
//         } 
//         //Reset the relevant variables
//         main_ac_calculation_ready = true;
//         main_ac_data_buffer_index = 0;

//         //Looking for the next zero crossing point to determine frequency
//         for (int i = 2; i < grid_data_sample_number; i++){
//             if ((main_AC_data[i] <= 0) && (main_AC_data[i -1] >= 0)){
//                 AC_grid_time_period = i; //Because the point where is data is taken overshot the actual zero crossing by 1 point. Well, actually no because the initial point is alrready overshot 1 point
//                 break;
//             }
//         }
//         bool crossing_detected_switch = false;
//         //Improve the frequency accuracy by measurring the other half too
//         for (int i = AC_grid_time_period + 5; i < grid_data_sample_number; i++){
//             if ((main_AC_data[i] >= 0) && (main_AC_data[i - 1] <= 0)){
//                 crossing_detected_switch = true;
//                 AC_grid_time_period = i;
//                 break;
//             }
//         }

//         // printf("Max_index: %d, min_index: %d, delta: %d\n", max_index, min_index, min_index - max_index);

//         // AC_grid_time_period--; //Compensate for excess read index, The zero crossing point is the point before. 
//         if (crossing_detected_switch == true){
//             AC_grid_frequency = (1.0 / AC_grid_time_period) * 10000.0; //Because the time is only between half cycle. So I need to divide by 2. 
//         } else {
//             AC_grid_frequency = (1.0 / (AC_grid_time_period)) * 5000.0;
//         }
        
//     }
// }

//This run after the ADC finished sampling the input values
void inverter_state_machine(){
    //Check execution time:
    // LED_D8_Set();

    //This is to test the UPS functionality
    //This is to generate a mock sine signal
    // if (mock_test_ups.main_ok == true){
    //     adc_aci_voltage[aci_sample_index++] = test_ups_sine_table(mock_test_ups.sine_index++) - test_ups_sine_table(0) + rand() % 100;
    // } else {
    //     adc_aci_voltage[aci_sample_index++] = 0;
    //     mock_test_ups.sine_index++;
    // }

    //Put the SOGI_PLL algorithm here:
    sogi_pll();

    //Continuously mornitor gate driver status:
    gate_driver_status();

    //Set real ADC value in here
    // adc_aci_voltage[aci_sample_index++] = read_adc_int(ACI_MCU_channel) - 1969; //Get the ACI ADC value and minus the offset
    // if (aci_sample_index > grid_data_sample_number - 1) aci_sample_index = 0;

    // probe_variable = adc_aci_voltage[aci_sample_index - 1];
    // if (mock_test_ups.sine_index > grid_data_sample_number - 1) mock_test_ups.sine_index = 0;

    switch (AC_grid_state_strc.AC_grid_main_status)
    {
    case grid_loss:
        grid_loss_strct.grid_on_delay_time++;
        if ((sogi_pll_strct.v_d[0] > 5000) && (grid_loss_strct.grid_on_delay_time > 100)){ //This threshold is choosen arbitrarily
            set_grid_main_status(grid_unstable);
            // printf("High voltage detected\n");
        }
        break;

    case grid_unstable:
        //Wait until vq is almost zero for 10 consecutive time for the grid to be stable and phase is captured
        if (abs(sogi_pll_strct.v_q[0]) < 2000){
            set_grid_main_status(main_collecting);
            main_collecting_strct.theta_0_count = 0;
        }

        //If the grid is stable, turn to that state 
        break;
    case main_collecting:
        //New algorithm, compute the ratio between incoming grid AC power compare to internal Q15 grid information and use that for reference
        //Compute 10 value to grab the correct ratio
        main_collecting_strct.current_sine = sine_wave_base(sogi_pll_strct.theta_sine_scaled) - 1200;
        main_collecting_strct.intemediate_val = read_adc_int(ACI_MCU_channel) - offset_calc_strct.offset_val[0];
        main_collecting_strct.intemediate_val_2 = ( main_collecting_strct.intemediate_val * 1000 ) / (sine_wave_base(sogi_pll_strct.theta_sine_scaled) - 1200);

        if ((main_collecting_strct.intemediate_val_2 > 0) && (sogi_pll_strct.theta_sine_scaled > 40) && (sogi_pll_strct.theta_sine_scaled < 70)){
            main_collecting_strct.voltage_ratio = main_collecting_strct.intemediate_val_2;
            main_collecting_strct.voltage_ratio_data[main_collecting_strct.collecting_index++] = main_collecting_strct.voltage_ratio;
        }
        if (main_collecting_strct.collecting_index >= 200){
            main_collecting_strct.sum = 0;
            for (int i = 0; i < 200; i++){
                main_collecting_strct.sum += main_collecting_strct.voltage_ratio_data[i];
            }
            main_collecting_strct.voltage_ratio_average = main_collecting_strct.sum / 200;
            main_collecting_strct.collecting_index = 0;
            set_grid_main_status(grid_stable);
        }   
        break;
    
    case grid_stable:
        //Regenerate the sine to see if it matches the grid voltage:
        grid_stable_strct.regen_ref_sine = offset_calc_strct.offset_val[0] +  ((sine_wave_base(sogi_pll_strct.theta_sine_scaled) - 1200) * main_collecting_strct.voltage_ratio_average )/ 1000;
        grid_stable_strct.grid_voltage = read_adc_int(ACI_MCU_channel);
        if (inv_state_strct.inverter_status == inv_outputting){
            //If the inverter is already running, set its running status to connecting to connect back to the grid
            set_inverter_status(inv_grid_connecting);
        }

        // if (DAC_IsReady()){
        //     DAC_DataWrite(offset_calc_strct.offset_val[0] / 3);
        //     probe_variable = grid_stable_strct.regen_ref_sine / 3;
        // }

        //Set the blanking time to 1s to prevent spurious grid_loss activation:
        if (grid_stable_strct.gridloss_blanking_time < 10000){
            grid_stable_strct.gridloss_blanking_time++;
            break;
        }

        grid_stable_strct.error = abs(grid_stable_strct.grid_voltage - grid_stable_strct.regen_ref_sine);
        if ((grid_stable_strct.error > 300) || (sogi_pll_strct.v_d[0] < 2000)){ //If the error is more than 20% different compared to the reference value, indicate the grid loss. Added condition to check for voltage amplitude.
            //Count the amount of time grid is loss continuously
            if (grid_stable_strct.loss_counter < 5){
                grid_stable_strct.loss_counter++;
                break;
            }
            
            //Main is lost
            grid_stable_strct.grid_loss_index = sogi_pll_strct.theta_sine_scaled;
            // printf("Grid is loss\n");
            set_grid_main_status(grid_loss);

            //This delay is wait for the v_d finally settling to zero
            grid_loss_strct.grid_on_delay_time = 0;

            //Reset the loss_counter value here
            grid_stable_strct.loss_counter = 0;

            // printf("Starting up inverter\n");
            if (inv_state_strct.inverter_status != inv_outputting){
                set_inverter_status(inv_starting_up);
            }
        } 
        break;

    default:
        break;
    }
    
    switch (inv_state_strct.inverter_status){
        case inv_off: //Turn off the inverter output part
            if (inverter_enable == true && inverter_manual_mode == false){
                inv_spwm_stop();
            }
            break;
        
        case inv_starting_up:
            //Perform system check, if inverter is already running, skip this test.
            //Check battery level
            //Starting the Push-Pull converter:
            //Check DC Link voltage
            //Turn on the bypass relay to allow full output voltage
            // bypass_relay_turn_on();
            //If everything is ok, run!
            inv_grid_connecting_strct.correct_phase_counter = 0;
            sine_lookup_index = 0;

            //Disconnect the Grid from the circuit
            grid_connect_relay_turn_off();
            inv_relay_on_delay_trct.time = 0;
            
            //Turn on the gate driver for Inverter
            if (inv_gate_driver_turn_on_reset()){ //In this already delayed by 1mS, check the status of the gate driver, change state only after gate driver is turned on successful.
                set_inverter_status(inv_relay_on_delay);
            } else {
                led_show_signal(led_push_pull_error_flash, 0, 1); //Show the led status, put the push pull error here temporily
            }
            // printf("Inverter startup completed, outputting\n");
            break;

        case inv_relay_on_delay:
            //Delay 5ms for the relay to actuate, prevent inverter back feeding to power back to the grid
            inv_relay_on_delay_trct.time++;
            //Command is run every 100uS, count this to 50 and proceeed
            if (inv_relay_on_delay_trct.time > 10){
                inv_spwm_start();
                if (inv_gate_driver_strc.status == inv_gate_driver_NORMAL){
                    set_inverter_status(inv_outputting);
                } else {
                    set_inverter_status(inv_starting_up);
                }
            }

            break;

        case inv_outputting: 
            //Mornitoring the system, hmmmm I can run the control law here. 
            //Run SOGI_PLL here to capture the AC output information
            inv_outputting_strct.grid_voltage = read_adc_int(ACO_MCU_channel);
            sogi_pll_2(inv_outputting_strct.grid_voltage, &inv_outputting_strct.sogi, &inv_outputting_strct.ac_offset);
            pid_update_Q15(inv_outputting_strct.sogi.v_d[0], 0, 3, &inv_outputting_strct.pid_ma, 0);
            
            //Continuously check the gate driver status:
            if (inv_gate_driver_strc.status != inv_gate_driver_NORMAL){
                set_inverter_status(inv_error);
                inv_error_strct.error_count = 0;
            }
            
            // sine_table_generation_strct.sine_ma_factor = inv_outputting_strct.pid_ma.output_q15;
            // update_sine_lookup_table();

            break;
        case inv_grid_connecting:
            //The aim here is to connect at index 0, right at the zero crossing!
            ; //THis is to avoid: a label can only be part of a statement and a declaration is not a statement. Link: https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
            
            //Keep the inverter running for a minimum of 5s before connecting back to the grid
            if (inv_grid_connecting_strct.min_runtime < 50000){
                inv_grid_connecting_strct.min_runtime++;
                break;
            }

            //New idea, only increment the sine_lookup_value until it match, dont minus 
            inv_grid_connecting_strct.phase_difference = sine_lookup_index - (sogi_pll_strct.theta_sine_scaled);
            if (inv_grid_connecting_strct.phase_difference != 0){
                sine_lookup_index++;
                if (sine_lookup_index >= 200) sine_lookup_index = 0;
                //Reset the counter if phase misallign.
                inv_grid_connecting_strct.correct_phase_counter = 0;
            } else { //Check for the phase match for a countinuous 100 time
                inv_grid_connecting_strct.correct_phase_counter++;
                //Detach the inverter 6.9mS before the inverter turn off, to allow time for relay to actuate.
                if ((inv_grid_connecting_strct.correct_phase_counter > 100)  && (sine_lookup_index >= 189) && (sine_lookup_index <= 135)){
                    //Reconnect the grid to the AC output here, 1mS before the actual zero-crossing since the relay is slow. 
                    grid_connect_relay_turn_on();
                }
                if ((inv_grid_connecting_strct.correct_phase_counter > 100) && (sine_lookup_index >= 198) && (grid_connect_relay_status())){ //Ensure that the relay is disconnected before turn off the inverter or else the it will trip grid loss status.
                    //Phase is matched at zero crossing point, safe to turn off the inverter. 
                    set_inverter_status(inv_off);
                    inv_spwm_stop();

                    //Reset the timer if the condition already passed
                    inv_grid_connecting_strct.min_runtime = 0;

                    //Reset the blanking time here to prevent spurious grid loss activation:
                    grid_stable_strct.gridloss_blanking_time = 0;
                }
            }

            break;

        case inv_error:
            //Handle the gate driver error status
            inv_error_strct.error_count++;
            if (inv_error_strct.error_count > 10){
                set_inverter_status(inv_off);
            }
            if (inv_gate_driver_strc.status == inv_gate_driver_NORMAL){
                set_inverter_status(inv_outputting);
            } 
            //Attempt to restart the gate driver
            // inv_gate_driver_turn_on_reset();
            // set_inverter_status(inv_off);
            break;
    }

    //Check execution time:
    // LED_D8_Clear();
}

void update_compare_channel( uint32_t status, uintptr_t context ){
    //Move the inverter state machine here to check execution time
    inverter_state_machine();
    if (inverter_enable == true){
    // if (true){ //Set to true for testing
        switch (output_mode)
        {
            case spwm_output_sine:
                //Output via DAC here for diagnostic:
                // if (DAC_IsReady()){
                //     DAC_DataWrite(sine_wave(sine_lookup_index) / 3);
                //     probe_variable = sine_wave(sine_lookup_index) / 3;
                // }
                // if (sogi_pll_strct.theta_scaled == (50)){
                //     LED_D8_Toggle();
                // }

                cc0_value = sine_wave(sine_lookup_index);
                TCC0_REGS->TCC_CCBUF[0] = TCC_CCBUF_CCBUF(cc0_value);
        
                cc1_value = inv_sine_wave(sine_lookup_index++);
                if (sine_lookup_index > 199) sine_lookup_index = 0;
                TCC0_REGS->TCC_CCBUF[1] = TCC_CCBUF_CCBUF(cc1_value);
                break;
            
            case spwm_output_duty:
                TCC0_REGS->TCC_CCBUF[0] = TCC_CCBUF_CCBUF(spwm_duty_output_struct.cc0_val);
                TCC0_REGS->TCC_CCBUF[1] = TCC_CCBUF_CCBUF(spwm_duty_output_struct.cc1_val);
                break;
        }

        while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CC0_Msk != 0U)
        {
            /* Wait for sync */
        } 
    } else { //Turn off the output
        TCC0_REGS->TCC_CCBUF[0] = TCC_CCBUF_CCBUF(0);
        TCC0_REGS->TCC_CCBUF[1] = TCC_CCBUF_CCBUF(0);
        while (TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CC0_Msk != 0U)
        {
            /* Wait for sync */
        } 
    }
    //State machine of the inverter:

    //State determine function:


    //Loss of grid
    //Flash the led 3 times all leds to indicate the grid is loss
    //Grid available again
    //Set the grid slowly turn on from left to right light all led to indicate the grid is available. 

    //Software start the ADC0 and ADC1:
    adc_conversion_start(ACI_MCU_channel, ACO_MCU_channel);
    
    //Update the runtime count so I have the time reference for inverter control:
    inv_runtime_count++;
}

//Implement protection for when the gate driver shutdown for protection
void inverter_fault_isr( uint32_t status, uintptr_t context){
    //Turn off push pull if inverter gate driver returns fault condition
    push_pull_error_handler(push_pull_no_output, from_inverter);
}