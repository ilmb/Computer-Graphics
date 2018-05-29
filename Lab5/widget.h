#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QString>

#include <QGLShaderProgram>
#include <QOpenGLShaderProgram>

#include <QMatrix4x4>
#include <QVector4D>
#include <QVector3D>
#include <qmath.h>

typedef std::pair<float, float> point;

class Widget: public QGLWidget {


    Q_OBJECT

public:

    static const int COLS = 50;
    const float GRID_SIZE = 0.05;
    static const int POINT_SIZE = 10;

    int dragNodeIndex;
    bool isDrag;
    float time;

    QList<point> nodes;
    QList <point> graphPoints;

    QGLShaderProgram* program;

    Widget(QWidget*);
    ~Widget();

    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    float getPolynomValue(float x);
    void recountGraphPoints();

    const QVector3D* torchPosition;
    const QVector4D* torchFirstColor;
    const QVector4D* torchSecondColor;
    const QVector4D* surfaceColor;

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent * e);

private slots:
    void refresh();
};

#endif // WIDGET_H
