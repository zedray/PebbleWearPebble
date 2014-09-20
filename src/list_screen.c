#include "pebble.h"

#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 5

static Window *list_screen_window;
static MenuLayer *list_screen_menu_layer;

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return NUM_FIRST_MENU_ITEMS;
}
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 0;
}
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Basic Item 1", "With a very long subtitle that can take the whole screen", NULL);
          break;
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "Basic Item 2", "Short stuff", NULL);
          break;
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Basic Item 3", "With a subtitle that is also long", NULL);
          break;
        case 3:
          menu_cell_basic_draw(ctx, cell_layer, "Basic Item 4", "With a subtitle...", NULL);
          break;
        case 4:
          menu_cell_basic_draw(ctx, cell_layer, "Basic Item 5", "With a subtitle...", NULL);
          break;
      }
      break;
  }
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->row) {
    case 0:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Item 0 selected");
    break;
    case 1:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Item 1 selected");
    break;
  }
}

void list_screen_window_load(Window *window) {
  // Now we prepare to initialize the menu layer
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  list_screen_menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(list_screen_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(list_screen_menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(list_screen_menu_layer));
}

void list_screen_window_unload(Window *window) {
  menu_layer_destroy(list_screen_menu_layer);
}

static Window * list_screen_getWindow(void) {
  list_screen_window = window_create();

  window_set_window_handlers(list_screen_window, (WindowHandlers) {
    .load = list_screen_window_load,
    .unload = list_screen_window_unload,
  });
  return list_screen_window;
}

static void list_screen_destroyWindow(void) {
  window_destroy(list_screen_window);
}
