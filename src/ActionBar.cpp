#include "Config/ConfigLoader.hpp"
#include "UI/ButtonModule.hpp"
#include "UI/SliderModule.hpp"
#include "UI/ToggleModule.hpp"
#include "UI/Window.hpp"
#include <gtkmm/application.h>
#include <iostream>

class ActionBar : public Gtk::Application {
public:
  static Glib::RefPtr<ActionBar> create(const Config &config) {
    return Glib::RefPtr<ActionBar>(new ActionBar(config));
  }

  ActionBar(const Config &config)
      : Gtk::Application("org.mrunknown850.action-menu"), config(config) {
    std::cout << "ActionBar constructed" << std::endl;
  }

protected:
  void on_activate() override {
    std::cout << "Generating windows..." << std::endl;
    auto xy_pair = config.get_margin();
    auto wh_pair = config.get_size();
    auto gap_pair = config.get_gap();
    auto win = new Window(config.get_anchor(), xy_pair.first, xy_pair.second,
                          wh_pair.first, wh_pair.second, gap_pair.first,
                          gap_pair.second);

    const std::unordered_map<std::string, ComponentInfo> &mod_configs =
        config.get_components_config();
    for (std::string widget_id : config.get_components_id()) {
      std::string type = mod_configs.at(widget_id).raw["type"].asString();
      if (type == "BUTTON") {
        std::cout << "Created btn: " << widget_id << std::endl;
        auto btn = std::make_unique<ButtonModule>(widget_id,
                                                  mod_configs.at(widget_id));
        win->add_component(std::move(btn));
      } else if (type == "TOGGLE") {

        std::cout << "Created toggle: " << widget_id << std::endl;
        auto tog = std::make_unique<ToggleModule>(widget_id,
                                                  mod_configs.at(widget_id));
        win->add_component(std::move(tog));
      } else if (type == "SLIDER") {

        std::cout << "Created slider: " << widget_id << std::endl;
        auto sli = std::make_unique<SliderModule>(widget_id,
                                                  mod_configs.at(widget_id));
        win->add_component(std::move(sli));
      }
    }

    std::cout << "Adding windows to app" << std::endl;
    add_window(*win);
  }

private:
  Config config;
};
