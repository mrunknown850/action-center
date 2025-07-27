#include "Config/ConfigLoader.hpp"
#include <fstream>
#include <json/reader.h>
#include <span>
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

std::pair<float, float> parse_float_pair(const Json::Value &arr) {
  if (!arr.isArray() || arr.size() != 2)
    throw std::runtime_error("Expected array of 2 elements");
  return {arr[0].asFloat(), arr[1].asFloat()};
}

std::pair<int, int> parse_int_pair(const Json::Value &arr) {
  if (!arr.isArray() || arr.size() != 2)
    throw std::runtime_error("Expected array of 2 elements");
  return {arr[0].asInt(), arr[1].asInt()};
}

const std::unordered_map<std::string, ComponentInfo> &
Config::get_components_config() const {
  return components_config;
}

std::pair<float, float> Config::get_position() const { return {x, y}; }
std::pair<float, float> Config::get_size() const { return {w, h}; }
std::pair<int, int> Config::get_layout() const {
  return {row_count, col_count};
}
std::span<const std::string> Config::get_components_id() const {
  return std::span<const std::string>(component_ids);
}

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
  std::pair<float, float> xy = parse_float_pair(root["position"]);
  std::pair<float, float> wh = parse_float_pair(root["size"]);
  std::pair<int, int> cells = parse_int_pair(root["cells"]);
  x = xy.first;
  y = xy.second;
  w = wh.first;
  h = wh.second;
  row_count = cells.first;
  col_count = cells.second;
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
