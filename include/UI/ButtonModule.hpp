#ifndef BUTTON_MODULE_HPP
#define BUTTON_MODULE_HPP

#include "UI/Component.hpp"
#include "gtkmm/button.h"

class ButtonModule : public Component {
protected:
  Gtk::Button button;

public:
  // Override pure functions
  ButtonModule(std::string mod_name,
               std::unique_ptr<ComponentInfo> comp_config);
  ButtonModule(ButtonModule &&other) noexcept = default;

  auto get_type() const -> ComponentType override {
    return ComponentType::BUTTON;
  }
  ~ButtonModule() override = default;
};

#endif
