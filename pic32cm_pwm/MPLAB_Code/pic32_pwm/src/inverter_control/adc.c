#include <inverter_control/adc.h>
#include <inverter_control/inverter.h>
#include <push_pull_control/push_pull_ctrl.h>

// #include "definitions.h"
// #include "plib_adc_common.h"

//The ADC runs in sequential mode, one after the other so that all channels are evaluated. Well this also does not work tho. 
// extern enum type ADC_POSINPUT





enum adc_interrupt_status{
    no_action = 0,
    result_ready = 1,
    overrun = 2,
    winmon = 4,
};

adc_value Vbat_voltage  = {Vbat_voltage_channel, 0};
adc_value I_Bat_MCU     = {I_Bat_MCU_channel, 0};
adc_value ACI_MCU       = {ACI_MCU_channel, 0, 2048};
adc_value ACO_MCU       = {ACO_MCU_channel, 0, 2048};
adc_value AC_Current_MCU = {AC_Current_MCU_channel, 0, 2048};
adc_value PP_Cur_MCU = {PP_Cur_MCU_channel, 0};
adc_value PP_Vol_MCU = {PP_Vol_MCU_channel, 0};

volatile uint16_t adc_probe = 0;

static volatile uint8_t adc0_current_channel = 0;
static volatile uint8_t adc1_current_channel = 0;


void adc_init(){
    ADC0_ChannelSelect(ADC_POSINPUT_AIN2, ADC_NEGINPUT_GND);
    //Enable the gain and bias correction for ADC0 and ADC1
    // ADC0_REGS->ADC_CTRLC |= ADC_CTRLC_CORREN_Msk;
    // ADC1_REGS->ADC_CTRLC |= ADC_CTRLC_CORREN_Msk;
    //Manually set the priority for ADC0 interrupt. Currently set at 3
    // NVIC->IP[5] |= (uint32_t)((3) << 14); //I will add the explaination later
    //register the read from sequence to the ISR of result ready
    ADC0_CallbackRegister(adc_read_from_seq, 0);
    ADC0_InterruptsEnable(0x1);
    ADC0_InterruptsClear(0x1); //0b| 0 | 0 | 0 | 0 | 0 | winmon | overrun | resrdy |  
    ADC0_Enable();
    ADC1_Enable(); //Don't use ADC1 interrupt to avoid conflict
    adc_conversion_start(Vbat_voltage_channel, I_Bat_MCU_channel); //Read the first adc conversion
}

void adc_disable(){
    ADC0_Disable();
    ADC1_Disable();
}

void adc_enable(){
    ADC0_Enable();
    ADC1_Enable();
}

void adc_conversion_start(adc0_channel channel_adc0, adc1_channel channel_adc1){
    channel_adc1 -= adc0_offset_index; //Remove the offset to yield the correct channel index
    ADC0_ChannelSelect(channel_adc0, ADC_NEGINPUT_GND);
    ADC1_ChannelSelect(channel_adc1, ADC_NEGINPUT_GND);
    adc0_current_channel = channel_adc0;
    adc1_current_channel = channel_adc1;
    ADC0_ConversionStart();
    //Only need the ADC0 conversion start, the ADC1 is in slave mode. The trigger is set at BOTH
    // ADC1_ConversionStart();
}

//These value has no offset correction
int read_adc_int(uint8_t channel){
    switch (channel)
    {
    case Vbat_voltage_channel:
        return Vbat_voltage.value[(Vbat_voltage.index == 0 ? max_adc_sample : Vbat_voltage.index) - 1];
    case I_Bat_MCU_channel:
        return I_Bat_MCU.value[(I_Bat_MCU.index == 0 ? max_adc_sample : I_Bat_MCU.index) - 1];
    case ACI_MCU_channel:
        return ACI_MCU.value[(ACI_MCU.index == 0 ? max_adc_sample : ACI_MCU.index) - 1];
    case ACO_MCU_channel:
        return ACO_MCU.value[(ACO_MCU.index == 0 ? max_adc_sample : ACO_MCU.index) - 1];
    case AC_Current_MCU_channel:
        return AC_Current_MCU.value[(AC_Current_MCU.index == 0 ? max_adc_sample : AC_Current_MCU.index) - 1];    
    case PP_Cur_MCU_channel:
        return PP_Cur_MCU.value[(PP_Cur_MCU.index == 0 ? max_adc_sample : PP_Cur_MCU.index) - 1];         
    case PP_Vol_MCU_channel:
        return PP_Vol_MCU.value[(PP_Vol_MCU.index == 0 ? max_adc_sample : PP_Vol_MCU.index) - 1];          
    default:
        break;
    }
    return 0;
}

