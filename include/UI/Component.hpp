#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Config/ConfigLoader.hpp"
#include <gtkmm/widget.h>

enum class ComponentType { BUTTON, TOGGLE, SLIDER, CONTAINER, LABEL };

class Window;
class Component {
protected:
  // Name format: [module_name]#[config.module_id]
  std::string module_name;
  ComponentType type;
  std::unique_ptr<ComponentInfo> config;
  Gtk::Widget *widget = nullptr;

public:
  Component(std::string module_name, ComponentType type,
            std::unique_ptr<ComponentInfo> config);
  Component(Component &&other);

  virtual ~Component() = default;

  // Getter
  virtual ComponentType get_type() const = 0;
  Gtk::Widget &get_widget() { return *widget; }
  virtual const ComponentInfo *get_config() const final { return config.get(); }
};

#endif // !COMPONENT_HPP
