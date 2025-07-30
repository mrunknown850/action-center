#include "UI/SliderModule.hpp"

SliderModule::SliderModule(std::string module_name,
                           std::unique_ptr<ComponentInfo> config)
    : Component::Component(std::move(module_name), ComponentType::SLIDER,
                           std::move(config)) {
  widget = &slider;
  slider.set_vexpand(false);
}
