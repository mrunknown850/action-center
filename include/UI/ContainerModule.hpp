#ifndef CONTAINER_MODULE_HPP
#define CONTAINER_MODULE_HPP

#include "UI/Component.hpp"
#include <gtkmm/grid.h>

class ContainerModule final : public Component {
protected:
  Gtk::Grid container;

public:
  ContainerModule(std::string module_name,
                  std::unique_ptr<ContainerInfo> config);
  ContainerModule(ContainerModule &&other) = default;

  ComponentType get_type() const override { return ComponentType::CONTAINER; }
  ~ContainerModule() override = default;

  void add_component(std::unique_ptr<Component> comp);
};

#endif
