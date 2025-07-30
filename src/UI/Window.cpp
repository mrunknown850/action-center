#include "UI/Window.hpp"
#include "Config/ConfigLoader.hpp"
#include <glibmm/refptr.h>
#include <gtk4-layer-shell.h>
#include <gtkmm/object.h>
#include <memory>

void Window::setup_anchoring() {
  if (anchor == MenuPosition::TOP || anchor == MenuPosition::TOP_LEFT ||
      anchor == MenuPosition::TOP_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, ym);
  }

  // BOTTOM SETUP
  if (anchor == MenuPosition::BOTTOM || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::BOTTOM_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, ym);
  }

  // RIGHT SETUP
  if (anchor == MenuPosition::RIGHT || anchor == MenuPosition::BOTTOM_RIGHT ||
      anchor == MenuPosition::TOP_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, xm);
  }

  // LEFT SETUP
  if (anchor == MenuPosition::LEFT || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::TOP_LEFT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, xm);
  }
}

#include <iostream>

Window::Window(MenuPosition anchor, int x_margin, int y_margin, int width,
               int height, int col_gap, int row_gap)
    : anchor(anchor), xm(x_margin), ym(y_margin), width(width), height(height),
      parent(nullptr), col_gap(col_gap), row_gap(row_gap) {
  std::cout << "Setting up variables" << std::endl;
  // Setup popup
  set_decorated(false);
  set_hide_on_close(true);
  set_resizable(false);

  set_default_size(width, height);
  gtk_layer_init_for_window(this->gobj());
  setup_anchoring();

  // Setup grid
  std::cout << "Setting up grids" << std::endl;
  root.set_column_spacing(col_gap);
  root.set_row_spacing(row_gap);
  root.set_column_homogeneous(true);
  set_child(root);

  std::cout << "Finished config window" << std::endl;
  show();
}

void Window::add_component(std::unique_ptr<Component> comp) {
  const ComponentInfo *config = comp->get_config();
  int width = config->grid_col.end - config->grid_col.start;
  int height = config->grid_row.end - config->grid_row.start;
  // Ensure at least 1
  if (width <= 0)
    width = 1;
  if (height <= 0)
    height = 1;
  root.attach(comp->get_widget(), config->grid_col.start,
              config->grid_row.start, width, height);
}
