#include <pebble.h>
#include "display.h"
#include "animation.h"
#include "message.h"
uint16_t counter;
double distance;
int stop=0;
Layer *s_layer;
BitmapLayer *character_layer;
GBitmap *character; 

///// DECLARATION //////////////
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

static uint16_t battery=24;
static BitmapLayer *batterie;
static BitmapLayer *batterie_end;
static BitmapLayer *batterie_start;


//////// BUTTON //////////
void down_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click down ...
    stop = 0;
  APP_LOG(APP_LOG_LEVEL_ERROR, "play");
  
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click up...
    counter = 0;
  APP_LOG(APP_LOG_LEVEL_ERROR, "replay");
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click middle, and every 1000ms of being held ... on s'en fiche!  
  stop = 1;
  APP_LOG(APP_LOG_LEVEL_ERROR, "stop");
}

void click_config_provider(void *context) {
 // single click / repeat-on-hold config:
   APP_LOG(APP_LOG_LEVEL_DEBUG, "provider");
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 50, up_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 50,down_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 50, select_click_handler);
   APP_LOG(APP_LOG_LEVEL_DEBUG, "provider2");
}

////////////////////////

void main_window_load(Window *window) {
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
  text_layer_set_text(s_textlayer_1, "Podometer");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);

  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorClear);
  action_bar_layer_set_click_config_provider(s_actionbarlayer_1, click_config_provider);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_replay);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_stop);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_play);

  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(38, 107, 100, 28));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Step:0");
  text_layer_set_font(s_textlayer_2, s_res_gothic_18);
  
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(9, 131, 100, 20));
  text_layer_set_text(s_textlayer_3, "Distance:0");
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  
   
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
   GRect finish = GRect(30, 37, 60, 60);
   GRect start = GRect(30, 50, 60, 60);
   animate_layer(s_layer, &start, &finish, 300);
   
   // Message at 10000 steps
   //dialog_message_window_push();
}

void main_window_unload(Window *window) {
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

/////// BATTERY ////////

static void initialise_ui_manuel(void){
  
  // Init. battery percentage
  BatteryChargeState state = battery_state_service_peek();
  battery = state.charge_percent;
  //overdraw everything with black
    batterie = bitmap_layer_create(GRect(2, 2, 25, 11));
    bitmap_layer_set_background_color(batterie, GColorBlack);
    layer_add_child(window_get_root_layer(s_window), (Layer *)batterie);
  
    // battery_end
  batterie_end = bitmap_layer_create(GRect(25, 5, 6, 6));
  bitmap_layer_set_background_color(batterie_end, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)batterie_end);
   //battery start
  batterie_start = bitmap_layer_create(GRect(2, 2, 2, 11));
  bitmap_layer_set_background_color(batterie_start, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)batterie_start);
  
  // battery
    int length = (22*battery)/100+1;
    batterie = bitmap_layer_create(GRect(25-length, 2, length, 11));
    bitmap_layer_set_background_color(batterie, GColorWhite);
    layer_add_child(window_get_root_layer(s_window), (Layer *)batterie);
 
}
void draw_battery(){ 
  //destroy previous layer of the battery
  bitmap_layer_destroy(batterie);
  
  //overdraw everything with black
  //  batterie = bitmap_layer_create(GRect(2, 2, 34, 20));
  //  bitmap_layer_set_background_color(batterie, GColorBlack);
  //  layer_add_child(window_get_root_layer(s_window), (Layer *)batterie);
  
  // draw new battery layer
    int length = (31*battery)/100;
    batterie = bitmap_layer_create(GRect(25-length, 2, length, 11));
    bitmap_layer_set_background_color(batterie, GColorWhite);
    layer_add_child(window_get_root_layer(s_window), (Layer *)batterie);
}

static void battery_handler(BatteryChargeState state) {
  battery = state.charge_percent;
  draw_battery();
  //---mark the drawing layer as dirty so as to force
  // a redraw---
  layer_mark_dirty((Layer *)batterie);
}

////////////////////////

void initialise_ui(void) {
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
   
   
  // Register with TickTimerService
  //tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
     
  battery_state_service_subscribe(battery_handler);
   
  // Make sure the time is displayed from the start
  //update_time();
}

void window_deinit(){
  window_destroy(s_window);
}

void update_counter(int add){
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "update");
  if (!stop){
    counter += add;
    distance = counter*0.70;
    GRect finish = GRect(30, 37, 60, 60);
    GRect start = GRect(30, 50, 60, 60);
    animate_layer(s_layer, &start, &finish, 300);  
  }
  if (counter==10){
    dialog_message_window_push();
  }
   //APP_LOG(APP_LOG_LEVEL_DEBUG, "update2");
  draw_battery();
  static char counter_text[60];
  snprintf(counter_text,60, "Steps: %d",counter);
  text_layer_set_text(s_textlayer_2,counter_text);
  static char dist[60];
  snprintf(dist,60,"Distance: %d", (int)distance);
  text_layer_set_text(s_textlayer_3,dist);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", stop);
  
}

//called to show the window will handle initialisation & display of window
void show_display(void) {
  initialise_ui();
  initialise_ui_manuel();
  window_stack_push(s_window, true);
}

//called to hide window. will handle destruction of window
/*void hide_display(void) {
  window_stack_remove(s_window, true);
}*/
