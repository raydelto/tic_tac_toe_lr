#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>

GLWidget::GLWidget(QWidget *parent)
        : QOpenGLWidget(parent),
          m_program(nullptr)
{
    m_playerX = new PlayerX();
    m_playerO = new PlayerO();
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
    delete m_playerO;
    m_playerO = nullptr;
    doneCurrent();
}


void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    m_playerX->initialize();
    m_playerO->initialize();
    m_playerX->play({0,0});
    m_playerX->play({0,1});
    m_playerX->play({0,2});

    m_playerO->play({1,0});
    m_playerO->play({1,1});
    m_playerO->play({1,2});

    m_playerX->play({2,0});
    m_playerX->play({2,1});
    m_playerX->play({2,2});
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_playerX->draw();
    m_playerO->draw();
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.00f, 1.0f);
    m_playerX->setProjection(m_proj);
    m_playerO->setProjection(m_proj);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}
