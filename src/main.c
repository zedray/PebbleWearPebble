#include <pebble.h>
#include <list_screen.c>

int main(void) {
  window_stack_push(list_screen_getWindow(), true);
  app_event_loop();
  list_screen_destroyWindow();
}