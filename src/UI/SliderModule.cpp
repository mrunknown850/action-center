#include "UI/SliderModule.hpp"
#include "Config/ConfigLoader.hpp"
#include "UI/Component.hpp"
#include <memory>
#include <string>
#include <utility>

SliderModule::SliderModule(std::string mod_name,
                           std::unique_ptr<ComponentInfo> comp_config)
    : Component::Component(std::move(mod_name), ComponentType::SLIDER,
                           std::move(comp_config)) {
  widget = &slider;
  slider.set_vexpand(false);
}
