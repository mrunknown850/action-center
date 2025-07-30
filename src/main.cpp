#include "ActionBar.cpp"
#include <iostream>
#include <memory>

void print_config(Config cf) {
  std::cout << "margin: " << cf.get_margin().x << " " << cf.get_margin().y
            << std::endl;
  std::cout << "size: " << cf.get_size().width << " " << cf.get_size().height
            << std::endl;
  std::cout << "gap: " << cf.get_gap().row << " " << cf.get_gap().col
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Please parse config file" << std::endl;
    return 1;
  }

  auto config_loader = std::make_unique<Config>(argv[1]);
  // print_config(config_loader);

  auto app = ActionBar::create(std::move(config_loader));
  // auto app = Glib::RefPtr<ActionBar>(new ActionBar(Config("dummy.json")));
  return app->run(1, argv);
}