//These value has no offset correction and read the previous values
int read_adc_index(uint8_t channel, uint8_t prev_index){
    switch (channel)
    {
    case Vbat_voltage_channel:
        return Vbat_voltage.value[Vbat_voltage.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : Vbat_voltage.index - prev_index];
    case I_Bat_MCU_channel:
        return I_Bat_MCU.value[I_Bat_MCU.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : I_Bat_MCU.index - prev_index];
    case ACI_MCU_channel:
        return ACI_MCU.value[ACI_MCU.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : ACI_MCU.index - prev_index];
    case ACO_MCU_channel:
        return ACO_MCU.value[ACO_MCU.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : ACO_MCU.index - prev_index];
    case PP_Cur_MCU_channel:
        return PP_Cur_MCU.value[PP_Cur_MCU.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : PP_Cur_MCU.index - prev_index];    
    case PP_Vol_MCU_channel:
        return PP_Vol_MCU.value[PP_Vol_MCU.index - prev_index < 0 ? max_adc_sample - 1 - prev_index : PP_Vol_MCU.index - prev_index];  
    default:
        break;
    }
    return 0;
}

float read_adc_float(uint8_t channel){
    switch (channel)
    {
    case Vbat_voltage_channel:
        return Vbat_voltage.value[(Vbat_voltage.index == 0 ? max_adc_sample : Vbat_voltage.index) - 1]*5.0/4096.0;
    case I_Bat_MCU_channel:
        return I_Bat_MCU.value[(I_Bat_MCU.index == 0 ? max_adc_sample : I_Bat_MCU.index) - 1]*5.0/4096.0;
    case ACI_MCU_channel:
        return ACI_MCU.value[(ACI_MCU.index == 0 ? max_adc_sample : ACI_MCU.index) - 1]*5.0/4096.0;
    case ACO_MCU_channel:
        return ACO_MCU.value[(ACO_MCU.index == 0 ? max_adc_sample : ACO_MCU.index) - 1]*5.0/4096.0;
    case AC_Current_MCU_channel:
        return AC_Current_MCU.value[(AC_Current_MCU.index == 0 ? max_adc_sample : AC_Current_MCU.index) - 1]*5.0/4096.0;    
    default:
        break;
    }
    return 0;
}

uint8_t read_adc_result_index(uint8_t channel){
    switch (channel)
    {
        case Vbat_voltage_channel:
            return Vbat_voltage.index;
        case I_Bat_MCU_channel:
            return I_Bat_MCU.index;
        case ACI_MCU_channel:
            return ACI_MCU.index;
        case ACO_MCU_channel:
            return ACO_MCU.index;
        case AC_Current_MCU_channel:
            return AC_Current_MCU.index; 
        case PP_Cur_MCU_channel:
            return PP_Cur_MCU.index;
        case PP_Vol_MCU_channel:
            return PP_Vol_MCU.index;                           
        default:
            break;
    }
    return 0;
}

