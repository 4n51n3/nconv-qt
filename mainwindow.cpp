#include "mainwindow.h"
#include <iostream>
#include <Converter.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    //  connect(ui.convertButton, SIGNAL(released()), this, SLOT(on_convertButton_clicked()));
}

void MainWindow::on_convertButton_clicked() {

    uint base = stoi(ui.spinBox->text().toStdString());
    uint toBase = stoi(ui.spinBox_2->text().toStdString());
    string rez("ERROR");
    try {
        rez = Number(ui.lineEdit->text().toStdString(), base).toBase(toBase);
    } catch (exc::ConvertException &ex) {
        cout << ex.what() << endl;
    }

    ui.lineEdit_3->setText(QString(rez.c_str()));

	//cout << "Base: " << base << "\ntoBase: " << toBase << "\nNumber: " << ui.lineEdit->text().toStdString() << endl;

}