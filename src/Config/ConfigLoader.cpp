#include "Config/ConfigLoader.hpp"
#include "UI/Window.hpp"
#include <fstream>
#include <json/reader.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::vector<std::string> parse_list(const Json::Value &arr) {
  std::vector<std::string> res;
  res.reserve(arr.size());

  for (const auto &itm : arr)
    res.push_back(itm.asString());
  return res;
}

std::pair<int, int> parse_pair(const Json::Value &arr) {
  if (!arr.isArray() || arr.size() != 2)
    throw std::runtime_error("Expected array of 2 elements");
  return {arr[0].asInt(), arr[1].asInt()};
}

const std::unordered_map<std::string, ComponentInfo> &
Config::get_components_config() const {
  return components_config;
}

std::pair<int, int> Config::get_margin() const { return {x_margin, y_margin}; }
std::pair<int, int> Config::get_size() const { return {width, height}; }
std::pair<int, int> Config::get_gap() const { return {row_gap, col_gap}; }
MenuPosition Config::get_anchor() const { return anchor; }

Config::Config(const std::string &path) {
  // Setup stream
  std::ifstream file_inp(path);
  if (!file_inp)
    throw std::runtime_error("Failed to open config: " + path);

  // Parse config
  Json::CharReaderBuilder builder;
  std::string errs;
  if (!Json::parseFromStream(builder, file_inp, &root, &errs))
    throw std::runtime_error("Failed to parse: " + errs);
  parse_components();
}

void Config::parse_components() {
  // Setting up global configs
  auto margin_pair = parse_pair(root["margin"]);
  x_margin = margin_pair.first;
  y_margin = margin_pair.second;
  auto size_pair = parse_pair(root["size"]);
  width = size_pair.first;
  height = size_pair.second;
  auto gap_pair = parse_pair(root["gaps"]);
  row_gap = gap_pair.first;
  col_gap = gap_pair.second;

  // Get anchor
  auto anchor_str = root["anchor"].asString();
  if (anchor_str == "TOP")
    anchor = MenuPosition::TOP;
  else if (anchor_str == "LEFT")
    anchor = MenuPosition::LEFT;
  else if (anchor_str == "RIGHT")
    anchor = MenuPosition::RIGHT;
  else if (anchor_str == "BOTTOM")
    anchor = MenuPosition::BOTTOM;
  else if (anchor_str == "TOP_LEFT")
    anchor = MenuPosition::TOP_LEFT;
  else if (anchor_str == "TOP_RIGHT")
    anchor = MenuPosition::TOP_RIGHT;
  else if (anchor_str == "BOTTOM_LEFT")
    anchor = MenuPosition::BOTTOM_LEFT;
  else if (anchor_str == "BOTTOM_RIGHT")
    anchor = MenuPosition::BOTTOM_RIGHT;

  component_ids = parse_list(root["modules"]);

  for (const std::string &id : component_ids) {
    if (!root.isMember(id))
      throw std::runtime_error("Module '" + id + "' not found in JSON");
    ComponentInfo conf;
    conf.raw = root[id];
    conf.format = conf.raw["format"].asString();
    components_config[id] = conf;
  }
}
