#include "UI/Component.hpp"

Component::Component(std::string module_name, ComponentType type,
                     ComponentInfo config)
    : module_name(module_name), type(type), config(config), widget(nullptr) {}
Component::Component(Component &&other)
    : module_name(std::move(other.module_name)), type(other.type),
      config(std::move(other.config)), widget(std::move(other.widget)) {}
