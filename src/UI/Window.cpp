#include "UI/Window.hpp"
#include "UI/Component.hpp"
#include "Config/ConfigLoader.hpp"
#include "glib.h"
#include <gtk4-layer-shell.h>
#include <memory>

void Window::setup_anchoring() {
  if (anchor == MenuPosition::TOP || anchor == MenuPosition::TOP_LEFT ||
      anchor == MenuPosition::TOP_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP,
                         static_cast<gboolean>(true));
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, margin.y);
  }

  // BOTTOM SETUP
  if (anchor == MenuPosition::BOTTOM || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::BOTTOM_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM,
                         static_cast<gboolean>(true));
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, margin.y);
  }

  // RIGHT SETUP
  if (anchor == MenuPosition::RIGHT || anchor == MenuPosition::BOTTOM_RIGHT ||
      anchor == MenuPosition::TOP_RIGHT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT,
                         static_cast<gboolean>(true));
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, margin.x);
  }

  // LEFT SETUP
  if (anchor == MenuPosition::LEFT || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::TOP_LEFT) {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT,
                         static_cast<gboolean>(true));
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, margin.x);
  }
}

#include <iostream>

Window::Window(MenuPosition anchor, Margin margin, Size size, Gap gap)
    : anchor(anchor), margin(margin), size(size), gap(gap) {
  std::cout << "Setting up variables" << '\n';
  // Setup popup
  set_decorated(false);
  set_hide_on_close(true);
  set_resizable(false);

  set_default_size(size.width, size.height);
  gtk_layer_init_for_window(this->gobj());
  setup_anchoring();

  // Setup grid
  std::cout << "Setting up grids" << '\n';
  root.set_column_spacing(gap.col);
  root.set_row_spacing(gap.row);
  root.set_column_homogeneous(true);
  set_child(root);

  std::cout << "Finished config window" << '\n';
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
