#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QApplication>

Window::Window(MainWindow *mw)
        : mainWindow(mw)
{
    glWidget = new GLWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    setLayout(mainLayout);
    setWindowTitle(tr("Tic Tac Toe LR"));
}
