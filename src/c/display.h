/*---------------------------------------------------------------------------
display.h
Authors: Lucie Houel, Cyrill Baumann
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

#pragma once


//////////// Construction and destriction function to handle the memory ////////////

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