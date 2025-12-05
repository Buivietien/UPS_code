// #include <GcodeExecutor.h>
#include <gcode_parser/GCodeParser.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>  
#include <inverter_control/inverter.h>
#include <float.h>
#include <system_mornitor_n_leds/system_mornitor.h>
#include <printf_custom\printf.h>
#include <push_pull_control/push_pull_ctrl.h>

enum relay_command{
    // relay_read_status = 0,
    relay_turn_off = 0,
    relay_turn_on = 1
};
enum relay_number{
    bypass_relay,
    grid_connect_relay
};
enum SPWM{
    SPWM_off,
    SPWM_on
};

//Inverter control SPWM ON OFF
void M120(){
    int param_p = 0;
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_int('P');
    } else {
        printf("Expecting P0 for OFF and P1 for ON, default is OFF \n");
        return;
    }   
    switch (param_p)
    {
    case SPWM_off:
        inv_gate_driver_turn_off();
        inv_spwm_manual_stop();
        printf("SPWM is OFF, Manual OFF \n");
        break;
    case SPWM_on:
        inv_gate_driver_turn_on_reset();
        inv_spwm_manual_start();
        printf("SPWM is ON, Manual ON \n");
        break;
    default:
        break;
    }
    return;
}

//Inverter set deadtime
void M121(){
    extern uint8_t deadtime_count;
    float param_p = 1.0; //Default is 1 usec
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_float('P');
    } else {
        printf("Current deadtime: %.2f uS\n", deadtime_count/48.0);
        return;
    }
    if (param_p < 0){
        printf("Deadtime can not be negative\n");
        return;
    }
    inv_set_deadtime(param_p); 
    return;

}

//Inverter set ma. Require M124 to set to Manual mode
void M122(){
    float param_p;
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_float('P');
        if (param_p > 1 || param_p < 0){
            printf("Invalid ma factor\n");
            return;
        }
        inv_set_ma(param_p);
        printf("Set ma_factor: %f\n", param_p);
    } else {
        printf("Required parameter in float format\n");
        return;
    }
}

//Inverter change Output frequency
void M123(){
    uint8_t param_p;
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_float('P');
    } else {
        printf("Required parameter in uint format\n");
        return;
    }
    inv_set_freq(param_p);
    printf("Set frequency: %d Hz\n", param_p);
    return; 
}

//Test inverter main detection
void M124(){
    uint8_t skip_phase = 0;
    uint8_t main_status = true;
    uint8_t restart_sine = false;
    if (GcodeParser_HasWord('S')){
        skip_phase = GcodeParser_GetWordValue_int('S');
    } 
    if (GcodeParser_HasWord('P')){
        main_status = GcodeParser_GetWordValue_int('P');
    } 
    if (GcodeParser_HasWord('R')){
        restart_sine = GcodeParser_GetWordValue_int('R');
    } 
    printf("Test option: (S)skip %d phase, %d (P)stat, %d (R)restart\n", skip_phase, main_status, restart_sine);
    test_ups(skip_phase, main_status, restart_sine);
}

//Check inverter gate driver status
void M125(){
    gate_driver_status();
}

//Turn on Gate driver manually
void M126(){
    inv_gate_driver_turn_on_reset();
}

//Turn off Gate driver manually
void M127(){
    inv_gate_driver_turn_off();
}

//Set PWM duty cycle rejection !DEPRECATED
void M128(){
    uint8_t duty_cycle = 2;
    if (GcodeParser_HasWord('P')){
        duty_cycle = GcodeParser_GetWordValue_int('P');
    }
    printf("Set rejection duty cycle as: %d %%", duty_cycle);
    set_spwm_rejection_duty_cycle(duty_cycle);
}

//Calculate the RMS value of the Grid
void M129(){
    // calculate_RMS_value();
}

//Inverter Relay control 
void M130(){
    int param_s;
    if (GcodeParser_HasWord('S')){
        param_s = GcodeParser_GetWordValue_int('S');
    } else {
        printf("Expecting relay number, S0 for bypass, S1 for grid connect \n");
        return;
    }
    int param_p = 0;
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_int('P');
    } else {
        switch (param_s)
        {
        case bypass_relay:
            bypass_relay_status();
            break;
        case grid_connect_relay:
            grid_connect_relay_status();
            break;
        default:
            break;
        }
    }
    switch (param_s){
        case bypass_relay:
            switch (param_p)
            {
                case relay_turn_off:
                    //Turn off the relay
                    bypass_relay_turn_off();
                    break;
                case relay_turn_on:
                    //Turn of the relay
                    bypass_relay_turn_on();
                    break;
                default:
                    break;
            }
            break;
        case grid_connect_relay:
            switch (param_p)
            {
            case relay_turn_off:
                grid_connect_relay_turn_off();
                break;
            case relay_turn_on:
                grid_connect_relay_turn_on();
            default:
                break;
            }
            break;

        default:
            break;
    }
    return; 
}

