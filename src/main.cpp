#include <iostream>
#include <QApplication>
#include <QGridLayout>
#include "Log.cpp"
#include "renderer/QtRenderer.h"
#include "core/MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Logger::setLogFile("Log.txt");
	LOG_INFO << "Program started.";
	QWidget *renderer = new QtRenderer();
//	renderer.initializeGL();
	LOG_INFO << "Renderer initialized.";
	MainWindow window;
//	auto *layout = new QGridLayout();
//	window.setLayout(layout);
//	layout->addWidget(renderer, 1, 0, 1, 1);
	window.setCentralWidget(renderer);
	window.resize(800, 600);
	window.setWindowTitle("Fluid Simulator");
	LOG_INFO << "Main window initialized.";
	window.show();
	LOG_INFO << "Main window shown.";
	LOG_INFO << "Program ended.";
//	delete renderer;
//	delete layout;
	return QApplication::exec();
}