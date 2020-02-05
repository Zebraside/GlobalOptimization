#include <QtWidgets/QApplication>

#include "Presenters/main_window.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWinow window;
    return app.exec();
    return 0;
}