#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radiusLineEdit->setText(QString::number(ui->fieldGLWidget->radius()));
    ui->countLineEdit->setText(QString::number(ui->fieldGLWidget->count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radiusLineEdit_returnPressed()
{
    ui->fieldGLWidget->setRadius(ui->radiusLineEdit->text().toInt());
}

void MainWindow::on_countLineEdit_returnPressed()
{
    ui->fieldGLWidget->setCount(ui->countLineEdit->text().toInt());
}
