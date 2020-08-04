#include "PlayerX.h"

PlayerX::PlayerX()
{
    m_model.setToIdentity();
}

void PlayerX::draw()
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
        f->glDrawArrays(GL_LINES, 0, m_numVertices);
    }

    m_program->release();
}

void PlayerX::initBuffer()
{
    m_vertices <<  0.0f  << 0.0f << 1.0f << 0.0f << 0.0f;  //lower left
    m_vertices <<  100.0f  << 100.0f  << 1.0f << 0.0f << 0.0f;  //upper right
    m_vertices <<  0.0f  <<  100.0f << 1.0f << 0.0f << 0.0f;  //upper left
    m_vertices <<  100.0f  <<  0.0f << 1.0f << 0.0f << 0.0f;  //lower right
    m_numVertices = m_vertices.count() / 5; //Each vertex has five fields (x,y ; r,g,b);
}