//Change the duty cycle of the load via IGBT to test the load response. Could use this Gcode to change mode
void M131(){
    uint8_t duty_cycle = 0;
    if (GcodeParser_HasWord('P')){
        duty_cycle = GcodeParser_GetWordValue_int('P');
        printf("Set IGBT duty cycle: %d\n", duty_cycle);
        spwm_manual_change_duty_cycle(duty_cycle);
        inv_spwm_manual_start();
    }

    uint8_t mode = 0;
    if (GcodeParser_HasWord('O')){
        mode = GcodeParser_GetWordValue_int('O');
        printf("Set output mode: %d\n", mode);
        spwm_change_output_mode(mode);
    }

}

//Enable or Disable AC and Inv state auto-switcher
void M132(){

}

//ADC read
void M140(){
    uint8_t selected_channel = 0;
    if (GcodeParser_HasWord('S')){
        selected_channel = GcodeParser_GetWordValue_int('S');
    }
    uint8_t param_p = 0;
    if (GcodeParser_HasWord('P')){
        param_p = GcodeParser_GetWordValue_int('P');
    }
    //Trigger conversion
    // adc_conversion_start(selected_channel);
    //print out all current indexed
    printf("Vbat ind: %d\n", read_adc_result_index(Vbat_voltage_channel));
    printf("I bat ind: %d\n", read_adc_result_index(I_Bat_MCU_channel));
    printf("ACI ind: %d\n", read_adc_result_index(ACI_MCU_channel));
    printf("ACO ind: %d\n", read_adc_result_index(ACO_MCU_channel));
    printf("AC Cur ind: %d\n", read_adc_result_index(AC_Current_MCU_channel));
    printf("PP_Cur ind: %d\n", read_adc_result_index(PP_Cur_MCU_channel));
    printf("PP_Vol ind: %d\n", read_adc_result_index(PP_Vol_MCU_channel));

    switch (selected_channel)
    {
        case Vbat_voltage_channel:
            printf("Battery vol: %d \n", read_adc_int(Vbat_voltage_channel));
            break;
        case I_Bat_MCU_channel:
            printf("I Bat: %d \n", read_adc_int(I_Bat_MCU_channel));
            break;
        case ACI_MCU_channel:
            printf("ACI vol: %d \n", read_adc_int(ACI_MCU_channel));
            break;
        case ACO_MCU_channel:
            printf("ACO vol: %d \n", read_adc_int(ACO_MCU_channel));
            break;
        case AC_Current_MCU_channel:
            printf("AC current: %d \n", read_adc_int(AC_Current_MCU_channel));
            break;
        case PP_Vol_MCU_channel:
            printf("PP vol: %d \n", read_adc_int(PP_Vol_MCU_channel));
            break;
        default:
            printf("Expecting ADC number, Battery %d, I Bat %d, ACI %d, ACO %d, AC cur %d, PP_Vol %d, PP_Cur %d\n", Vbat_voltage_channel, I_Bat_MCU_channel, ACI_MCU_channel, ACO_MCU_channel, AC_Current_MCU_channel, PP_Vol_MCU_channel, PP_Cur_MCU_channel);
            break;
    }


}


//M150: Test led patterns
void M150(){
    uint8_t selected_event = 0;
    if (GcodeParser_HasWord('S')){
        selected_event = GcodeParser_GetWordValue_int('S');
    }
    uint8_t repetition = 0;
    if (GcodeParser_HasWord('P')){
        repetition = GcodeParser_GetWordValue_int('P');
    }    
    printf("Run led event: %d, repeat: %d\n", selected_event, repetition);
    switch (selected_event)
    {
    case bypass_relay_on:
        led_show_signal(bypass_relay_on, 0, 0);
        break;
    case bypass_relay_off:
        led_show_signal(bypass_relay_off, 0, 0);
        break;
    case grid_connect_relay_on:
        led_show_signal(grid_connect_relay_on, 0, 0);
        break;
    case grid_connect_relay_off:
        led_show_signal(grid_connect_relay_off, 0, 0);
        break;
    case led_running_100ms_lr:
        led_show_signal(led_running_100ms_lr, 0, repetition);
        break;
    default:
        break;
    }
}

//Test sogi with generated dataset.
void M160(){
    
}

