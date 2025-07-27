#include "UI/Window.hpp"
#include "glibmm/refptr.h"
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <gtkmm/application.h>
#include <iostream>

class App : public Gtk::Application {
public:
  App() : Gtk::Application("org.sample.org") {}

protected:
  void on_activate() override {
    auto app = Gtk::Application::create("org.sample.org");

    win = new Window(10, 10, 500, 500, 3, 3);

    gtk_layer_init_for_window(GTK_WINDOW(win->gobj()));
    gtk_layer_set_layer(GTK_WINDOW(win->gobj()), GTK_LAYER_SHELL_LAYER_TOP);
    gtk_layer_set_anchor(GTK_WINDOW(win->gobj()), GTK_LAYER_SHELL_EDGE_TOP,
                         true);
    gtk_layer_set_anchor(GTK_WINDOW(win->gobj()), GTK_LAYER_SHELL_EDGE_RIGHT,
                         true);
    gtk_layer_set_margin(GTK_WINDOW(win->gobj()), GTK_LAYER_SHELL_EDGE_RIGHT,
                         10);
    gtk_layer_set_margin(GTK_WINDOW(win->gobj()), GTK_LAYER_SHELL_EDGE_TOP, 10);
    add_window(*win);
  }

private:
  Window *win = nullptr;
};

int main(int argc, char *argv[]) {
  auto app = Glib::make_refptr_for_instance<App>(new App());
  std::cout << "Action Menu\n";
  return app->run(argc, argv);
}
