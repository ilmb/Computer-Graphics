#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>
#include <QDebug>
#include <cmath>
#include <QMouseEvent>

struct Point3Df
{
    double x;
    double y;
    double z;
    double red;
    double green;
    double blue;
    double alpha;
};

struct Point2Df
{
    double m_x;
    double m_y;
    Point2Df(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}
};

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    Point2Df m_startPoint = Point2Df(0.0, 0.0);
    //double m_angle = -M_PI/2;
    size_t m_radius = 200;
    double m_scale = 0.0015;
    int m_mousePositionX = 0;
    int m_mousePositionY = 0;
    double m_positionX = 0;
    double m_positionY = 0;
    int m_count = 3;

public:
    explicit GL_Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();

public slots:
    void drawFractal(int count);

    void wheelEvent(QWheelEvent *wheelEvent);

    void mouseMoveEvent(QMouseEvent *mouseEvent);

    void mousePressEvent(QMouseEvent *mouseEvent);

    void setPositionX(double value);

    void setPositionY(double value);

    void setStartPoint(double x, double y);

    void setRadius(int value);

    void setCount(int value);

    size_t radius() const;

    int count() const;

    std::pair<double, double> startPoint() const;

protected slots:
    void drawCircle(float x, float y, float r, int amountSegments);
    void drawLine(float x, float y, float a, float b);

    void scaling(int delta);

    void move();
};

#endif // GL_WINDGET_H