//M170: Turn on or off the push pull PWM signal
void M170(){
    uint8_t on_status = 0;
    if (GcodeParser_HasWord('P')){
        on_status = GcodeParser_GetWordValue_int('P');
    } else {
        printf("No input, default is off\n");
    }    
    switch (on_status)
    {
    case 1:
        push_pull_pwm_start();
        break;
    
    case 0:
        push_pull_exit_burst_mode(); //Turn off burst mode, since it is indepedent of run mode
        push_pull_exit_duty_pid_mode(); //Turn off duty pid mode here, since it is also independent of run mode
        push_pull_pwm_stop();
        printf("Push pull stop");
        break;
    }
}

//Change push pull duty cycle
void M171(){
    //Trigger the function to return the current duty cycle, 100 is the error value
    uint8_t current_duty_cycle = push_pull_duty_change(100);
    uint8_t increment = 0;
    if (GcodeParser_HasWord('I')){
        increment = GcodeParser_GetWordValue_int('I');
        printf("Increase duty cycle to: %d", push_pull_duty_change(current_duty_cycle + increment));
        return;
    }

    uint8_t duty_cycle = 0;
    if (GcodeParser_HasWord('P')){
        duty_cycle = GcodeParser_GetWordValue_int('P');
        printf("Current duty cycle: %d\n", push_pull_duty_change(duty_cycle));
    }
}

//Change push pull frequency
void M172(){
    //Get the current frequency, the 0 triggers error value and returns the current value
    uint16_t current_frequency = push_pull_frequency_change(0);
    uint8_t increment = 0;
    if (GcodeParser_HasWord('I')){
        increment = GcodeParser_GetWordValue_int('I');
        printf("Increase frequency to: %d", push_pull_frequency_change(current_frequency + increment));
        return;
    }
    
    uint16_t frequency = 0;
    if (GcodeParser_HasWord('F')){
        frequency = GcodeParser_GetWordValue_int('F');
        printf("Current frequency (0.1kHz): %d", push_pull_frequency_change(frequency));
    } 
}

//Trigger the softstart sequence
void M173(){
    uint8_t softstart_status = 0;
    if (GcodeParser_HasWord('P')){
        softstart_status = GcodeParser_GetWordValue_int('P');
        printf("Start softstart sequence\n");
    }

    if (softstart_status){
        push_pull_test_softstart(); //Run the softstart sequence!
    }
}

//Trigger the frequency PID control mode
void M174(){
    uint8_t pid_status = 0;
    if (GcodeParser_HasWord('P')){
        pid_status = GcodeParser_GetWordValue_int('P');
        printf("Start PID control mode\n");
    }

    if (pid_status){
        push_pull_enter_freq_pid_mode(); //Run the PID control mode!
    }
}

//Set push pull frequency PID parameters
void M175(){
    uint16_t setpoint = 0; //This is voltage
    if (GcodeParser_HasWord('V')){
        setpoint = GcodeParser_GetWordValue_int('V');
        push_pull_set_freq_pid_params(pid_setpoint, setpoint);
        printf("Set point: %d\n", setpoint);
    }

    uint16_t max_output = 0; //This is voltage
    if (GcodeParser_HasWord('O')){
        setpoint = GcodeParser_GetWordValue_int('O');
        push_pull_set_freq_pid_params(pid_setpoint, setpoint);
        printf("Max out: %d\n", setpoint);
    }

    float Kp = 0;
    if (GcodeParser_HasWord('P')){
        Kp = GcodeParser_GetWordValue_float('P');
        push_pull_set_freq_pid_params(pid_Kp, Kp);
        printf("Set Kp: %f\n", Kp);
    }

    float Ki = 0;
    if (GcodeParser_HasWord('I')){
        Ki = GcodeParser_GetWordValue_float('I');
        push_pull_set_freq_pid_params(pid_Ki, Ki);
        printf("Set Ki: %f\n", Ki);
    }
}

//Printout frequency Push pull PID status, like current error, setpoint and such
void M176(){
    uint8_t select = 0;
    if (GcodeParser_HasWord('S')){
        select = GcodeParser_GetWordValue_int('S');
        printf("Current val: %.2f\n", push_pull_set_freq_pid_params(select, -1)); //Negative is the error value which prompts the function to return the current val
    } else {
        printf("Options: Kp(%d), Ki(%d), Setpoint(%d), Input(%d), Output(%d), Error(%d)\n", pid_Kp, pid_Ki, pid_setpoint, pid_input, pid_output, pid_error);
    }
}

