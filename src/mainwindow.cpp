#include "mainwindow.h"
#include "window.h"
#include <QMenuBar>
#include <QMenu>
#include <iostream>
#include <QGamepadManager>


MainWindow::MainWindow()
{
    setCentralWidget(new Window(this));
    setFixedSize(400,400);
    std::cout << "Initializing Gamepads" << std::endl;
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    std::cout << "There are " << gamepads.count() << " gamepads connected" << std::endl;
    if(!gamepads.isEmpty())
    {
        std::cout << "The id of the last gamepad found is " << gamepads.last() << std::endl;
        QGamepad* gamepad = new QGamepad(gamepads.last());
        GamePadListener* listener = new GamePadListener();
        connect(gamepad,&QGamepad::buttonUpChanged, listener, &GamePadListener::up);
        connect(gamepad,&QGamepad::buttonDownChanged, listener, &GamePadListener::down);
        connect(gamepad,&QGamepad::buttonLeftChanged, listener, &GamePadListener::left);
        connect(gamepad,&QGamepad::buttonRightChanged, listener, &GamePadListener::right);

    }
    std::cout << "Initializing Gamepads end" << std::endl;

}
