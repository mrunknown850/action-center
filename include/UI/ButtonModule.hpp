#ifndef BUTTON_MODULE_HPP
#define BUTTON_MODULE_HPP

#include "UI/Component.hpp"
#include "gtkmm/button.h"

class ButtonModule : public Component {
protected:
  Gtk::Button button;

public:
  // Override pure functions
  ButtonModule(std::string module_name, std::unique_ptr<ComponentInfo> config);
  ButtonModule(ButtonModule &&other) = default;

  ComponentType get_type() const override { return ComponentType::BUTTON; }
  ~ButtonModule() override = default;
};

#endif
