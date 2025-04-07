#include <iostream>
#include <QApplication>
#include "Log.cpp"
#include "renderer/Renderer.h"
#include "core/MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Logger::setLogFile("Log.txt");

	Renderer renderer;
//	renderer.initializeGL();

	MainWindow window;
	window.setCentralWidget(&renderer);
	window.resize(800, 600);
	window.show();

	return QApplication::exec();
}