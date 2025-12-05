#include <system_mornitor_n_leds/system_mornitor.h>
#include "definitions.h"
#include "system_mornitor.h"

#define event_buffer_max_depth 10
led_blink_queue led_event_buffer[event_buffer_max_depth];
led_blink_queue current_block;
volatile uint8_t head_index, tail_index;
volatile uint8_t current_queue_depth = 0;
volatile uint8_t persistent_state = 0; //This is the bit map for the persistence state of the leds. After pattern is completed it will light up this persistence state.
volatile uint8_t temporary_state = 0;
volatile bool finished_flag = true;
static uint8_t run_counter = 0;
volatile uint32_t previous_time_led[5];

void led_show_signal(led_signal signal, led_priority priority, uint8_t repetition){
    led_blink_queue new_block = {signal, priority, repetition, false};
    led_event_buffer[head_index++] = new_block;
    if (head_index > event_buffer_max_depth - 1) head_index = 0;
    //This part rearrage the blocks in the buffer queue based on priority level.
    // for (int i = 0; i < current_queue_depth; i++){
    //     if (led_event_buffer[i].processing_guard == true) continue;
    //     if (new_block.priority <= led_event_buffer[i].priority) continue;
    //     led_blink_queue temp_block = led_event_buffer[i];
    //     led_event_buffer[i] = new_block;
    //     new_block = temp_block;
    // }
}

void fetch_current_block(){
    if (tail_index - head_index == 0) return;
    current_queue_depth = tail_index++;
    if (tail_index > event_buffer_max_depth - 1) tail_index = 0;
    led_event_buffer[current_queue_depth].processing_guard = true;
}


void processing_light_pattern(){
    if (tail_index - head_index == 0 && (finished_flag == true) && ((led_event_buffer[current_queue_depth].pattern_repetition <= 0))) { //The queue is finished, run persistent states
        execute_persistent_state();
        return;
    }
    if (finished_flag == true){
        if (led_event_buffer[current_queue_depth].pattern_repetition <= 0){
            fetch_current_block();
            // printf("repetition: %d\n", led_event_buffer[current_queue_depth].pattern_repetition);
        }
        led_event_buffer[current_queue_depth].pattern_repetition--;
        // printf("repetition 2: %d\n", led_event_buffer[current_queue_depth].pattern_repetition);
        run_counter = 0;
        finished_flag = false;
    }
    switch (led_event_buffer[current_queue_depth].event)
    {
        case error:
            error_fn();
            break;
        case bypass_relay_on:
            bypass_relay_on_fn();
            break;
        case bypass_relay_off:
            bypass_relay_off_fn();
            break;
        case grid_connect_relay_on:
            grid_connect_relay_on_fn();
            break;
        case grid_connect_relay_off:
            grid_connect_relay_off_fn();
            break;
        case led_running_100ms_lr:
            led_running_100ms_lr_fn();
            break;
        case led_running_500ms_lr:
            led_running_500ms_lr_fn();
            break; 
        case led_running_100ms_rl:
            led_running_100ms_rl_fn();
            break;
        case led_running_500ms_rl:
            led_running_500ms_rl_fn();
            break;  
        case led_push_pull_error_flash:
            led_push_pull_error_flash_fn();
            break;                               
        default:
            printf("Unexpected led event request");
            break;
    }
    execute_temporary_state();
    return;
}
//How about pattern and toggle, like after the pattern is finished, the leds lights up based on predefined leds postion. 
//Each light pattern occupies a separate function entirely

//Persistent patterns.
void bypass_relay_on_fn(){
    persistent_state |= 0x1 << 0;
    // printf("Bypass relay on");
    printf(persistent_state);
    finished_flag = true;
}

void bypass_relay_off_fn(){
    persistent_state &= ~0x1 << 0;
    // printf("Bypass relay off");
    printf(persistent_state);
    finished_flag = true;
}

void grid_connect_relay_on_fn(){
    persistent_state |= 0x1 << 2;
    finished_flag = true;
}

void grid_connect_relay_off_fn(){
    persistent_state &= ~(0x1 << 2);
    finished_flag = true;
}

void all_on_fn(){
    persistent_state = 0xF;
    // printf("All on");
    printf(persistent_state);
    finished_flag = true;
}

void all_off_fn(){
    persistent_state = 0x0;
    // printf("All off");
    printf(persistent_state);
    finished_flag = true;
}

