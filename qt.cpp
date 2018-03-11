#include <QApplication>
#include <QPalette>
#include <iostream>
#include "mainwindow.h"


int main(int argc, char *argv[]) {	

	std::cout << "Compiled with Qt Version " << QT_VERSION_STR << std::endl;
    std::cout << "DATE: " << __DATE__ << std::endl;
    std::cout << "TIME: " << __TIME__ << std::endl << std::endl;
    QApplication app(argc, argv);
    MainWindow mf;
    mf.show();
    return app.exec();
}
