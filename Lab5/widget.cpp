#include "widget.h"


Widget::Widget(QWidget *parent ) : QGLWidget(parent)
{
    isDrag = false;
    time = 0.0;
}

void Widget::initializeGL()
{

    qglClearColor(Qt::white);
    glPointSize(POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    //check extensions
    const GLubyte *extensions;
    extensions = glGetString(GL_EXTENSIONS);
    int i = 0;
    QString extensionsString;
    while (extensions[i] != 0) {
        extensionsString += extensions[i];
        i++;
    }
    if (!extensionsString.contains("GL_ARB_vertex_shader") ||
            !extensionsString.contains("GL_ARB_fragment_shader") ||
            !extensionsString.contains("GL_ARB_shader_objects") ||
            !extensionsString.contains("GL_ARB_shading_language_100"))
    {
        exit(0);
    }

    //compile shaders
    program = new QGLShaderProgram(this);
    QGLShader vShader( QGLShader::Vertex);
    vShader.compileSourceFile(":/torch_vertex_shader.glsl");
    QGLShader fShader( QGLShader::Fragment );
    fShader.compileSourceFile(":/torch_fragment_shader.glsl");

    program->addShader(&vShader);
    program->addShader(&fShader);
    program->link();
    program->bind();

    //set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 100);

    //set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -1);

    //get model-view-projection matrix for vertex shader
    glPushMatrix();
    float* mvp = new float[16];
    glGetFloatv(GL_PROJECTION_MATRIX, mvp);
    glMultMatrixf(mvp);
    glGetFloatv(GL_MODELVIEW_MATRIX, mvp);
    glPopMatrix();
    QMatrix4x4 mvpMatrix(mvp);
    program->setUniformValue("mvp", mvpMatrix);

    //set light parameters
    torchPosition = new QVector3D(1, 0.8, -1.2);
    torchFirstColor = new QVector4D(1, 1, 1, 1);        //white
    torchSecondColor = new QVector4D(0, 1, 1, 1);       //blue

    program->setUniformValue("torch_position", *torchPosition);
    program->setUniformValue("torch_first_color", *torchFirstColor);
    program->setUniformValue("torch_second_color", *torchSecondColor);
    surfaceColor = new QVector4D(0.85, 0.83, 0.87, 0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(100);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->setUniformValue("torch_first_color", *torchFirstColor);
    program->setUniformValue("torch_second_color", *torchSecondColor);

    //surface
    program->setUniformValue("lighting", true);
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < graphPoints.size()-1; i++) {

            float x1 = graphPoints.at(i).first;
            float y1 = graphPoints.at(i).second;
            float x2 = graphPoints.at(i+1).first;
            float y2 = graphPoints.at(i+1).second;

            program->setUniformValue("color", *surfaceColor);
            const QVector3D* normal = new QVector3D(-GRID_SIZE * (y2-y1) , GRID_SIZE * (x2-x1), 0);
            program->setUniformValue("normal", *normal);
            glBegin(GL_POLYGON);
            glVertex3f(x1, y1, -j * GRID_SIZE);
            glVertex3f(x1, y1, -j * GRID_SIZE - GRID_SIZE);
            glVertex3f(x2, y2, -j * GRID_SIZE - GRID_SIZE);
            glVertex3f(x2, y2, -j * GRID_SIZE);
            glEnd();
        }
    }

    program->setUniformValue("lighting", false);

    //nodes
    program->setUniformValue("color", QColor(0, 0, 200, 200));
    glBegin(GL_POINTS);
    for (int i = 0; i < nodes.size(); i++)
        glVertex3f(nodes.at(i).first, nodes.at(i).second, -0.4901);
    glEnd();

    //light position
    QVector4D* torchColor = new QVector4D(1, 0, 0, 1);
    program->setUniformValue("color", *torchColor);
    glBegin(GL_POINTS);
    glVertex3f(torchPosition->x(), torchPosition->y(), torchPosition->z());
    glEnd();

}

float Widget::getPolynomValue(float x) {
    float value = 0;
    for (int i = 0; i < nodes.size(); i++) {
        float nom = nodes[i].second;
        for (int j = 0; j < nodes.size(); j++) {
            if (j == i) continue;
            nom *= (float) (x - nodes[j].first) / (nodes[i].first - nodes[j].first);
        }
        value += nom;
    }
    return value;
}

void Widget::recountGraphPoints() {
    QList<point> newGraphPoints;
    for (int i = 0; i < COLS; i++) {
        float x = (float) i * 2 / COLS - 1;
        float y = getPolynomValue(x);
        newGraphPoints.append(point(x, y));
    }
    this->graphPoints = newGraphPoints;
}

void Widget::mousePressEvent(QMouseEvent *e) {

    float x = (float) e->x() / this->width() * 2 - 1;
    float y = - (float) e->y() / this->height() * 2 + 1;
    float pointSize = (float) 1 / this->width() * (POINT_SIZE + 10);
    for (int i = 0; i < nodes.size(); i++)
        if ((fabs(x - nodes.at(i).first) < pointSize) &&
                (fabs(y - nodes.at(i).second) < pointSize)) {
            isDrag = true;
            dragNodeIndex = i;
        }
}

void Widget::mouseReleaseEvent(QMouseEvent *e) {
    isDrag = false;
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    if (isDrag) {
        float x = (float) e->x() / this->width() * 2 - 1;
        float y = - (float) e->y() / this->height() * 2 + 1;
        nodes[dragNodeIndex].first = x;
        nodes[dragNodeIndex].second = y;
        recountGraphPoints();
        update();
    }
}

void Widget::refresh() {
    time += 0.1;
    if (time > 2 * M_PI) time = 0.0;
    program->setUniformValue("time", time);
    update();
}

Widget::~Widget() {

}
