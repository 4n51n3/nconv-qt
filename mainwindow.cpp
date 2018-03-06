#include "mainwindow.h"
#include <iostream>
#include <Converter.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect( ui.convertButton, SIGNAL(released()),this, SLOT(on_convertButton_clicked()));
}

void MainWindow::on_convertButton_clicked(){
	Converter conv;
	uint base = stoi(ui.spinBox->text().toStdString());
	uint toBase = stoi(ui.spinBox_2->text().toStdString());
	string rez;
	try{
		rez = conv.Convert(conv.GetDecNumber(ui.lineEdit->text().toStdString(), base), toBase);
	}catch(ConvertException &ex){
		cout << ex.what() << endl;
	}
	
//	cout << "Base: " << base << "\ntoBase: " << toBase << "\nrez: "<< conv.GetDecNumber(string("523"), base) <<endl;
	ui.lineEdit_3->setText(QString(rez.c_str()));
}
