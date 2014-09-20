#include <pebble.h>
#include <screen1.c>

int main(void) {
  window_stack_push(screen1_getWindow(), true);
  app_event_loop();
  screen1_destroyWindow();
}