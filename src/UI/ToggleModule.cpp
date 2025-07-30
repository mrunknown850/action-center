#include "UI/ToggleModule.hpp"
#include "UI/Component.hpp"

ToggleModule::ToggleModule(std::string module_name,
                           std::unique_ptr<ComponentInfo> config)
    : Component::Component(std::move(module_name), ComponentType::TOGGLE,
                           std::move(config)) {
  widget = &toggle;
  toggle.set_label(config->format);
  toggle.set_vexpand(true);
}
