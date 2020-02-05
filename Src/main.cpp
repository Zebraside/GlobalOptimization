#include <iostream>

#ifdef ENABLE_GUI
#include "Presenters/application.hpp"
#endif

int main(int argc, char **argv) {
#ifdef ENABLE_GUI
    Application a(argc, argv);
    a.run();
#else
    std::cout << "Nothing to show\n";
#endif

    return 0;
}