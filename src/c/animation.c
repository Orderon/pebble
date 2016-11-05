#include <pebble.h>
#include "animation.h"



static void anim_started_handler(Animation *animation, void *context) {
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "Animation started!");
}

static void anim_stopped_handler(Animation *animation, bool finished, void *context) {
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "Animation stopped!");
   animation_destroy(animation);
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration){
    //Declare property animation
    PropertyAnimation *property_anim_up = property_animation_create_layer_frame(layer, start, finish);
    Animation *anim_up = property_animation_get_animation(property_anim_up);
    PropertyAnimation *property_anim_down = property_animation_create_layer_frame(layer, finish, start);
    Animation *anim_down = property_animation_get_animation(property_anim_down);
 
    //Set characteristics
    animation_set_duration((Animation*) anim_up, duration);
    animation_set_duration((Animation*) anim_down, duration);
  
    // Define sequence
    Animation *anim = animation_sequence_create(anim_up, anim_down, NULL);
 
    // Set some handlers
    animation_set_handlers(anim, (AnimationHandlers) {
    .started = anim_started_handler,
    .stopped = anim_stopped_handler
    }, NULL);
 
    //Start animation!
    animation_schedule((Animation*) anim);

}

