#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->taskComboBox->addItem("GL_POINTS");
    ui->taskComboBox->addItem("GL_LINES");
    ui->taskComboBox->addItem("GL_LINE_STRIP");
    ui->taskComboBox->addItem("GL_LINE_LOOP");
    ui->taskComboBox->addItem("GL_TRIANGLES");
    ui->taskComboBox->addItem("GL_TRIANGLE_STRIP");
    ui->taskComboBox->addItem("GL_TRIANGLE_FAN");
    ui->taskComboBox->addItem("GL_QUADS");
    ui->taskComboBox->addItem("GL_QUAD_STRIP");
    ui->taskComboBox->addItem("GL_POLYGON");
    QObject::connect(ui->taskComboBox, SIGNAL(activated(int)), ui->glWidget, SLOT(setPrimitive(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
