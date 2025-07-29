#include "UI/ToggleModule.hpp"
#include "UI/Component.hpp"

ToggleModule::ToggleModule(std::string module_name, const ComponentInfo &config)
    : Component::Component(std::move(module_name), ComponentType::TOGGLE,
                           config) {
  widget = &toggle;
  toggle.set_label(config.format);
  toggle.set_vexpand(true);
}
