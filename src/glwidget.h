#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <memory>

class LogicHandler;
class PlayerX;
class PlayerO;

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void cleanup();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *m_program;
    QMatrix4x4 m_proj;
    PlayerX* m_playerX;
    PlayerO* m_playerO;
    QSize m_screenSize;
    bool m_isXTurn = true;
    QPoint translatePosition(QPoint original);
    std::shared_ptr<LogicHandler> m_logic;

};
