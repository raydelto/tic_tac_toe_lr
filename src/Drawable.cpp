#include "Drawable.h"

static const char *vertexShaderSource =
        R"""(
    #version 330 core

    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec3 aColor;

    uniform mat4 model;
    uniform mat4 projection;

    out vec3 vertexColor;

    void main()
    {
        gl_Position = projection * model * vec4(aPos, 0.0 , 1.0);
        vertexColor = aColor;
    }
)""";

static const char *fragmentShaderSource =
        R"""(
    #version 330 core
    in vec3 vertexColor;
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(vertexColor,1.0);
    }
)""";

Drawable::Drawable(): m_initialized(false), m_numVertices(0)
{
}


void Drawable::initialize()
{
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projection");
    m_modelMatrixLoc = m_program->uniformLocation("model");

    // Create a vertex array object.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_vbo.create();
    m_vbo.bind();
    initBuffer();
    m_vbo.allocate(m_vertices.constData(), m_vertices.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();
    m_program->release();
    m_initialized = true;

}

void Drawable::setupVertexAttribs()
{
    m_vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void *>(2 * sizeof(GLfloat)));
    m_vbo.release();
}

const QMatrix4x4 &Drawable::getMProj() const
{
    return m_proj;
}

void Drawable::setProjection(const QMatrix4x4 &projection)
{
    m_proj = projection;
}

