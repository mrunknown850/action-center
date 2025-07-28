#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

// #include "UI/Window.hpp"
#include <json/json.h>
#include <json/value.h>
#include <unordered_map>

enum class MenuPosition;
struct ComponentInfo {
  std::pair<int, int> grid_column; // Follows CSS grid format
  std::pair<int, int> grid_row;    // Follows CSS grid format
  std::string module_id = "";      // ID for multiple instance of one mod
  std::string format;              // Default label
  Json::Value raw;                 // Raw config
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
