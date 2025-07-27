#include "Config/ConfigLoader.hpp"
#include "UI/Window.hpp"
#include <gtkmm/application.h>
#include <iostream>

class ActionBar : public Gtk::Application
{
public:
  static Glib::RefPtr<ActionBar> create(const Config &config)
  {
    return Glib::RefPtr<ActionBar>(new ActionBar(config));
  }

  ActionBar(const Config &config)
      : Gtk::Application("org.mrunknown850.action-menu"), config(config)
  {
    std::cout << "ActionBar constructed" << std::endl;
  }

protected:
  // void on_open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint) override
  // {
  //   std::cout << "on_open called, falling back to on_activate" << std::endl;
  //   activate(); // fallback to on_activate
  // }
  void on_activate() override
  {
    std::cout << "Generating windows..." << std::endl;
    auto xy_pair = config.get_margin();
    auto wh_pair = config.get_size();
    auto gap_pair = config.get_gap();
    auto win = new Window(config.get_anchor(), xy_pair.first, xy_pair.second,
                          wh_pair.first, wh_pair.second, gap_pair.first,
                          gap_pair.second);
    std::cout << "Adding windows to app" << std::endl;
    add_window(*win);
  }

private:
  Config config;
};

void print_config(Config cf)
{
  std::cout << "margin: " << cf.get_margin().first << " "
            << cf.get_margin().second << std::endl;
  std::cout << "size: " << cf.get_size().first << " " << cf.get_size().second
            << std::endl;
  std::cout << "gap: " << cf.get_gap().first << " " << cf.get_gap().second
            << std::endl;
}

int main(int argc, char *argv[])
{
  // if (argc < 2)
  // {
  //   std::cout << "Please parse config file" << std::endl;
  //   return 1;
  // }

  Config config_loader(argv[1]);
  // print_config(config_loader);

  auto app = ActionBar::create(config_loader);
  // auto app = Glib::RefPtr<ActionBar>(new ActionBar(Config("dummy.json")));
  return app->run(1, argv);
}
