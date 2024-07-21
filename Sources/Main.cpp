#include <iostream>

#include "BrickDuino.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QSize screenSize = app.screens().at(0)->size();
    try {
        BrickDuino mainWindow;
        mainWindow.resize(screenSize.width() * 0.5, screenSize.height() * 0.8);
        mainWindow.show();

        return app.exec();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}