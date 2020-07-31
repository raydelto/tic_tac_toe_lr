#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

GLWidget::GLWidget(QWidget *parent)
        : QOpenGLWidget(parent),
          m_program(0)
{
}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_vbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

static const char *vertexShaderSourceCore =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 vertexColor;\n"
        "uniform mat4 projMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "void main() {\n"
        "   vertexColor = aColor;\n"
        "   gl_Position = projMatrix * modelMatrix * vec4(aPos,1);\n"
        "}\n";

static const char *fragmentShaderSourceCore =
        "#version 330 core\n"
        "in vec3 vertexColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = vec4(vertexColor, 1.0);\n"
        "}\n";

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_modelMatrixLoc = m_program->uniformLocation("modelMatrix");

    // Create a vertex array object.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_vbo.create();
    m_vbo.bind();
    m_vertices <<  100.0f  << 100.0f << 0.0f << 1.0f << 0.0f << 0.0f;  //left
    m_vertices <<  300.0f  << 100.0f << 0.0f << 0.0f << 1.0f << 0.0f;  //right
    m_vertices <<  100.0f  <<  300.0f << 0.0f << 0.0f << 0.0f << 1.0f;  //top


    m_vbo.allocate(m_vertices.constData(), m_vertices.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();
    m_program->release();
}

void GLWidget::setupVertexAttribs()
{
    m_vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vbo.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_modelMatrixLoc, m_model);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.count());

    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
//  This commented ortho would maintain aspect ratio.  It's commented out since it has an unwanted behaviour when resizing the window.
//    m_proj.ortho(0.0f, GLfloat(w), 0.0f, h, 0.00f, 1.0f);
    m_proj.ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.00f, 1.0f);
    m_model.setToIdentity();
//    The model matrix is used for moving and rotating our models around the screen.  We're currently not using it, I just left it here in case we need this later.
//    m_model.translate(GLfloat(w) /2,h/2);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}
