#include "Config/ConfigLoader.hpp"
#include "UI/Window.hpp"
#include <fstream>
#include <json/reader.h>
#include <memory>
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

ComponentInfo *Config::get_component_config(const std::string &id) const {
  return component_lookup.at(id);
}

const std::vector<ComponentInfo *> &Config::get_component_configs() const {
  if (component_ptrs.empty()) {
    component_ptrs.reserve(component_ptrs.size());
    for (const auto &comp : components) {
      component_ptrs.push_back(comp.get());
    }
  }
  return component_ptrs;
}

Margin Config::get_margin() const { return margin; }
Size Config::get_size() const { return size; }
Gap Config::get_gap() const { return gap; }
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

void Config::parse_config() {
  // Setting up global configs
  auto margin_pair = parse_pair(root["margin"]);
  margin.x = margin_pair.first;
  margin.y = margin_pair.second;
  auto size_pair = parse_pair(root["size"]);
  size.width = size_pair.first;
  size.height = size_pair.second;
  auto gap_pair = parse_pair(root["gaps"]);
  gap.row = gap_pair.first;
  gap.col = gap_pair.second;

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

  parse_components();
}

std::unique_ptr<ContainerInfo>
parse_container(const Json::Value &root, const std::string &container_id) {
  auto container = std::make_unique<ContainerInfo>(
      std::make_shared<Json::Value>(root[container_id]));
  auto container_raw = root[container_id];

  container->module_id = container_id;
  container->format = container_raw["format"].asString();
  auto grid_col = parse_pair(container_raw["grid-column"]);
  auto grid_row = parse_pair(container_raw["grid-row"]);
  container->grid_col.start = grid_col.first;
  container->grid_col.end = grid_col.second;
  container->grid_row.start = grid_row.first;
  container->grid_row.end = grid_row.second;

  auto sub_mods = parse_list(container_raw["modules"]);
  for (const auto &id : sub_mods) {
    const Json::Value &submod_raw = root[id];
    std::string type = submod_raw["type"].asString();
    if (type == "CONTAINER") {
      auto sub_container = parse_container(root, id);
      container->add_component(id, std::move(sub_container));
    } else {
      auto comp = std::make_unique<ComponentInfo>(
          std::make_shared<Json::Value>(submod_raw));
      comp->module_id = id;
      comp->format = submod_raw["format"].asString();
      auto sub_grid_col = parse_pair(submod_raw["grid-column"]);
      auto sub_grid_row = parse_pair(submod_raw["grid-row"]);
      comp->grid_col.start = sub_grid_col.first;
      comp->grid_col.end = sub_grid_col.second;
      comp->grid_row.start = sub_grid_row.first;
      comp->grid_row.end = sub_grid_row.second;
      container->add_component(id, std::move(comp));
    }
  }
  return container;
}

void ContainerInfo::add_component(const std::string &id,
                                  std::unique_ptr<ComponentInfo> comp) {

  component_lookup[id] = comp.get();
  components.push_back(std::move(comp));
}

void Config::parse_components() {
  for (const auto &id : parse_list(root["modules"])) {
    const auto &raw_module = root[id];
    auto type = raw_module["type"].asString();
    if (type == "CONTAINER") {
      auto sub = parse_container(root, id);
      component_lookup[id] = sub.get();
      components.push_back(std::move(sub));
    } else {
      auto comp = std::make_unique<ComponentInfo>(
          std::make_shared<Json::Value>(raw_module));
      comp->module_id = id;
      comp->format = raw_module["format"].asString();
      auto sub_grid_col = parse_pair(raw_module["grid-column"]);
      auto sub_grid_row = parse_pair(raw_module["grid-row"]);
      comp->grid_col.start = sub_grid_col.first;
      comp->grid_col.end = sub_grid_col.second;
      comp->grid_row.start = sub_grid_row.first;
      comp->grid_row.end = sub_grid_row.second;
      component_lookup[id] = comp.get();
      components.push_back(std::move(comp));
    }
  }
}