void execute_persistent_state(){
    if ((persistent_state & (0x1 << 0)) > 0) LED_D8_Set(); else LED_D8_Clear(); //Release this pin so I can use it for diagnostic
    if ((persistent_state & (0x1 << 1)) > 0) LED_D7_Set(); else LED_D7_Clear();
    if ((persistent_state & (0x1 << 2)) > 0) LED_D9_Set(); else LED_D9_Clear();  
}

//Non-persistent patterns.
void error_fn(){

}
void led_running_100ms_rl_fn(){
    if (SYSTICK_GetTickCounter() - previous_time_led[0] > 100){
        previous_time_led[0] = SYSTICK_GetTickCounter();
        temporary_state = 1;
        switch (run_counter)
        {
        case 0:
            temporary_state = 0;
            run_counter++;
            break;
        case 1:
            temporary_state <<= 0;
            run_counter++;
            break; 
        case 2:
            temporary_state <<= 1;
            run_counter++;
            break;
        case 3:
            temporary_state <<= 2;
            run_counter++;
            break;    
        default:
            finished_flag = true;
            break;
        }
    }
}

void led_running_500ms_rl_fn(){
    if (SYSTICK_GetTickCounter() - previous_time_led[0] > 500){
        previous_time_led[0] = SYSTICK_GetTickCounter();
        temporary_state = 1;
        switch (run_counter)
        {
        case 0:
            temporary_state = 0;
            run_counter++;
            break;
        case 1:
            temporary_state <<= 1;
            run_counter++;
            break; 
        case 2:
            temporary_state <<= 2;
            run_counter++;
            break;
        case 3:
            temporary_state <<= 3;
            run_counter++;
            break;    
        default:
            finished_flag = true;
            break;
        }
    }
}

void led_running_100ms_lr_fn(){
    if (SYSTICK_GetTickCounter() - previous_time_led[0] > 100){
        previous_time_led[0] = SYSTICK_GetTickCounter();
        temporary_state = 0b100;
        switch (run_counter)
        {
        case 0:
            temporary_state = 0;
            run_counter++;
            break;
        case 1:
            temporary_state >>= 0;
            run_counter++;
            break; 
        case 2:
            temporary_state >>= 1;
            run_counter++;
            break;
        case 3:
            temporary_state >>= 2;
            run_counter++;
            break;    
        default:
            finished_flag = true;
            break;
        }
    }
}

void led_running_500ms_lr_fn(){
    if (SYSTICK_GetTickCounter() - previous_time_led[0] > 500){
        previous_time_led[0] = SYSTICK_GetTickCounter();
        temporary_state = 0b100;
        switch (run_counter)
        {
        case 0:
            temporary_state = 0;
            run_counter++;
            break;
        case 1:
            temporary_state >>= 0;
            run_counter++;
            break; 
        case 2:
            temporary_state >>= 1;
            run_counter++;
            break;
        case 3:
            temporary_state >>= 2;
            run_counter++;
            break;    
        default:
            finished_flag = true;
            break;
        }
    }
}

//Flash all 3 LEDs 3 times to indicate error 
void led_push_pull_error_flash_fn(){
    if (SYSTICK_GetTickCounter() - previous_time_led[0] > 500){
        previous_time_led[0] = SYSTICK_GetTickCounter();
        switch (run_counter){
            case 0:
                //Turn on all three LEDs
                temporary_state = 0b111;
                run_counter++;
                break;
            case 1:
                //Turn off all three LEDs
                temporary_state = 0b000;
                run_counter++;
                break;
            case 2:
                //Turn on all three LEDs
                temporary_state = 0b111;
                run_counter++;
                break;
            case 3:
                //Turn off all three LEDs
                temporary_state = 0b000;
                run_counter++;
                break;
            case 4:
                //Turn on all three LEDs
                temporary_state = 0b111;
                run_counter++;
                break;
            case 5:
                //Turn off all three LEDs
                temporary_state = 0b000;
                run_counter++;
                break;
            default:
                finished_flag = true;
                break;
        }
    }
}

void execute_temporary_state(){
    if ((temporary_state & (0x1 << 0)) > 0) LED_D8_Set(); else LED_D8_Clear(); //Release this pin so I can use it for diagnostic
    if ((temporary_state & (0x1 << 1)) > 0) LED_D7_Set(); else LED_D7_Clear();
    if ((temporary_state & (0x1 << 2)) > 0) LED_D9_Set(); else LED_D9_Clear();  
}