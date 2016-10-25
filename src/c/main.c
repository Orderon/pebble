/*---------------------------------------------------------------------------
Template for TP of the course "System Engineering" 2016, EPFL

Authors: Flavien Bardyn & Martin Savary
Version: 1.0
Date: 10.08.2016

Use this "HelloWorld" example as basis to code your own app, which should at least 
count steps precisely based on accelerometer data. 

- Add the accelerometer data acquisition
- Implement your own pedometer using these data
- (Add an estimation of the distance travelled)

- Make an effort on the design of the app, try to do something fun!
- Comment and indent your code properly!
- Try to use your imagination and not google (we already did it, and it's disappointing!)
  to offer us a smart and original solution of pedometer

Don't hesitate to ask us questions.
Good luck and have fun!
---------------------------------------------------------------------------*/

// Include Pebble library
#include <pebble.h>
#include "src/c/display.h"
#include "src/c/data_acc.h"

// Declare the main window and two text layers
Window *main_window;
TextLayer *background_layer;
TextLayer *helloWorld_layer;
static Data_Acc* Acc[3];
static Data_Norm* Norm;

// Callback funtcion of the accelerometer
static void accel_data_handler(AccelData * Data, uint32_t num_samples)
{
    data_acc_update_acc(Data,Acc,Norm);
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
    data_acc_init(Acc);
    // Init. the norm datas
    data_norm_init(Norm);
  
    // Show the user Interface display
    show_display();
  
    // Add a logging meassage (for debug)
	  APP_LOG(APP_LOG_LEVEL_DEBUG, "Just write my first app!");
}

// deinit function called when the app is closed
static void deinit(void) {
  
    // Destroy layers and main window 
    text_layer_destroy(background_layer);
	  text_layer_destroy(helloWorld_layer);
    window_destroy(main_window);
    // Stop accelerometer
    accel_data_service_unsubscribe();
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
