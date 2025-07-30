#include "Config/ConfigLoader.hpp"
#include <gtkmm/application.h>
#include <iostream>
#include <memory>

class ActionBar : public Gtk::Application {
public:
  static Glib::RefPtr<ActionBar> create(std::unique_ptr<Config> config) {
    return Glib::RefPtr<ActionBar>(new ActionBar(std::move(config)));
  }

  ActionBar(std::unique_ptr<Config> config)
      : Gtk::Application("org.mrunknown850.action-menu"),
        config(std::move(config)) {
    std::cout << "ActionBar constructed" << std::endl;
  }

protected:
  void on_activate() override {
    std::cout << "Generating windows..." << std::endl;
    auto xy_pair = config->get_margin();
    auto wh_pair = config->get_size();
    auto gap_pair = config->get_gap();

    std::cout << "Adding windows to app" << std::endl;
  }

private:
  std::unique_ptr<Config> config;
};
