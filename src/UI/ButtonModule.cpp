#include "UI/ButtonModule.hpp"
#include "Config/ConfigLoader.hpp"
#include "UI/Component.hpp"
#include <gtkmm/button.h>
#include <memory>
#include <string>
#include <utility>

ButtonModule::ButtonModule(std::string mod_name,
                           std::unique_ptr<ComponentInfo> comp_config)
    : Component::Component(std::move(mod_name), ComponentType::BUTTON,
                           std::move(comp_config)) {
  widget = &button;
  button.set_label(config->format);
  button.set_vexpand(true);
}
