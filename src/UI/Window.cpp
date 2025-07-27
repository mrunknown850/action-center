#include "UI/Window.hpp"

Window::Window(float x, float y, float w, float h, int row, int col) {
  set_decorated(false);
  set_hide_on_close(true);
  set_resizable(false);

  set_default_size(w, h);
  show();
}
