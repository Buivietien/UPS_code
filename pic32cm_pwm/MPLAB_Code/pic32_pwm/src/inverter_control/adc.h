#pragma once
#include "definitions.h"


#define max_adc_sample 10
typedef enum adc0_channel_enum{
    I_Bat_MCU_channel = 3,
    ACI_MCU_channel = 4,
    AC_Current_MCU_channel = 6,
    PP_Cur_MCU_channel = 7,
    PP_Vol_MCU_channel = 5,
} adc0_channel;

typedef enum adc1_channel_enum{
    adc0_offset_index = 11, //The offset is for switch case to work correctly and avoid conflict
    Vbat_voltage_channel = 14,
    ACO_MCU_channel = 15,
} adc1_channel;

typedef struct {
    uint8_t channel_number;
    volatile uint8_t index;
    uint16_t offset;
    float scale;
    volatile uint16_t value[max_adc_sample];
} adc_value;

//Declare extern so others program can access these value unrestricted.
extern adc_value Vbat_voltage;   
extern adc_value I_Bat_MCU;  
extern adc_value ACI_MCU; 
extern adc_value ACO_MCU;        
extern adc_value AC_Current_MCU;
extern adc_value PP_Cur_MCU;
extern adc_value PP_Vol_MCU;

void adc_init();
void adc_disable();
void adc_conversion_start(adc0_channel channel_adc0, adc1_channel channel_adc1);
int read_adc_int(uint8_t channel);
int read_adc_index(uint8_t channel, uint8_t prev_index);
float read_adc_float(uint8_t channel);
uint8_t read_adc_result_index(uint8_t channel);
void adc_read_from_seq(ADC_STATUS status, uintptr_t context);

