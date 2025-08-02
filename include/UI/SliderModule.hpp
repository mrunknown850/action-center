#ifndef SLIDER_MODULE_HPP
#define SLIDER_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/scale.h>

class SliderModule : public Component {
protected:
  Gtk::Scale slider;

public:
  SliderModule(std::string mod_name,
               std::unique_ptr<ComponentInfo> comp_config);
  SliderModule(SliderModule &&other) = default;

  auto get_type() const -> ComponentType override {
    return ComponentType::SLIDER;
  };
  ~SliderModule() override = default;
};

#endif
