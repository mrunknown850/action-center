#ifndef SLIDER_MODULE_HPP
#define SLIDER_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/scale.h>

class SliderModule : public Component {
protected:
  Gtk::Scale slider;

public:
  SliderModule(std::string module_name, std::unique_ptr<ComponentInfo> config);
  SliderModule(SliderModule &&other) = default;

  ComponentType get_type() const override { return ComponentType::SLIDER; };
  ~SliderModule() override = default;
};

#endif
