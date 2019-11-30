#include "SequentWorker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SequentWorker w;
	w.show();
	return a.exec();
}
