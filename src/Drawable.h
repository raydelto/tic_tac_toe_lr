#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector>

class Drawable
{
public:
    void initialize();
    Drawable();
    ~Drawable();
    void setProjection(const QMatrix4x4 &projection);
    virtual void draw() = 0;
    void play(const QPoint &move) { m_moves << move; }

protected:
    void setupVertexAttribs();
    virtual void initBuffer() = 0;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *m_program;
    GLuint m_projMatrixLoc;
    QVector<GLfloat> m_vertices;
    GLuint m_modelMatrixLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;
    bool m_initialized;
    uint32_t m_numVertices;
    QVector<QPoint> m_moves;
};
