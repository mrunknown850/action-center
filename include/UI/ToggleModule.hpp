#ifndef TOGGLE_MODULE_HPP
#define TOGGLE_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/togglebutton.h>

class ToggleModule : public Component {
protected:
  Gtk::ToggleButton toggle;

public:
  ToggleModule(std::string module_name, std::unique_ptr<ComponentInfo> config);
  ToggleModule(ToggleModule &&other) = default;

  ComponentType get_type() const override { return ComponentType::TOGGLE; };
  ~ToggleModule() override = default;
};
#endif