//Trigger the push pull burst mode
void M177(){
    uint8_t burst_status = 0;
    if (GcodeParser_HasWord('P')){
        burst_status = GcodeParser_GetWordValue_int('P');
    }
    
    bool single_shot = false;
    if (GcodeParser_HasWord('S')){
        single_shot = true;
    }

    bool pid_mode = false;
    if (GcodeParser_HasWord('N')){
        pid_mode = true;
    }

    if (burst_status){
        push_pull_enter_burst_mode(single_shot, pid_mode); //Enter push_pull burst mode.
        printf("Start push pull burst mode\n");
    } else {
        push_pull_exit_burst_mode();
        printf("Exit push pull burst mode\n");
    }
}

//Update push pull burst mode working parameters
void M178(){
    uint16_t setpoint = 0; //This is ADC value for the voltage
    if (GcodeParser_HasWord('V')){
        setpoint = GcodeParser_GetWordValue_int('V');
        push_pull_set_burst_mode_param(pp_burst_setpoint, setpoint);
        printf("Set point: %d\n", setpoint);
    }

    uint8_t hold_time = 0;
    if (GcodeParser_HasWord('H')){
        hold_time = GcodeParser_GetWordValue_float('H');
        if (hold_time > 0){
            push_pull_set_burst_mode_param(pp_burst_holdtime, hold_time);
        }
        printf("Set hold time: %d\n", hold_time);
    }

    uint8_t number_of_burst = 0;
    if (GcodeParser_HasWord('N')){
        number_of_burst = GcodeParser_GetWordValue_float('N');
        //Check odd or even
        if ((number_of_burst & 0x1) || (number_of_burst == 0)){
            //If the number is odd, reject the value
            printf("Even number of burst only, exiting\n");
            return;
        }
        push_pull_set_burst_mode_param(pp_burst_number_of_burst, number_of_burst);
        printf("Number of burst: %d\n", number_of_burst);
    }
}

//Trigger the duty PID control mode
void M179(){
    uint8_t pid_status = 0;
    if (GcodeParser_HasWord('P')){
        pid_status = GcodeParser_GetWordValue_int('P');
        printf("Start PID control mode\n");
    }

    if (pid_status){
        push_pull_enter_duty_pid_mode(); //Run the PID control mode!
    } else {
        push_pull_exit_duty_pid_mode();
    }
}

//Set push pull duty PID parameters
void M180(){
    uint16_t setpoint = 0; //This is voltage
    if (GcodeParser_HasWord('V')){
        setpoint = GcodeParser_GetWordValue_int('V');
        push_pull_set_duty_pid_params(pid_setpoint, setpoint);
        printf("Set point: %d\n", setpoint);
    }

    float Kp = 0;
    if (GcodeParser_HasWord('P')){
        Kp = GcodeParser_GetWordValue_float('P');
        push_pull_set_duty_pid_params(pid_Kp, Kp);
        printf("Set Kp: %f\n", Kp);
    }

    float Ki = 0;
    if (GcodeParser_HasWord('I')){
        Ki = GcodeParser_GetWordValue_float('I');
        push_pull_set_duty_pid_params(pid_Ki, Ki);
        printf("Set Ki: %f\n", Ki);
    }

    float max_out = 0;
    if (GcodeParser_HasWord('O')){
        max_out = GcodeParser_GetWordValue_float('O');
        push_pull_set_duty_pid_params(pid_max_output, max_out);
        printf("Set max out: %f\n", max_out);
    }
}

//Printout duty Push pull PID status, like current error, setpoint and such
void M181(){
    uint8_t select = 0;
    if (GcodeParser_HasWord('S')){
        select = GcodeParser_GetWordValue_int('S');
        printf("Current val: %.2f\n", push_pull_set_duty_pid_params(select, -1)); //Negative is the error value which prompts the function to return the current val
    } else {
        printf("Options: Kp(%d), Ki(%d), Setpoint(%d), Input(%d), Output(%d), Error(%d)\n", pid_Kp, pid_Ki, pid_setpoint, pid_input, pid_output, pid_error);
    }
}

//Set up push pull protection values
void M182(){
    uint16_t voltage_value;
    if (GcodeParser_HasWord('V')){
        voltage_value = GcodeParser_GetWordValue_int('V');
        printf("Set up push pull voltage protection: %d\n", voltage_value);
        push_pull_protection_strc.max_adc_voltage = voltage_value;
    }

    uint16_t current_value;
    if (GcodeParser_HasWord('I')){
        current_value = GcodeParser_GetWordValue_int('I');
        printf("Set up push pull current protection: %d\n", current_value);
        push_pull_protection_strc.max_adc_current = current_value;
    }
}
