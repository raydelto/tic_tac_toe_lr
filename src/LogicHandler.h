#pragma once
#include <memory>
#include <QPoint>

namespace tictactoelr
{
    enum class status
    {
        EMPTY,
        X,
        O
    };

}

class LogicHandler
{
public:
    LogicHandler();
    ~LogicHandler();
    void play(QPoint location, tictactoelr::status status);
    tictactoelr::status getStatus(QPoint location);
    static std::shared_ptr<LogicHandler> getInstance();

private:
    static std::shared_ptr<LogicHandler> m_instance;
    void initBoard();
    tictactoelr::status m_board[3][3];

};
