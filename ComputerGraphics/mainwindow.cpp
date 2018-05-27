#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(ui->fieldGLWidget->getCurvePointCount()));
    ui->checkBox->setChecked(ui->fieldGLWidget->getDebugMode());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked()
{
    ui->fieldGLWidget->setDebugMode(ui->checkBox->isChecked());
}

void MainWindow::on_pushButton_clicked()
{
    int currentPointCount = ui->fieldGLWidget->getCurvePointCount();

    QString pointsCount = ui->lineEdit->text();
    bool ok = true;
    double value = pointsCount.toUInt(&ok);

    if(ok)
    {
        if(value != currentPointCount)
        {
            ui->fieldGLWidget->setCurvePointCount(value);
        }
    }
    else
    {
        ui->lineEdit->setText(QString::number(currentPointCount));
    }
}
