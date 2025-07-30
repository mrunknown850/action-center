#include "UI/ButtonModule.hpp"
#include <gtkmm/button.h>
#include <gtkmm/object.h>

ButtonModule::ButtonModule(std::string module_name,
                           std::unique_ptr<ComponentInfo> config)
    : Component::Component(std::move(module_name), ComponentType::BUTTON,
                           std::move(config)) {
  widget = &button;
  button.set_label(config->format);
  button.set_vexpand(true);
}
