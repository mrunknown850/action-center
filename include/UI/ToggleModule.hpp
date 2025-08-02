#ifndef TOGGLE_MODULE_HPP
#define TOGGLE_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/togglebutton.h>

class ToggleModule : public Component {
protected:
  Gtk::ToggleButton toggle;

public:
  ToggleModule(std::string name, std::unique_ptr<ComponentInfo> in_config);
  ToggleModule(ToggleModule &&other) = default;

  auto get_type() const -> ComponentType override {
    return ComponentType::TOGGLE;
  };
  ~ToggleModule() override = default;
};
#endif
