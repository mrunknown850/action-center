#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Config/ConfigLoader.hpp"
#include <gtkmm/widget.h>

enum class ComponentType : std::int8_t {
  BUTTON,
  TOGGLE,
  SLIDER,
  CONTAINER,
  LABEL
};

class Window;
class Component {
protected:
  // Name format: [module_name]#[config.module_id]
  std::string module_name;
  ComponentType type;
  std::unique_ptr<ComponentInfo> config;
  Gtk::Widget *widget = nullptr;

public:
  Component(std::string name, ComponentType comp_type,
            std::unique_ptr<ComponentInfo> in_config);
  Component(Component &&other) noexcept = default;

  virtual ~Component() = default;

  // Getter
  [[nodiscard]] virtual auto get_type() const -> ComponentType = 0;
  auto get_widget() -> Gtk::Widget & { return *widget; }
  [[nodiscard]] virtual auto get_config() const -> const ComponentInfo * final {
    return config.get();
  }
};

#endif // !COMPONENT_HPP
