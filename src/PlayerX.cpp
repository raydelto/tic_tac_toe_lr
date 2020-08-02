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
    m_program->setUniformValue(m_modelMatrixLoc, m_model);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
    m_program->release();
}

void PlayerX::initBuffer()
{
    m_vertices <<  100.0f  << 100.0f << 0.0f << 1.0f << 0.0f << 0.0f;  //left
    m_vertices <<  300.0f  << 100.0f << 0.0f << 0.0f << 1.0f << 0.0f;  //right
    m_vertices <<  100.0f  <<  300.0f << 0.0f << 0.0f << 0.0f << 1.0f;  //top
    m_numVertices = m_vertices.count() / 6; //Each vertex has six fields (x,y,z ; r,g,b);
}
