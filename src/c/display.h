/*---------------------------------------------------------------------------
display.h
Authors: Lucie Houel, Cyrill Baumann
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

#pragma once
  /*Handler des boutons, permettent de changer la valeur de stop: 
une fois stop à 1, on ne compte plus les pas et l'animation stoppe */
static void down_click_handler(ClickRecognizerRef recognizer, void *context);
static void up_click_handler(ClickRecognizerRef recognizer, void *context);
static void select_click_handler(ClickRecognizerRef recognizer, void *context);
  /* soubscription aux event bouton */
static void click_config_provider(void *context);

//////////////Background //////////

/* the window's handlers*/
static void main_window_load(Window *window);
static void main_window_unload(Window *window);

/////// BATTERY ////////
/* Battery initialisation */
static void initialise_ui_manuel(void);

static void draw_battery();
static void battery_handler(BatteryChargeState state);

//////////// Construction and destriction function to handle the memory ////////////

static void initialise_ui(void);
void window_deinit();

///////////// UPDATE LOOP //////

/* Update the number of steps if !stop and schedule the background animation.
When the number of steps is 10000 (but here 100 in order to maj-ke it visible rapidly) it pushes the message "wow ! you ran 10000 steps" */
void update_counter(int add);

//////////// Gather the 'init' and 'deinit' functions  //////////////

//called to show the window will handle initialisation & display of window
void show_display(void) ;
//called to hide window. will handle destruction of window
void hide_display(void) ;