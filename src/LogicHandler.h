#pragma once
#include <memory>
#include <QPoint>

namespace tictactoelr
{
    enum class cellStatus
    {
        NONE,
        EMPTY,
        X,
        O
    };

    enum class gameStatus
    {
        TIE,
        X_TURN,
        O_TURN,
        X_WON,
        O_WON
    };
}

class LogicHandler
{
public:
    LogicHandler();
    ~LogicHandler();
    void play(QPoint location, tictactoelr::cellStatus status);
    tictactoelr::cellStatus getStatus(QPoint location) const;
    static std::shared_ptr<LogicHandler> getInstance();
    tictactoelr::gameStatus getGameStatus();

    bool isXTurn() const { return m_isXTurn; }
    void setXTurn(bool mIsXTurn) { m_isXTurn = mIsXTurn; }

private:
    void initBoard();
    tictactoelr::gameStatus getTurn() const;
    static std::shared_ptr<LogicHandler> m_instance;

    tictactoelr::cellStatus m_board[3][3];
    tictactoelr::gameStatus m_gameStatus;
    bool m_gameOver;
    bool m_isXTurn;
    tictactoelr::gameStatus checkWinner();
    void printBoard();

};
