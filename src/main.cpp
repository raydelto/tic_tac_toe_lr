#include <QApplication>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "glwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat openglFormat;
    openglFormat.setDepthBufferSize(24);
    openglFormat.setSamples(4);
    openglFormat.setVersion(3, 3);
    openglFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(openglFormat);

    MainWindow mainWindow;
    mainWindow.setWindowTitle(QApplication::translate("MainWindow", "Tic Tac Toe LR v0.1", nullptr));

    mainWindow.resize(mainWindow.sizeHint());
    mainWindow.show();
    return app.exec();
}
