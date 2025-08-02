#ifndef WINDOW_LOADER_HPP
#define WINDOW_LOADER_HPP

#include "Config/ConfigLoader.hpp"
#include "UI/Component.hpp"
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <memory>

enum class MenuPosition : std::int8_t {
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
  Margin margin;
  Size size;
  Gap gap;

  void setup_anchoring();

public:
  Window(MenuPosition anchor, Margin, Size, Gap);
  ~Window() override = default;

  void add_component(std::unique_ptr<Component> comp);
};

#endif // !WINDOW_LOADER_HPP
