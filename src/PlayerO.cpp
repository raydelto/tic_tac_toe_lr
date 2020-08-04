#include "PlayerO.h"
#include <cmath>

PlayerO::PlayerO() = default;

void PlayerO::draw()
{
    assert(m_initialized);
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    for(auto const &move: m_moves)
    {
        m_model.setToIdentity();
        m_model.translate(move.row * ROW_PADDING, move.column * COL_PADDING);
        m_program->setUniformValue(m_modelMatrixLoc, m_model);
        f->glDrawArrays(GL_LINE_STRIP, 0, m_numVertices);
    }

    m_program->release();
}

void PlayerO::initBuffer()
{
    double radius = 40.0f;

    for(int i = 1 ; i <= 361; i++)
    {
        m_vertices << (float) (radius * ( cos(i * (M_PI /180) ))) << (float) ( radius * sin( i * (M_PI /180) )) + 42.0f;
        m_vertices <<  0.0f << 1.0f << 0.0f;
    }

    m_numVertices = m_vertices.count() / 5; //Each vertex has five fields (x,y ; r,g,b);
}
