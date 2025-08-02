#include "Config/ConfigLoader.hpp"
#include "glibmm/refptr.h"
#include <gtkmm/application.h>
#include <iostream>
#include <memory>
#include <utility>

class ActionBar : public Gtk::Application {
public:
  static auto create(std::unique_ptr<Config> configuration)
      -> Glib::RefPtr<ActionBar> {
    return std::make_shared<ActionBar>(std::move(configuration));
  }

  ActionBar(std::unique_ptr<Config> config)
      : Gtk::Application("org.mrunknown850.action-menu"),
        current_config(std::move(config)) {
    std::cout << "ActionBar constructed" << '\n';
  }

protected:
  void on_activate() override {
    std::cout << "Generating windows..." << '\n';
    auto xy_pair = current_config->get_margin();
    auto wh_pair = current_config->get_size();
    auto gap_pair = current_config->get_gap();

    std::cout << "Margin: " << xy_pair.x << " " << xy_pair.y << '\n';
    std::cout << "Size: " << wh_pair.width << " " << wh_pair.height << '\n';
    std::cout << "Gap: " << gap_pair.row << " " << gap_pair.col << '\n';

    std::cout << "Adding windows to app" << '\n';
  }

private:
  std::unique_ptr<Config> current_config;
};
