#include "UI/Window.hpp"
#include <gtkmm/application.h>

class ActionBar : public Gtk::Application {
public:
  ActionBar() : Gtk::Application("org.example.ActionBar") {}

protected:
  void on_activate() override {
    auto win = new Window(static_cast<MenuPosition>(5), 10, 10, 300, 300, 5, 5);
    add_window(*win);
  }
};

int main(int argc, char *argv[]) {
  auto app = new ActionBar();
  return app->run(argc, argv);
}
