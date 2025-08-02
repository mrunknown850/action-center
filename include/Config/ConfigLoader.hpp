#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

// #include "UI/Window.hpp"
#include <json/json.h>
#include <json/value.h>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

struct Margin {
  int x, y;
};
struct Size {
  int width, height;
};
struct Gap {
  int row, col;
};

struct GridRange {
  int start, end;
};

enum class MenuPosition : std::int8_t;
struct ComponentInfo {
  GridRange grid_col;
  GridRange grid_row;
  std::string module_id = "";
  std::string format;
  std::shared_ptr<Json::Value> raw;

  ComponentInfo(std::shared_ptr<Json::Value> json_raw)
      : raw(std::move(json_raw)) {}
  ComponentInfo(ComponentInfo &&other) = default;
};

class ContainerInfo : public ComponentInfo {
private:
  Gap gap;
  std::vector<std::unique_ptr<ComponentInfo>> components;
  std::unordered_map<std::string, ComponentInfo *> component_lookup;
  mutable std::vector<ComponentInfo *> component_ptrs;

public:
  ContainerInfo(std::shared_ptr<Json::Value> json_raw)
      : ComponentInfo(std::move(json_raw)) {}
  ContainerInfo(ContainerInfo &&other) = default;

  void add_component(const std::string &id,
                     std::unique_ptr<ComponentInfo> comp);
  auto get_component_config(const std::string &id) const -> ComponentInfo *;
  auto get_component_configs() const -> const std::vector<ComponentInfo *> &;
};

class Config {
private:
  MenuPosition anchor;
  Margin margin;
  Size size;
  Gap gap;

  Json::Value root;

  std::vector<std::unique_ptr<ComponentInfo>> components;
  std::unordered_map<std::string, ComponentInfo *> component_lookup;
  mutable std::vector<ComponentInfo *> component_ptrs;

  void parse_config();
  void parse_components();

public:
  Config(const std::string &path);
  Config(Config &&other) = default;
  auto operator=(const Config &) -> Config & = delete;

  // Window's property getter
  auto get_margin() const -> Margin;
  auto get_size() const -> Size;
  auto get_gap() const -> Gap;
  auto get_anchor() const -> MenuPosition;

  // Component's getter
  auto get_component_config(const std::string &id) const -> ComponentInfo *;
  auto get_component_configs() const -> const std::vector<ComponentInfo *> &;
};

auto parse_pair(const Json::Value &arr) -> std::pair<int, int>;
auto parse_list(const Json::Value &arr) -> std::vector<std::string>;

#endif // !CONFIG_LOADER_HPP
