#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <json/json.h>
#include <json/value.h>
#include <unordered_map>

struct GeneralInfo {
  float x, y, w, h;
  int row_count, col_count;

  std::vector<std::string> component_ids;
};

struct ComponentInfo {
  std::string format;
  Json::Value raw;
};

class Config {
private:
  Json::Value root;
  GeneralInfo general_config;
  std::unordered_map<std::string, ComponentInfo> components_config;

  void parse_components();

public:
  Config(const std::string &path);
  const std::unordered_map<std::string, ComponentInfo> &
  get_components_config() const;

  std::pair<float, float> get_position() const;
  std::pair<float, float> get_size() const;
  std::pair<int, int> get_layout() const;
  std::span<const std::string> get_components_id() const;
};

#endif // !CONFIG_LOADER_HPP
