/*---------------------------------------------------------------------------
message.h
Authors: Lucie Houel
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

#pragma once
#define DIALOG_MESSAGE_WINDOW_MARGIN 10
#define DIALOG_MESSAGE_WINDOW_MESSAGE "you ran 10000 steps !"

static void anim_stopped_handler(Animation *animation, bool finished, void *context);

static void background_update_proc(Layer *layer, GContext *ctx);

static void icon_update_proc(Layer *layer, GContext *ctx);

static void window_load(Window *window);

static void window_unload(Window *window);

static void window_appear(Window *window);

void dialog_message_window_push();