#pragma once

#include <QtWidgets/QApplication>
#include "main_window.hpp"

class Application {
public:
    Application(int argc, char** argv) : m_app(argc, argv) {
        MainWinow window;
    }

    int run() {
        return m_app.exec();
    }

private:
    QApplication m_app;
};
