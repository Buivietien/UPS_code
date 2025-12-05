#pragma once
#include <printf_custom/printf.h>
#include <push_pull_control/push_pull_ctrl.h>
#include "definitions.h"

enum systick_interval_counter {
    ms_100 = 0,
    ms_300,
    ms_500,
    ms_1000,
};

typedef enum led_signal_enum{
    error = 1,
    bypass_relay_on,
    bypass_relay_off,
    grid_connect_relay_on,
    grid_connect_relay_off,
    led_running_100ms_lr,
    led_running_500ms_lr,
    led_running_100ms_rl,
    led_running_500ms_rl,
    led_push_pull_error_flash,
    all_off,
    all_on,
} led_signal;

typedef enum led_priority_enum{
    urgent,
    intermediate,
    low,
} led_priority;

typedef struct {
    led_signal event;
    volatile led_priority priority;
    volatile int8_t pattern_repetition;
    volatile bool processing_guard;
} led_blink_queue;

//LEDs
void led_show_signal(led_signal signal, led_priority priority, uint8_t repetition);
void fetch_current_block();
void processing_light_pattern();
void bypass_relay_on_fn();
void bypass_relay_off_fn();
void grid_connect_relay_on_fn();
void grid_connect_relay_off_fn();
void all_on_fn();
void all_off_fn();
void execute_persistent_state();
void error_fn();
void led_running_100ms_lr_fn();
void led_running_100ms_rl_fn();
void led_running_500ms_rl_fn();
void led_running_500ms_lr_fn();
void led_push_pull_error_flash_fn();
void execute_temporary_state();

//System mornitor
void system_mornitor_init();
void systick_isr(uintptr_t context);