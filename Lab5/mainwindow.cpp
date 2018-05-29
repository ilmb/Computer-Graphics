#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat fmt;
    fmt.setSampleBuffers(true);
    fmt.setSamples(16);
    QGLFormat::setDefaultFormat(fmt);

    glwidget = new Widget(this);
    int width = size().width() - 220;
    int height = size().height() - 10;
    glwidget->resize(width, height);
    glwidget->setGeometry(210, 5, width, height);
    glwidget->resizeGL(width, height);

    QList<point> pts;
    pts.append(point(-0.8, 0.5));
    pts.append(point(-0.4, -0.2));
    pts.append(point(0.4, -0.7));
    pts.append(point(0.8, -0.3));
    pts.append(point(0.95, -0.8));
    glwidget->nodes = pts;
    glwidget->recountGraphPoints();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    int width = e->size().width() - 240;
    int height = e->size().height() - 10;
    glwidget->setGeometry(230, 5, width, height);
    glwidget->resizeGL(width, height);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    glwidget->torchPosition = new QVector3D((float)2 * value / 100 - 1,
                                            glwidget->torchPosition->y(), glwidget->torchPosition->z());
    glwidget->program->setUniformValue("torch_position", *(glwidget->torchPosition));
    glwidget->update();
    ui->lcdNumber->display(glwidget->torchPosition->x());
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    glwidget->torchPosition = new QVector3D(glwidget->torchPosition->x(),
                                            (float)3 * value / 100 - 1, glwidget->torchPosition->z());
    glwidget->program->setUniformValue("torch_position", *(glwidget->torchPosition));
    glwidget->update();
    ui->lcdNumber_2->display(glwidget->torchPosition->y());
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    glwidget->torchPosition = new QVector3D(glwidget->torchPosition->x(),
                                            glwidget->torchPosition->y(), (float) -2 * value / 100 - 0.5);
    glwidget->program->setUniformValue("torch_position", *(glwidget->torchPosition));
    glwidget->update();
    ui->lcdNumber_3->display(glwidget->torchPosition->z());
}
