#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>

GLWidget::GLWidget(QWidget *parent)
        : QOpenGLWidget(parent),
          m_program(nullptr)
{
    m_playerX = new PlayerX();
}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return {50, 50};
}

QSize GLWidget::sizeHint() const
{
    return {400, 400};
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_vbo.destroy();
    delete m_program;
    m_program = nullptr;
    delete m_playerX;
    m_playerX = nullptr;
    doneCurrent();
}


void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    m_playerX->initialize();
    m_playerX->play({0,0});
    m_playerX->play({0,1});
    m_playerX->play({0,2});

    m_playerX->play({1,0});
    m_playerX->play({1,1});
    m_playerX->play({1,2});

    m_playerX->play({2,0});
    m_playerX->play({2,1});
    m_playerX->play({2,2});
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_playerX->draw();
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
//  This commented ortho would maintain aspect ratio.  It's commented out since it has an unwanted behaviour when resizing the window.
//    m_proj.ortho(0.0f, GLfloat(w), 0.0f, h, 0.00f, 1.0f);
    m_proj.ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.00f, 1.0f);
    m_playerX->setProjection(m_proj);
//    The model matrix is used for moving and rotating our models around the screen.  We're currently not using it, I just left it here in case we need this later.
//    m_model.translate(GLfloat(w) /2,h/2);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}
