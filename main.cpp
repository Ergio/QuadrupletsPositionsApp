#include "mainwindow.h"
#include <QApplication>

// a little change here


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;
	w.show();



	return a.exec();
}
