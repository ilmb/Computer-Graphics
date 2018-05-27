#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(20, 20, 550, 500);
}

void GL_Widget::initializeGL(){
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glViewport(0, 0, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0.0, 800.0, 0.0, 0.0, 700.0, 0.0);
    glScalef(m_scale, m_scale, m_scale);
}

void GL_Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    for(int i = 0; i < m_points.size(); i++)
    {
        drawPoint(m_points[i], i);
    }

    drawCurve();
}

/*void GL_Widget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    double dx = (double) (mouseEvent->x() - m_mousePositionX) / (10 * (this->width() / 2));
    double dy = (double) (mouseEvent->y() - m_mousePositionY) / (10 * (this->height() / 2));

    if(m_debugPointIndex > 0 && m_debugPointIndex < m_points.size())
    {
        m_points[m_debugPointIndex].m_x += dx;
        m_points[m_debugPointIndex].m_y -= dy;
    }
//    if(m_debugMode)
//    {
//        if(m_debugPointIndex > 0 && m_debugPointIndex < m_points.size())
//        {
//            m_points[m_debugPointIndex].m_x += dx;
//            m_points[m_debugPointIndex].m_y -= dy;
//        }
//    }

    updateGL();
}*/

void GL_Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_mousePositionX = mouseEvent->x();
    m_mousePositionY = mouseEvent->y();

    Point2Df center((double) this->width() / 2, (double) this->height() / 2);
    double x = (double) (m_mousePositionX - center.m_x) / (this->width() / 2);
    double y = (double) (center.m_y - m_mousePositionY) / (this->height() / 2);

    if(!m_debugMode)
    {
        if(m_points.size() >= curvePointCount)
        {
            m_points.clear();
            currentPointIndex = 0;
        }

        Point2Df point(x, y);
        m_points.push_back(point);

        m_points[currentPointIndex].m_x = x;
        m_points[currentPointIndex].m_y = y;

        currentPointIndex++;
    }
    else
    {
        double deltaX = INT_MAX;
        double deltaY = INT_MAX;

        for(int i = 0; i < m_points.size(); i++)
        {
            double currentDeltaX = abs(m_points[i].m_x - x);
            double currentDeltaY = abs(m_points[i].m_y - y);
            if(currentDeltaX < deltaX && currentDeltaY < deltaY)
            {
                deltaX = currentDeltaX;
                deltaY = currentDeltaY;
                m_debugPointIndex = i;
            }
        }
    }

    updateGL();
}

void GL_Widget::setPositionX(double value)
{
    m_positionX = value;
}

void GL_Widget::setPositionY(double value)
{
    m_positionY = value;
}

void GL_Widget::drawLine(Point2Df begin, Point2Df end)
{
    glBegin(GL_LINES);
    glVertex2f(begin.m_x, begin.m_y);
    glVertex2f(end.m_x, end.m_y);
    glEnd();
    glFlush();
}

void GL_Widget::drawPoint(double x, double y)
{
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void GL_Widget::drawPoint(Point2Df point, int index)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(point.m_x, point.m_y);
    glEnd();
    glFlush();

    renderText(point.m_x, point.m_y, 0, QString::number(index));
}

void GL_Widget::drawCurve()
{
    glViewport(0, 0, this->width(), this->height());
    if(currentPointIndex == curvePointCount)
    {
        // Drawing the control lines
        glColor3f(0.0, 0.0, 1.0);
        glLineWidth(1);
        for (int i = 0; i < curvePointCount - 1; i++)
        {
            drawLine(m_points[i], m_points[i+1]);
        }

        glColor3f(0.2, 1.0, 0.0);
        glLineWidth(5);

        Point2Df p1 = m_points[0];
        /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
        for (double t = 0.0; t <= 1.0; t += 0.02)
        {
            Point2Df p2 = drawBezierGeneralized(m_points, t);
            drawLine(p1, p2);
            p1 = p2;
        }
        glColor3f(0.0, 0.0, 0.0);
    }
}

Point2Df GL_Widget::rotateMatrix(Point2Df point, double angle, Point2Df offset)
{
    double radian = angle * (M_PI/180);

    Point2Df res;

    res.m_x = point.m_x * cos(radian) - point.m_y * sin(radian) + offset.m_x;
    res.m_y = point.m_x * sin(radian) + point.m_y * cos(radian) + offset.m_y;

    return res;
}

int GL_Widget::getCurvePointCount() const
{
    return curvePointCount;
}

void GL_Widget::setCurvePointCount(int value)
{
    curvePointCount = value;
    m_points.clear();
    currentPointIndex = 0;
    updateGL();
}

bool GL_Widget::getDebugMode() const
{
    return m_debugMode;
}

void GL_Widget::setDebugMode(bool debugMode)
{
    m_debugMode = debugMode;
}
