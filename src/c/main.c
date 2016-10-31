#include <pebble.h>
#include "animation.h"
#include "message.h"

uint16_t counter;
long double distance;
Layer *s_layer;
BitmapLayer *character_layer;
GBitmap *character; 

// Background //////////////
Window *s_window;
GFont s_res_gothic_28_bold;
GBitmap *s_res_replay;
GBitmap *s_res_stop;
GBitmap *s_res_play;
GFont s_res_gothic_18;
TextLayer *s_textlayer_1;
ActionBarLayer *s_actionbarlayer_1;
TextLayer *s_textlayer_2;
TextLayer *s_textlayer_3;


//////////////////////////////

 static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Improve the layout to be more like a watchface
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_replay = gbitmap_create_with_resource(RESOURCE_ID_replay);
  s_res_stop = gbitmap_create_with_resource(RESOURCE_ID_stop);
  s_res_play = gbitmap_create_with_resource(RESOURCE_ID_play);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
   
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(-5, 9, 130, 28));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "Pedometer");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorClear);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_replay);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_stop);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_play);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(45, 107, 100, 28));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Step:");
  text_layer_set_font(s_textlayer_2, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(9, 131, 100, 20));
  text_layer_set_text(s_textlayer_3, "Distance:");
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
   
  // Create the Animate Layer
  character_layer = bitmap_layer_create(GRect(30, 37, 60, 60));
  character = gbitmap_create_with_resource(RESOURCE_ID_mario2);
  bitmap_layer_set_background_color(character_layer, GColorBlack);
  bitmap_layer_set_bitmap(character_layer, character);
  s_layer=bitmap_layer_get_layer(character_layer);
  

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, action_bar_layer_get_layer(s_actionbarlayer_1));
  layer_add_child(window_layer, text_layer_get_layer(s_textlayer_1));
  layer_add_child(window_layer, text_layer_get_layer(s_textlayer_2));
  layer_add_child(window_layer, text_layer_get_layer(s_textlayer_3));
  layer_add_child(window_layer, s_layer);
   
   // Animate the layer
   GRect start = GRect(30, 37, 60, 60);
   GRect finish = GRect(30, 50, 60, 60);
   animate_layer(s_layer, &start, &finish, 300);
   
   // Message at 10000 steps
   //dialog_message_window_push();
}

static void main_window_unload(Window *window) {
   // Destroy child layer
  layer_destroy(s_layer);
  bitmap_layer_destroy(character_layer);
  text_layer_destroy(s_textlayer_1);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_textlayer_3);


   // Destroy images
  gbitmap_destroy(s_res_replay);
  gbitmap_destroy(s_res_stop);
  gbitmap_destroy(s_res_play);
  gbitmap_destroy(character);

}

// Create animation ////////
/*void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
  int seconds = tick_time->tm_sec;
  if (seconds==0) {
        //Slide offscreen up
        GRect start = GRect(30, 37, 60, 60);
        GRect finish = GRect(30, 50, 60, 60);
        animate_layer(s_layer, &start, &finish, 300, 500);
  }

}*/

///////////////////////////

 void init(void) {
   // Create main Window element and assign to pointer
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
    });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_window, true);
   
  // Register with TickTimerService
  //tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
   
  // Make sure the time is displayed from the start
  //update_time();
}

 void deinit(void) {
   // Destroy window
  window_destroy(s_window);
}

/////////////////////////////

int main(void) {
  // initialisation
  init();
 // dialog_message_window_push();
   
 app_event_loop();
  
  //Deinitialisation
  deinit();
}