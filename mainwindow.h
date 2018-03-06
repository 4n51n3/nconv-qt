#ifndef MAINFORM_H
#define MAINFORM_H

#include "ui_mainwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
	void on_convertButton_clicked();

private:
    Ui::MainWindow ui;
};

#endif
