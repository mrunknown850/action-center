#ifndef WINDOW_LOADER_HPP
#define WINDOW_LOADER_HPP

#include <gtkmm/grid.h>
#include <gtkmm/window.h>

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
  int x, y;
  float w, h;
  int grid_row, grid_col;

  Window *parent;
  Gtk::Grid grid;

public:
  Window(MenuPosition anchor, int x_margin, int y_margin, float width,
         float height, int row, int col);
  ~Window() override = default;
};

#endif // !WINDOW_LOADER_HPP
