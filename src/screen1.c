#include <pebble.h>
#include <screen2.c>

static Window *screen1_window;
static TextLayer *screen1_text_layer;

static void logsomething() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "logsomething was just run!");
}

static void screen1_selectClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen1_text_layer, "Select");
  logsomething();
  window_stack_push(screen2_getWindow(), true);
}

static void screen1_upClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen1_text_layer, "Up");
  logsomething();
}

static void screen1_downClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen1_text_layer, "Down");
  logsomething();
}

static void screen1_clickConfigProvider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, screen1_selectClickHandler);
  window_single_click_subscribe(BUTTON_ID_UP, screen1_upClickHandler);
  window_single_click_subscribe(BUTTON_ID_DOWN, screen1_downClickHandler);
}

static void screen1_windowLoad(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  screen1_text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(screen1_text_layer, "Press a button");
  text_layer_set_text_alignment(screen1_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(screen1_text_layer));
}

static void screen1_windowUnload(Window *window) {
  text_layer_destroy(screen1_text_layer);
}

static Window * screen1_getWindow(void) {
  screen1_window = window_create();
  window_set_click_config_provider(screen1_window, screen1_clickConfigProvider);
  window_set_window_handlers(screen1_window, (WindowHandlers) {
	  .load = screen1_windowLoad,
    .unload = screen1_windowUnload,
  });
  return screen1_window;
}

static void screen1_destroyWindow(void) {
  window_destroy(screen1_window);
}