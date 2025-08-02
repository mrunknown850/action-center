#include "UI/ContainerModule.hpp"
#include "Config/ConfigLoader.hpp"
#include "UI/Component.hpp"
#include <memory>
#include <string>
#include <utility>

ContainerModule::ContainerModule(std::string mod,
                                 std::unique_ptr<ContainerInfo> cont_config)
    : Component::Component(std::move(mod), ComponentType::CONTAINER,
                           std::move(cont_config)) {
  widget = &container;
  // auto gaps = parse_pair(config.raw["gaps"]);
  // container.set_row_spacing(gaps.first);
  // container.set_column_spacing(gaps.second);
}

void ContainerModule::add_component(std::unique_ptr<Component> comp) {
  const ComponentInfo *container_config = comp->get_config();
  int width = container_config->grid_col.end - container_config->grid_col.start;
  int height =
      container_config->grid_row.end - container_config->grid_row.start;
  // Ensure at least 1
  if (width <= 0)
    width = 1;
  if (height <= 0)
    height = 1;
  container.attach(comp->get_widget(), container_config->grid_col.start,
                   container_config->grid_row.start, width, height);
}
