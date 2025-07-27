#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <Config/ConfigLoader.hpp>
#include <gtkmm/widget.h>

enum class ComponentType { BUTTON, TOGGLE, SLIDER };

class Component {
protected:
  ComponentType type;
  ComponentInfo config;
  std::string class_name;

public:
  virtual ComponentType get_type();
  virtual ~Component() = default;
};

class Toggle : public Component {
public:
  ComponentType get_type() { return ComponentType::TOGGLE; }
};

#endif // !COMPONENT_HPP
