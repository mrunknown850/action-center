#include "UI/Window.hpp"
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <iostream>

Window::Window(MenuPosition anchor, int x_margin, int y_margin, float width,
               float height, int row, int col)
    : w(width), h(height), grid_row(row), grid_col(col), parent(nullptr)
{
  // Setup popup
  set_decorated(false);
  set_hide_on_close(true);
  set_resizable(false);

  set_default_size(w, h);

  gtk_layer_init_for_window(this->gobj());

  // TOP SETUP
  if (anchor == MenuPosition::TOP || anchor == MenuPosition::TOP_LEFT ||
      anchor == MenuPosition::TOP_RIGHT)
  {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, y_margin);
    std::cout << "TOP";
  }

  // BOTTOM SETUP
  if (anchor == MenuPosition::BOTTOM || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::BOTTOM_RIGHT)
  {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, y_margin);
    std::cout << "BOTTOM";
  }

  // RIGHT SETUP
  if (anchor == MenuPosition::RIGHT || anchor == MenuPosition::BOTTOM_RIGHT ||
      anchor == MenuPosition::TOP_RIGHT)
  {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, x_margin);
    std::cout << "RIGHT";
  }

  // LEFT SETUP
  if (anchor == MenuPosition::LEFT || anchor == MenuPosition::BOTTOM_LEFT ||
      anchor == MenuPosition::TOP_LEFT)
  {
    gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
    gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, x_margin);
    std::cout << "LEFT";
  }

  std::cout << std::endl;

  show();
}
