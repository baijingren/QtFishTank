#include <iostream>
#include <QApplication>
#include "Log.cpp"
#include "renderer/QtRenderer.h"
#include "core/MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Logger::setLogFile("Log.txt");
	LOG_INFO << "Program started.";
	QtRenderer renderer;
//	renderer.initializeGL();
	LOG_INFO << "Renderer initialized.";
	MainWindow window;
	window.setCentralWidget(&renderer);
	window.resize(800, 600);
	window.setWindowTitle("Fluid Simulator");
	LOG_INFO << "Main window initialized.";
	window.show();
	LOG_INFO << "Main window shown.";
	return QApplication::exec();
}