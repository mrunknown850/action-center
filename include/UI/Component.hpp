#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Config/ConfigLoader.hpp"
#include <gtkmm/widget.h>

enum class ComponentType { BUTTON, TOGGLE, SLIDER };

class Window;
class Component {
protected:
  // Name format: [module_name]#[config.module_id]
  std::string module_name;
  ComponentType type;
  ComponentInfo config;
  Gtk::Widget *widget = nullptr;

public:
  Component(std::string module_name, ComponentType type, ComponentInfo config);
  Component(Component &&other);

  virtual ~Component() = default;

  // Getter
  virtual ComponentType get_type() const = 0;
  Gtk::Widget &get_widget() { return *widget; }
  virtual const ComponentInfo &get_config() const final { return config; }
};

#endif // !COMPONENT_HPP
