#ifndef WINDOW_LOADER_HPP
#define WINDOW_LOADER_HPP

#include "UI/Component.hpp"
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <memory>

enum class MenuPosition {
  TOP,
  LEFT,
  RIGHT,
  BOTTOM,
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT
};

class Window : public Gtk::Window {
private:
  Gtk::Grid root;
  MenuPosition anchor;
  int xm, ym, width, height, col_gap, row_gap;

  Window *parent;

  void setup_anchoring();

public:
  Window(MenuPosition anchor, int x_margin, int y_margin, int width, int height,
         int col_gap, int row_gap);
  ~Window() override = default;

  void add_component(std::unique_ptr<Component> comp);
};

#endif // !WINDOW_LOADER_HPP
