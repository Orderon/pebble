#pragma once

// Animation's handlers
static void anim_started_handler(Animation *animation, void *context);

static void on_animation_stopped(Animation *anim, bool finished, void *context);

 // Function xhich create the animation
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration);