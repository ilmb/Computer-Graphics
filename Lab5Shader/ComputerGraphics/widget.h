#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
private:
    QMatrix4x4 m_projectionMatrix; // матрица проекции
    QOpenGLShaderProgram m_program; // подключение шейдеров
};

#endif // WIDGET_H
