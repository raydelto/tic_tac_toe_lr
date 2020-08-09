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
            m_board[i][j] = tictactoelr::status::EMPTY;
        }
    }
}

LogicHandler::LogicHandler()
{
    initBoard();
}

void LogicHandler::play(QPoint location,  tictactoelr::status status)
{
    const int row = location.x();
    const int column = location.y();
    assert(row >= 0 && row < 3 && column >= 0 && column < 3);
    m_board[row][column] = status;
}

tictactoelr::status LogicHandler::getStatus(QPoint location)
{
    const int row = location.x();
    const int column = location.y();
    assert(row >= 0 && row < 3 && column >= 0 && column < 3);
    return m_board[row][column];
}

LogicHandler::~LogicHandler() = default;
