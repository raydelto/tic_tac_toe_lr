#include "glwidget.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include "PlayerX.h"
#include "PlayerO.h"
#include "LogicHandler.h"

GLWidget::GLWidget(QWidget *parent)
        : QOpenGLWidget(parent),
          m_program(nullptr)
{
    m_playerX = new PlayerX();
    m_playerO = new PlayerO();
    m_logic = LogicHandler::getInstance();
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
    m_screenSize.setWidth(w);
    m_screenSize.setHeight(h);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    tictactoelr::gameStatus gameStatus = m_logic->getGameStatus();
    if(gameStatus == tictactoelr::gameStatus::X_WON || gameStatus == tictactoelr::gameStatus::O_WON)
    {
        QMessageBox::information(this,"Game over",(gameStatus == tictactoelr::gameStatus::X_WON ? "X" :"O") + QString(" has won the match"));
        return;
    }
    static const int SPACING = 400 / 3;
    QPoint point = translatePosition({event->pos().x() / SPACING, event->pos().y() / SPACING });
    if(m_logic->getStatus(point) == tictactoelr::cellStatus::EMPTY)
    {
        Drawable* player = m_isXTurn ? static_cast<Drawable*>(m_playerX) : static_cast<Drawable*>(m_playerO);
        player->play(point);
        m_logic->play(point, m_isXTurn ? tictactoelr::cellStatus::X : tictactoelr::cellStatus::O);
        gameStatus = m_logic->getGameStatus();
        if(gameStatus == tictactoelr::gameStatus::X_WON || gameStatus == tictactoelr::gameStatus::O_WON)
        {
            QMessageBox::information(this,"Game over",(gameStatus == tictactoelr::gameStatus::X_WON ? "X" :"O") + QString(" has won the match"));
            return;
        }

        m_isXTurn = !m_isXTurn;
        repaint();
    }
}

QPoint GLWidget::translatePosition(QPoint original)
{
    QPoint result = original;

    switch(original.y())
    {
        case 0:
            result.setY(2);
        break;
        case 1:
            result.setY(1);
        break;
        case 2:
            result.setY(0);
        break;
    }
    return result;
}
