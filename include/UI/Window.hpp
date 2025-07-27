#ifndef WINDOW_LOADER_HPP
#define WINDOW_LOADER_HPP

#include <gtkmm/window.h>

class Window : public Gtk::Window {
private:
  float x, y, w, h;
  int grid_row, grid_col;

public:
  Window(float x, float y, float w, float h, int row, int col);
  ~Window() override = default;
};

#endif // !WINDOW_LOADER_HPP
