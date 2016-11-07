/*---------------------------------------------------------------------------
animation.h
Authors: Lucie Houel
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

#pragma once

// Animation's handlers
//static void anim_started_handler(Animation *animation, void *context);

//static void on_animation_stopped(Animation *anim, bool finished, void *context);

 // Function which create the animation
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration);