#include <pebble.h>

static Window *screen2_window;
static TextLayer *screen2_text_layer;

static void screen2_selectClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen2_text_layer, "2 Select");
}

static void screen2_upClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen2_text_layer, "2 Up");
}

static void screen2_downClickHandler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(screen2_text_layer, "2 Down");
}

static void screen2_clickConfigProvider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, screen2_selectClickHandler);
  window_single_click_subscribe(BUTTON_ID_UP, screen2_upClickHandler);
  window_single_click_subscribe(BUTTON_ID_DOWN, screen2_downClickHandler);
}

static void screen2_windowLoad(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  screen2_text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(screen2_text_layer, "Second screen!!!");
  text_layer_set_text_alignment(screen2_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(screen2_text_layer));
}

static void screen2_windowUnload(Window *window) {
  text_layer_destroy(screen2_text_layer);
}

static Window * screen2_getWindow(void) {
  screen2_window = window_create();
  window_set_click_config_provider(screen2_window, screen2_clickConfigProvider);
  window_set_window_handlers(screen2_window, (WindowHandlers) {
	  .load = screen2_windowLoad,
    .unload = screen2_windowUnload,
  });
  return screen2_window;
}

static void screen2_destroyWindow(void) {
  window_destroy(screen2_window);
}