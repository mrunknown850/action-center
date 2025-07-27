#include "UI/Window.hpp"
#include "glibmm/refptr.h"
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <gtkmm/gridlayout.h>
#include <gtkmm/object.h>

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

Window::Window(MenuPosition anchor, int x_margin, int y_margin, int width,
               int height, int col_gap, int row_gap)
    : anchor(anchor), xm(x_margin), ym(y_margin), width(width), height(height),
      parent(nullptr), col_gap(col_gap), row_gap(row_gap) {
  // Setup popup
  set_decorated(false);
  set_hide_on_close(true);
  set_resizable(false);

  set_default_size(width, height);
  gtk_layer_init_for_window(this->gobj());
  setup_anchoring();

  // Setup grid
  auto layout = Gtk::GridLayout::create();
  layout->set_column_spacing(col_gap);
  layout->set_row_spacing(row_gap);
  set_layout_manager(layout);
  show();
}
