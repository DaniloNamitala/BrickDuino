#include "ShafraBlock.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QSize screenSize = app.screens().at(0)->size();

	ShafraBlock mainWindow;
	mainWindow.resize(screenSize.width() * 0.5, screenSize.height() * 0.8);
	mainWindow.show();

	return app.exec();
}