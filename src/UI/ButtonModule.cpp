#include "UI/ButtonModule.hpp"
#include <gtkmm/button.h>
#include <gtkmm/object.h>

ButtonModule::ButtonModule(std::string module_name, ComponentType type,
                           const ComponentInfo& config)
    : Component::Component(std::move(module_name), type, config) {
  widget = &button;
  button.set_label(config.format);
}
