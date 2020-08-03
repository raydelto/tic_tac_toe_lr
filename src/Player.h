#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector>

//Stores which square in the board is occupied by the player
struct position
{
    int row;
    int column;
};

class Player
{
public:
    void initialize();
    Player();
    const QMatrix4x4 &getMProj() const;
    void setProjection(const QMatrix4x4 &projection);
    virtual void draw() = 0;
    const QVector<position> &getMoves() const { return m_moves; }
    void play(const position &move) { m_moves << move; }


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
    QVector<position> m_moves;
    // How far is one play from other
    const int ROW_PADDING = 100;
    const int COL_PADDING = 100;

};
