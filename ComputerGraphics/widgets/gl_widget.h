#ifndef GL_WINDGET_H
#define GL_WINDGET_H

#include <QGLWidget>
#include <QDebug>
#include <cmath>
#include <QMouseEvent>

struct Point2Df
{
    double m_x;
    double m_y;
    Point2Df(double x = 0.0, double y = 0.0) : m_x(x), m_y(y) {}

    const Point2Df & operator=(const Point2Df &rPoint)
    {
        m_x = rPoint.m_x;
        m_y = rPoint.m_y;
        return *this;
    }

    void setxy(float x, float y)
        {
            m_x = x; m_y = y;
        }
};

class GL_Widget: public QGLWidget
{
    Q_OBJECT
private:
    double m_scale = 1;
    int m_mousePositionX = 0;
    int m_mousePositionY = 0;
    double m_positionX = 0;
    double m_positionY = 0;

    bool m_debugMode = false;
    int m_debugPointIndex = -1;

    QList<Point2Df> m_points;

    int currentPointIndex = 0;
    int curvePointCount = 5;


public:
    explicit GL_Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();

    int getCurvePointCount() const;
    void setCurvePointCount(int value);

    bool getDebugMode() const;
    void setDebugMode(bool debugMode);

public slots:
    //void mouseMoveEvent(QMouseEvent *mouseEvent);

    void mousePressEvent(QMouseEvent *mouseEvent);

    void setPositionX(double value);

    void setPositionY(double value);

protected slots:
    void drawLine(Point2Df begin, Point2Df end);
    void drawPoint(double x, double y);
    void drawPoint(Point2Df point, int index);
    void drawCurve();

    Point2Df rotateMatrix(Point2Df point, double angle, Point2Df offset = Point2Df());

    Point2Df drawBezierGeneralized(QList<Point2Df> pointsList, double t) {
        Point2Df bezierPoint;
        bezierPoint.m_x = 0; bezierPoint.m_y = 0;
        for (int i = 0; i < curvePointCount; i++)
        {
            bezierPoint.m_x = bezierPoint.m_x + binomial_coff((float)(curvePointCount - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (curvePointCount - 1 - i)) * pointsList[i].m_x;
            bezierPoint.m_y = bezierPoint.m_y + binomial_coff((float)(curvePointCount - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (curvePointCount - 1 - i)) * pointsList[i].m_y;
        }
        return bezierPoint;
    }

    int factorial(int n)
    {
        if (n <= 1)
            return(1);
        else
            n = n * factorial(n - 1);
        return n;
    }

    float binomial_coff(float n, float k)
    {
        float ans;
        ans = factorial(n) / (factorial(k)*factorial(n - k));
        return ans;
    }

    //void scaling(int delta);
};

#endif // GL_WINDGET_H
