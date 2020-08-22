#include "LogicHandler.h"

std::shared_ptr<LogicHandler> LogicHandler::m_instance;

std::shared_ptr<LogicHandler> LogicHandler::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = std::make_shared<LogicHandler>();
    }
    return m_instance;
}

void LogicHandler::initBoard()
{
    for(int i = 0 ; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m_board[i][j] = tictactoelr::cellStatus::EMPTY;
        }
    }
}

LogicHandler::LogicHandler(): m_gameOver(false)
{
    m_gameStatus = tictactoelr::gameStatus::X_TURN;
    initBoard();
}

void LogicHandler::play(QPoint location,  tictactoelr::cellStatus status)
{
    const int row = location.x();
    const int column = location.y();
    assert(row >= 0 && row < 3 && column >= 0 && column < 3);
    m_board[row][column] = status;
}

tictactoelr::gameStatus LogicHandler::getGameStatus()
{
    if(m_gameOver)
    {
        return m_gameStatus == tictactoelr::gameStatus::X_TURN ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
    }

    //vertical check
    for(int i = 0; i < 3; i++)
    {
        m_gameOver = true;
        tictactoelr::cellStatus cell = tictactoelr::cellStatus::EMPTY;
        for(int j = 0; j < 3; j++)
        {
            if(m_board[i][j] == tictactoelr::cellStatus::EMPTY || (j != 0 && m_board[i][j] != cell))
            {
                m_gameOver = false;
                continue;
            }
            cell = m_board[i][j];
        }
        if(m_gameOver)
        {
            return m_gameStatus == tictactoelr::gameStatus::X_TURN ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
        }
    }
    return m_gameStatus = getTurn();
}

tictactoelr::cellStatus LogicHandler::getStatus(QPoint location) const
{
    const int row = location.x();
    const int column = location.y();
    assert(row >= 0 && row < 3 && column >= 0 && column < 3);
    return m_board[row][column];
}

tictactoelr::gameStatus LogicHandler::getTurn() const
{
    return m_gameStatus == tictactoelr::gameStatus::X_TURN ? tictactoelr::gameStatus::O_TURN : tictactoelr::gameStatus::X_TURN;
}

LogicHandler::~LogicHandler() = default;
