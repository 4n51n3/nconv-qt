#include <QApplication>
#include <iostream>
#include "mainwindow.h"


int main(int argc, char *argv[]) {	

	std::cout << "Compiled with Qt Version " << QT_VERSION_STR << std::endl;
    QApplication app(argc, argv);
    MainWindow mf;
    mf.show();
    return app.exec();
}
