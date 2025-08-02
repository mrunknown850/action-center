#include "UI/Component.hpp"
#include "Config/ConfigLoader.hpp"
#include <memory>
#include <string>
#include <utility>

Component::Component(std::string name, ComponentType comp_type,
                     std::unique_ptr<ComponentInfo> in_config)
    : module_name(std::move(name)), type(comp_type),
      config(std::move(in_config)) {}
