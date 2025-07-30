#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

// #include "UI/Window.hpp"
#include <json/json.h>
#include <json/value.h>
#include <memory>
#include <unordered_map>

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

enum class MenuPosition;
struct ComponentInfo {
  GridRange grid_col;
  GridRange grid_row;
  std::string module_id = "";
  std::string format;
  std::shared_ptr<Json::Value> raw;

  ComponentInfo(std::shared_ptr<Json::Value> raw) : raw(raw) {}
  ComponentInfo(ComponentInfo &&other) = default;
};

class ContainerInfo : public ComponentInfo {
private:
  Gap gap;
  std::vector<std::unique_ptr<ComponentInfo>> components;
  std::unordered_map<std::string, ComponentInfo *> component_lookup;
  mutable std::vector<ComponentInfo *> component_ptrs;

public:
  ContainerInfo(std::shared_ptr<Json::Value> raw) : ComponentInfo(raw) {}
  ContainerInfo(ContainerInfo &&other) = default;

  void add_component(const std::string &id,
                     std::unique_ptr<ComponentInfo> comp);
  ComponentInfo *get_component_config(const std::string &id) const;
  const std::vector<ComponentInfo *> &get_component_configs() const;
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
  Config &operator=(const Config &) = delete;

  // Window's property getter
  Margin get_margin() const;
  Size get_size() const;
  Gap get_gap() const;
  MenuPosition get_anchor() const;

  // Component's getter
  ComponentInfo *get_component_config(const std::string &id) const;
  const std::vector<ComponentInfo *> &get_component_configs() const;
};

std::pair<int, int> parse_pair(const Json::Value &arr);

#endif // !CONFIG_LOADER_HPP
