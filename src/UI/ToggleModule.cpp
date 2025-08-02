#include "UI/ToggleModule.hpp"
#include "Config/ConfigLoader.hpp"
#include "UI/Component.hpp"
#include <memory>
#include <string>
#include <utility>

ToggleModule::ToggleModule(std::string name,
                           std::unique_ptr<ComponentInfo> in_config)
    : Component::Component(std::move(name), ComponentType::TOGGLE,
                           std::move(in_config)) {
  widget = &toggle;
  toggle.set_label(config->format);
  toggle.set_vexpand(true);
}
