#pragma once
#include <QWidget>

class GLWidget;
class MainWindow;

class Window : public QWidget
{
Q_OBJECT

public:
    Window(MainWindow *mw);

private:
    GLWidget *glWidget;
    MainWindow *mainWindow;
};