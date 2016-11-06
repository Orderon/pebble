/*---------------------------------------------------------------------------
main.c
Authors: Thomas Triquet, Cyrill Baumann
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

// Include Pebble library
#include <pebble.h>
#include "src/c/display.h"
#include "src/c/data_acc.h"
#include "display.h"

// Callback funtcion of the accelerometer
static void accel_data_handler(AccelData * Data, uint32_t num_samples) {
    data_acc_update_acc(Data);
}

// Init function called when app is launched
static void init(void) {

    // Number of samples needed to call the accelerometer callback function
    uint32_t num_samples = NSAMPLES;
    // Allow accelerometer event
    accel_data_service_subscribe(num_samples, accel_data_handler);
    // Define accelerometer sampling rate  
    accel_service_set_sampling_rate(ACCEL_SAMPLING_25HZ);
  
    // Init. the acceleration datas
    data_acc_init();
    // Init. the norm datas
    data_norm_init();
  
    // Show the user Interface display
    show_display();
  }

// deinit function called when the app is closed
static void deinit(void) {
  
    // Destroy layers and main window 
    window_deinit();
  
    // Stop accelerometer
    accel_data_service_unsubscribe();
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}