#include "UI/SliderModule.hpp"

SliderModule::SliderModule(std::string module_name, const ComponentInfo &config)
    : Component::Component(std::move(module_name), ComponentType::SLIDER,
                           config) {
  widget = &slider;
  slider.set_vexpand(false);
}
