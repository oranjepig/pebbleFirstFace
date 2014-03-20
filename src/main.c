#include <pebble.h>

Window *my_window;
TextLayer *top_layer;


static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  
  char *timestring = "00 00";
  strftime(timestring, 80, "%I:%M %p", tick_time); //get the time
  text_layer_set_text(top_layer, timestring);
  
 }

void handle_init(void) {
    my_window = window_create();
    window_stack_push(my_window, true);
    top_layer = text_layer_create(GRect(0, 0, 144, 50));
    text_layer_set_text_alignment(top_layer, GTextAlignmentCenter);

    text_layer_set_background_color(top_layer, GColorBlack);
    text_layer_set_text_color(top_layer, GColorWhite);
    text_layer_set_font(top_layer, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
    layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(top_layer));
    text_layer_set_text(top_layer, "hi!");
    tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  } 


void handle_deinit(void) {
	  tick_timer_service_unsubscribe();
     text_layer_destroy(top_layer);
	  window_destroy(my_window);
  
}

int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}
