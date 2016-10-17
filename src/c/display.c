#include <pebble.h>
#include "display.h"

static uint16_t counter;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24;
static GBitmap *s_res_replay;
static GBitmap *s_res_stop;
static GBitmap *s_res_play;
static TextLayer *s_textlayer_1;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_replay = gbitmap_create_with_resource(RESOURCE_ID_replay);
  s_res_stop = gbitmap_create_with_resource(RESOURCE_ID_stop);
  s_res_play = gbitmap_create_with_resource(RESOURCE_ID_play);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(-17, 1, 130, 28));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "Pedometer");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorWhite);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_replay);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_stop);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_play);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(10, 73, 100, 20));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Count:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_2);
  gbitmap_destroy(s_res_replay);
  gbitmap_destroy(s_res_stop);
  gbitmap_destroy(s_res_play);
}
// END AUTO-GENERATED UI CODE
void draw_counter(){
  
    static char results[60];
  snprintf(results,60, "Count: %d",counter);
  
    text_layer_set_text(s_textlayer_2,results);
  
}
static void handle_window_unload(Window* window) {
  destroy_ui();
}
void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click ...
  Window *window = (Window *)context;
  ButtonId buttonId = click_recognizer_get_button_id(recognizer);
    counter += 1;
  draw_counter(); 
}
void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click ...
  Window *window = (Window *)context;
  ButtonId buttonId = click_recognizer_get_button_id(recognizer);
    counter += 1;
  draw_counter(); 
}
void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called on single click, and every 1000ms of being held ... on s'en fiche!  
  counter += 1;
  draw_counter();
  Window *window = (Window *)context;
}


void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
//  ... called on long click start ... on s'en fiche! 
  counter = 0;
  static char results[60];
  snprintf(results,60, "Count: %d",counter);
  
    text_layer_set_text(s_textlayer_2,results);
  Window *window = (Window *)context;
}

void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
 // ... called when long click is released ... on s'en fiche! 
    Window *window = (Window *)context;
}
void config_provider(Window *window) {
 // single click / repeat-on-hold config:
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_SELECT, 1000, select_single_click_handler);

  // long click config:
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
}

void show_display(void) {
  initialise_ui();
  window_set_click_config_provider(s_window, (ClickConfigProvider) config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_display(void) {
  window_stack_remove(s_window, true);
}
