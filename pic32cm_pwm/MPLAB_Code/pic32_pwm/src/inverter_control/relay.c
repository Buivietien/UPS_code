#include <inverter_control/relay.h>
#include <inverter_control/inverter.h>
#include "definitions.h"

void bypass_relay_turn_on(){
    A1_bypass_relay_Set();
    // printf("Relay ON\n");

}

void bypass_relay_turn_off(){
    A1_bypass_relay_Clear();
    // printf("Relay OFF\n");

}

bool bypass_relay_status(){
    switch (A1_bypass_relay_Get())
    {
    case true:
        printf("On");
        break;
    case false:
        printf("Off");
    
    default:
        break;
    };
    return A1_bypass_relay_Get();
}

void grid_connect_relay_turn_on(){
    A2_grid_connect_Set();
    // printf("Relay ON\n");
    LED_D9_Set();

}

void grid_connect_relay_turn_off(){
    A2_grid_connect_Clear();
    // printf("Relay OFF\n");
    LED_D9_Clear();
}

bool grid_connect_relay_status(){
    // switch (A2_grid_connect_Get())
    //     {
    //     case true:
    //         printf("On");
    //         break;
    //     case false:
    //         printf("Off");
        
    //     default:
    //         break;
    //     };
    return A2_grid_connect_Get();
}


void inv_fan_turn_on(){
    inv_FAN_Set();
    printf("FAN ON\n");
}

void inv_fan_turn_off(){
    inv_FAN_Clear();
    printf("FAN OFF\n");
}