#include "ActionBar.cpp"
#include <iostream>

void print_config(Config cf) {
  std::cout << "margin: " << cf.get_margin().first << " "
            << cf.get_margin().second << std::endl;
  std::cout << "size: " << cf.get_size().first << " " << cf.get_size().second
            << std::endl;
  std::cout << "gap: " << cf.get_gap().first << " " << cf.get_gap().second
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Please parse config file" << std::endl;
    return 1;
  }

  Config config_loader(argv[1]);
  // print_config(config_loader);

  auto app = ActionBar::create(config_loader);
  // auto app = Glib::RefPtr<ActionBar>(new ActionBar(Config("dummy.json")));
  return app->run(1, argv);
}
