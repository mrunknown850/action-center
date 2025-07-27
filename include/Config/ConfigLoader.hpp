#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include "UI/Window.hpp"
#include <json/json.h>
#include <json/value.h>
#include <unordered_map>

struct ComponentInfo {
  std::string format;
  Json::Value raw;
};

class Config {
private:
  MenuPosition anchor;
  int x_margin, y_margin, width, height, col_gap, row_gap;
  std::vector<std::string> component_ids;

  Json::Value root;
  std::unordered_map<std::string, ComponentInfo> components_config;

  void parse_components();

public:
  Config(const std::string &path);
  std::pair<int, int> get_margin() const;
  std::pair<int, int> get_size() const;
  std::pair<int, int> get_gap() const;
  MenuPosition get_anchor() const;
  const std::unordered_map<std::string, ComponentInfo> &
  get_components_config() const;
  const std::vector<std::string> &get_components_id() const;
};

#endif // !CONFIG_LOADER_HPP
