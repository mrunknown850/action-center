#ifndef CONTAINER_MODULE_HPP
#define CONTAINER_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/grid.h>

class ContainerModule final : public Component {
protected:
  Gtk::Grid container;

public:
  ContainerModule(std::string mod_name,
                  std::unique_ptr<ContainerInfo> cont_config);
  ContainerModule(ContainerModule &&other) = default;

  auto get_type() const -> ComponentType override {
    return ComponentType::CONTAINER;
  }
  ~ContainerModule() override = default;

  void add_component(std::unique_ptr<Component> comp);
};

#endif
