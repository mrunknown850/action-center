// #include "helloworld.hpp"
#include <iostream>
#include "Config/ConfigLoader.hpp"
#include <unistd.h> // For getcwd
#include <limits.h> // For PATH_MAX

int main(int argc, char *argv[]) {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    std::cout << cwd << std::endl;

    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config.json>\n";
        return 1;
    }

    try {
        Config config(argv[1]);

        auto [x, y] = config.get_position();
        auto [w, h] = config.get_size();
        auto [rows, cols] = config.get_layout();
        auto ids = config.get_components_id();

        std::cout << "Position: (" << x << ", " << y << ")\n";
        std::cout << "Size: (" << w << ", " << h << ")\n";
        std::cout << "Layout: " << rows << " rows, " << cols << " cols\n";
        std::cout << "Component IDs:\n";
        for (const auto& id : ids) {
            std::cout << "  - " << id << "\n";
        }

        const auto& comps = config.get_components_config();
        std::cout << "Component Configs:\n";
        for (const auto& [id, info] : comps) {
            std::cout << "  [" << id << "] format: " << info.format;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
