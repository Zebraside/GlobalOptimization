#pragma once

#include <QtWidgets/QApplication>
#include "main_window.hpp"

class Application {
public:
    Application(int argc, char** argv) : m_app(argc, argv) {
        m_main_window.reset(new MainWinow());
    }

    int run() {
        return m_app.exec();
    }

private:
    QApplication m_app;
    std::unique_ptr<MainWinow> m_main_window;
};