//The interrupt is activated via TCC0 at the middle of turn off to get clear value. //Well this doesnt work...
void adc_read_from_seq(ADC_STATUS status, uintptr_t context){
    //See what triggered the interrupt
    // uint8_t adc_intrp_status = ADC0_REGS->ADC_INTFLAG; //0b| 0 | 0 | 0 | 0 | 0 | winmon | overrun | resrdy |

    // uint8_t bitmask = 1;
    // while (bitmask < 4){
    //     switch (status & bitmask)
    //     {
    //     case no_action:
    //         break;
    //     case result_ready:
            switch (adc0_current_channel)
                {
                case I_Bat_MCU_channel:
                    adc_probe++;
                    I_Bat_MCU.value[I_Bat_MCU.index++] = ADC0_ConversionResultGet();
                    if (I_Bat_MCU.index > max_adc_sample - 1) I_Bat_MCU.index = 0;
                    while (!ADC1_ConversionStatusGet())
                    {
                        //Wait until the ADC1 result is ready, usually it is ready right away.
                    }
                    Vbat_voltage.value[Vbat_voltage.index++] = ADC1_ConversionResultGet();
                    if (Vbat_voltage.index > (max_adc_sample - 1)) Vbat_voltage.index = 0;
                    
                    adc_conversion_start(PP_Vol_MCU_channel, ACO_MCU_channel);
                    break;
                case ACI_MCU_channel:
                    ACI_MCU.value[ACI_MCU.index++] = ADC0_ConversionResultGet();
                    if (ACI_MCU.index > max_adc_sample - 1) ACI_MCU.index = 0;

                    //Get the ADC value for ACO too from ADC1
                    while (!ADC1_ConversionStatusGet())
                    {
                        //Wait until the ADC1 result is ready, usually it is ready right away.
                    }
                    ACO_MCU.value[ACO_MCU.index++] = ADC1_ConversionResultGet();
                    if (ACO_MCU.index > max_adc_sample - 1) ACO_MCU.index = 0;
                    //Run the calculation from here!
                    //The interrupt routine for Inverter control is here. 

                    // inverter_state_machine();

                    //Start the ADC conversion for Ibat and Vbat.
                    // adc_conversion_start(I_Bat_MCU_channel, Vbat_voltage_channel);

                    break;
                case PP_Cur_MCU_channel:
                    PP_Cur_MCU.value[PP_Cur_MCU.index++] = ADC0_ConversionResultGet();
                    if (PP_Cur_MCU.index > max_adc_sample - 1) PP_Cur_MCU.index = 0;
                    adc_conversion_start(AC_Current_MCU_channel, ACO_MCU_channel);
                    
                    break;
                case AC_Current_MCU_channel:
                    AC_Current_MCU.value[AC_Current_MCU.index++] = ADC0_ConversionResultGet();
                    if (AC_Current_MCU.index > max_adc_sample - 1) AC_Current_MCU.index = 0;
                    break;

                case PP_Vol_MCU_channel:
                    PP_Vol_MCU.value[PP_Vol_MCU.index++] = ADC0_ConversionResultGet();
                    if (PP_Vol_MCU.index > max_adc_sample - 1) PP_Vol_MCU.index = 0;
                    adc_conversion_start(PP_Cur_MCU_channel, ACO_MCU_channel);

                    //Check the voltage level of Push pull output and trigger fault handler if PP voltage too high.
                    if (PP_Vol_MCU.value[PP_Vol_MCU.index - 1] > push_pull_protection_strc.max_adc_voltage){
                        push_pull_error_handler(push_pull_overvoltage, from_adc);
                    }
                    break;
               
                default:
                    break;
                }
            /*
            Calculate inverter working parameter
            Inverter voltage ref, voltage error, current ref, current error, RMS values,  

            */
            //Run the Inverter state machine here!

    //         break;
    //     case overrun:
    //         //Clear the overrun flag if not already
    //         ADC0_REGS -> ADC_INTFLAG |= (uint8_t)(ADC_INTFLAG_OVERRUN_Msk);
    //         // printf("ADC0 overrun");
    //         break;
    //     case winmon:
    //         //Claer the winmon flag if not already
    //         ADC0_REGS -> ADC_INTFLAG |= (uint8_t)(ADC_INTFLAG_WINMON_Msk);
    //         break;
    //     default:
    //         printf("Undefined adc0 option\n");
    //         break;
    //     }
    //     status &= ~bitmask; //Cancel the bit
    //     bitmask <<= 1; //Shift left
    // }   

    return;
}

