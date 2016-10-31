#include <pebble.h>
#include "animation.h"

/*void on_animation_stopped(Animation *anim, bool finished, void *context){
    //Free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
}*/
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration){
    //Declare animation
    PropertyAnimation *property_anim_up = property_animation_create_layer_frame(layer, start, finish);
    Animation *anim_up = property_animation_get_animation(property_anim_up);
    PropertyAnimation *property_anim_down = property_animation_create_layer_frame(layer, finish, start);
    Animation *anim_down = property_animation_get_animation(property_anim_down);
 
    //Set characteristics
    animation_set_duration((Animation*) anim_up, duration);
    animation_set_duration((Animation*) anim_down, duration);
  
    // Define sequence
    Animation *anim = animation_sequence_create(anim_up, anim_down, NULL);
 
    //Set stopped handler to free memory
   /* AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);*/
 
    //Start animation!
    animation_set_play_count(anim, PLAY_COUNT_INFINITE);
    animation_schedule((Animation*) anim);
}

// Update time
/*void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);
}*/
