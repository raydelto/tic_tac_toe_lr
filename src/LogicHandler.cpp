#include "LogicHandler.h"
#include <iostream>

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

LogicHandler::LogicHandler(): m_isXTurn(true)
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
    tictactoelr::gameStatus status = checkWinner();
    switch(status)
    {
        case tictactoelr::gameStatus::TIE:
        case tictactoelr::gameStatus::O_WON:
        case tictactoelr::gameStatus::X_WON:
            return status;
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

tictactoelr::gameStatus LogicHandler::checkWinner()
{
    /*Please note that the board matrix is rotated in 90 degrees.
     * Therefore Horizontal matrix validation checks if a player has won vertically and so on.
    */
    tictactoelr::cellStatus status = tictactoelr::cellStatus::NONE;
    bool winner = true;

    //Horizontal
    for(size_t i = 0 ; i < 3; i++)
    {
        if(i == 0)
        {
            status = m_board[i][0];
        }
        for(size_t j = 0 ; j < 3; j++)
        {
            if(m_board[i][j] != status || m_board[i][j] == tictactoelr::cellStatus::EMPTY)
            {
                winner = false;
                break;
            }
        }
        if(winner)
        {
            return m_isXTurn ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
        }
    }

    //Vertical
    for(size_t j = 0 ; j < 3; j++)
    {
        winner = true;
        for(size_t i = 0 ; i < 3; i++)
        {
            if(i == 0)
            {
                status = m_board[i][j];
            }

            if(m_board[i][j] != status || m_board[i][j] == tictactoelr::cellStatus::EMPTY)
            {
                winner = false;
                continue;
            }
        }
        if(winner)
        {
            break;
        }
    }
    if(winner)
    {
        return m_isXTurn ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
    }

    //Diagonal (upper left to bottom right)
    if(m_board[0][0] != tictactoelr::cellStatus::EMPTY && m_board[0][0] == m_board[1][1]  &&  m_board[1][1] == m_board[2][2]  )
    {
        return m_isXTurn ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
    }

    //Diagonal (upper right to bottom left)

    if(m_board[0][2] != tictactoelr::cellStatus::EMPTY &&  m_board[0][2] == m_board[1][1]  &&  m_board[1][1] == m_board[2][0]  )
    {
        return m_isXTurn ? tictactoelr::gameStatus::X_WON : tictactoelr::gameStatus::O_WON;
    }

    if(!winner)
    {
        return m_isXTurn ? tictactoelr::gameStatus::X_TURN :tictactoelr::gameStatus::O_TURN;
    }

    return tictactoelr::gameStatus::TIE;
}

LogicHandler::~LogicHandler() = default;
