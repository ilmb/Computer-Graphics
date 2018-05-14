#include "gl_widget.h"

GL_Widget::GL_Widget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(20, 20, 550, 500);
}

void GL_Widget::initializeGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GL_Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Задаем режим матрицы
    glMatrixMode(GL_PROJECTION);

    //Загружаем матрицу
    glLoadIdentity();

    move();
    glScalef(m_scale, m_scale, m_scale);

    drawFractal(m_count);
}

void GL_Widget::drawFractal(int count)
{
    glViewport(0, 0, this->width(), this->height());
    for(int i = 1; i <= count; i++)
    {
        drawCircle(m_startPoint.m_x, m_startPoint.m_y + i * m_radius / 2, i * m_radius / 2, 300);
        drawCircle(m_startPoint.m_x, m_startPoint.m_y - i * m_radius / 2, i * m_radius / 2, 300);
        drawCircle(m_startPoint.m_x + i * sqrt(3) * m_radius / 4, m_startPoint.m_y + i * m_radius / 4, i * m_radius / 2, 300);
        drawCircle(m_startPoint.m_x - i * sqrt(3) * m_radius / 4, m_startPoint.m_y + i * m_radius / 4, i * m_radius / 2, 300);
        drawCircle(m_startPoint.m_x + i * sqrt(3) * m_radius / 4, m_startPoint.m_y - i * m_radius / 4, i * m_radius / 2, 300);
        drawCircle(m_startPoint.m_x - i * sqrt(3) * m_radius / 4, m_startPoint.m_y - i * m_radius / 4, i * m_radius / 2, 300);

        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x, m_startPoint.m_y + i * m_radius);
        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x, m_startPoint.m_y - i * m_radius);

        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y, m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);

        drawLine(m_startPoint.m_x, m_startPoint.m_y + i * m_radius, m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y - i * m_radius, m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y + i * m_radius, m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2);
        drawLine(m_startPoint.m_x, m_startPoint.m_y - i * m_radius, m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);

        drawLine(m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2, m_startPoint.m_x + i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);
        drawLine(m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y + i * m_radius / 2, m_startPoint.m_x - i * sqrt(3) * m_radius / 2, m_startPoint.m_y - i * m_radius / 2);
    }
}

void GL_Widget::drawCircle(float x, float y, float r, int amountSegments)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < amountSegments; i++)
    {
    float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);
    float dx = r * cosf(angle);
    float dy = r * sinf(angle);
    glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void GL_Widget::drawLine(float x, float y, float a, float b)
{
    glBegin(GL_LINES);
        glVertex2d(x, y);
        glVertex2d(a, b);
    glEnd();
}

void GL_Widget::wheelEvent(QWheelEvent *wheelEvent)
{
    scaling(wheelEvent->delta());
}

void GL_Widget::scaling(int delta)
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе - делим на 1.1
    if (delta > 0)
    {
        m_scale *= 1.1;
    }
    else
    {
        if (delta < 0)
        {
            m_scale /= 1.1;
        }
    }
    updateGL();
}

void GL_Widget::move()
{
    glTranslatef(0.5f * m_positionX, -(0.5f * m_positionY), 0);
}

void GL_Widget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    double dx = (mouseEvent->x() - m_mousePositionX) / 10;
    double dy = (mouseEvent->y() - m_mousePositionY) / 10;

    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        setPositionX(m_positionX + dx/1000);
        setPositionY(m_positionY + dy/1000);
    }

    updateGL();
}

void GL_Widget::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_mousePositionX = mouseEvent->x();
    m_mousePositionY = mouseEvent->y();
}

void GL_Widget::setPositionX(double value)
{
    m_positionX = value;
}

void GL_Widget::setPositionY(double value)
{
    m_positionY = value;
}

void GL_Widget::setStartPoint(double x, double y)
{
    m_startPoint = Point2Df(x, y);
    updateGL();
}

void GL_Widget::setRadius(int value)
{
    m_radius = value;
    updateGL();
}

void GL_Widget::setCount(int value)
{
    m_count = value;
    updateGL();
}

size_t GL_Widget::radius() const
{
    return m_radius;
}

int GL_Widget::count() const
{
    return m_count;
}

std::pair<double, double> GL_Widget::startPoint() const
{
    return std::make_pair(m_startPoint.m_x, m_startPoint.m_y);
}
