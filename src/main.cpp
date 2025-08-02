#include "ActionBar.cpp"
#include <Config/ConfigLoader.hpp>
#include <iostream>
#include <memory>
#include <utility>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Please parse config file" << '\n';
    return 1;
  }

  auto config_loader = std::make_unique<Config>(argv[1]);

  auto app = ActionBar::create(std::move(config_loader));
  // auto app = Glib::RefPtr<ActionBar>(new ActionBar(Config("dummy.json")));
  return app->run(1, argv);
}
