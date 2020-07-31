#pragma once
#include <QWidget>

class QPushButton;
class GLWidget;
class MainWindow;

class Window : public QWidget
{
Q_OBJECT

public:
    Window(MainWindow *mw);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void dockUndock();

private:
    GLWidget *glWidget;
    QPushButton *dockBtn;
    MainWindow *mainWindow;
};