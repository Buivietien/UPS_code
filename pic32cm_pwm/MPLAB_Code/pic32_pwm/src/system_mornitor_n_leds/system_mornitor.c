#include "definitions.h"
#include <system_mornitor_n_leds/system_mornitor.h>

#define RMS_ring_buffer_max 20

volatile uint32_t previous_time[5];

typedef struct RMS_buffer_struct {
    float value;
    uint32_t value_ring_buffer[RMS_ring_buffer_max];
    uint32_t square;
    uint8_t head_index;
    uint8_t tail_index;
} RMS_buffer;

RMS_buffer ACO;
RMS_buffer ACI;

void system_mornitor_init(){

    SYSTICK_TimerCallbackSet(systick_isr, 0); //This isr runs every 1mS
}

void calculate_RMS(){

}

void systick_isr(uintptr_t context){ //Ok... what to put here to run every 1mS. Well first, leds
     //Run every 1mS
     //I can calculate the RMS here instead of the ADC0 ISR
    ACO.value_ring_buffer[ACO.head_index++];
    if (ACO.head_index++ > RMS_ring_buffer_max - 1) ACO.head_index = 0;
    ACI.value_ring_buffer[ACI.head_index++];
    if (ACI.head_index++ > RMS_ring_buffer_max - 1) ACI.head_index = 0;
    
    //Processing LEDs pattern
    processing_light_pattern();

    //Calculate the Inverter main ac data
    // calculate_main_ac();

    //Run the push pull state machine here, this is moved to tc4 isr
    // push_pull_state_machine();

    if (SYSTICK_GetTickCounter() - previous_time[ms_100] > 100){ 
        previous_time[ms_100] = SYSTICK_GetTickCounter();
        //Run every 100mS

    }

    if (SYSTICK_GetTickCounter() - previous_time[ms_300] > 300){ 
        previous_time[ms_300] = SYSTICK_GetTickCounter();
        //Run every 300mS

    }

    if (SYSTICK_GetTickCounter() - previous_time[ms_500] > 500){ 
        previous_time[ms_500] = SYSTICK_GetTickCounter();
        //Run every 500mS

    }   

        if (SYSTICK_GetTickCounter() - previous_time[ms_1000] > 1000){ 
        previous_time[ms_1000] = SYSTICK_GetTickCounter();
        //Run every 1000mS

    }

}