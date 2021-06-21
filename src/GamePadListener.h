#pragma once
#include <string>
#include <QObject>

class GamePadListener: public QObject
{
    Q_OBJECT
public:
    void up(bool pressed);
    void down(bool pressed);
    void left(bool pressed);
    void right(bool pressed);
private:
    void handleArrowPressed(bool pressed, std::string name);
};
