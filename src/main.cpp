#include <QApplication>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QScreen>

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

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopArea = screenGeometry.width() * screenGeometry.height();
    int widgetArea = mainWindow.width() * mainWindow.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        mainWindow.show();
    else
        mainWindow.showMaximized();
    return app.exec();
}
