#include "ChessPiece.h"
#include "Board.h"

bool isWhite(Color color)
{
    return color == Color::White;
}

King::King(Color color) 
{
    _color = color;
    _typeChess = typeChess::King;
    if (isWhite(color))
    {

        if (!_texture.loadFromFile("wKing.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
    else
    {

        if (!_texture.loadFromFile("bKing.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void King::showMove(Board& board)
{
    board._cells[_x][_y].target();
    int moveX[8] = { -1,-1,-1,0,1,1,1,0 };
    int moveY[8] = { -1,0,1,1,1,0,-1,-1 };

    for (int i = 0; i < 8; i++)
    {
        if (board._cells[_x + moveX[i]][_y + moveY[i]]._chess && board._cells[_x + moveX[i]][_y + moveY[i]]._chess->_color == this->_color)
        {

        }
        else
        {
            board._cells[_x + moveX[i]][_y + moveY[i]].canMove();
        }
    }
}

void King::move(Board& board, int x, int y)
{
}

bool King::isChecked(Board& board)
{
    int moveX[8] = { -1,-1,-1,0,1,1,1,0 };
    int moveY[8] = { -1,0,1,1,1,0,-1,-1 };
    int moveX_knight[8] = { -2,-2,-1,1,2,2,1,-1 };
    int moveY_knight[8] = { -1,1,2,2,1,-1,-2,-2 };

    for (int i = 0; i < 8; i++)
    {
        int recentX = _x + moveX[i];
        int recentY = _y + moveY[i];
        if (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess
                && board._cells[recentX][recentY]._chess->_color != this->_color
                && board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::King)
            {
                return true;
            }
        }

        int knightCheckX = _x + moveX_knight[i];
        int knightCheckY = _y + moveY_knight[i];
        if (knightCheckX >= 1 && knightCheckX <= 8 && knightCheckY >= 1 && knightCheckY <= 8)
        {
            if (board._cells[knightCheckX][knightCheckY]._chess
                && board._cells[knightCheckX][knightCheckY]._chess->_color != this->_color
                && board._cells[knightCheckX][knightCheckY]._chess->_typeChess == ChessPiece::typeChess::Knight)
            {
                return true;
            }
        }

        while (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess == nullptr)
            {
                recentX += moveX[i];
                recentY += moveY[i];
            }
            else if (board._cells[recentX][recentY]._chess)
            {
                if (board._cells[recentX][recentY]._chess->_color != this->_color)
                {
                    if (i % 2 == 0 && board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::Bishop)
                    {
                        return true;
                    }
                    if (board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::Queen)
                    {
                        return true;
                    }
                    if (i % 2 != 0 && board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::Rook)
                    {
                        return true;
                    }
                }
                break;
            }
        }
    }
    
    if (_color == Color::Black)
    {
        int moveX[2] = { 1,1 };
        int moveY[2] = { -1,1 };
        for (int i = 0; i < 2; i++)
        {
            int recentX = _x + moveX[i];
            int recentY = _y + moveY[i];
            if (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
            {
                if (board._cells[recentX][recentY]._chess
                    && board._cells[recentX][recentY]._chess->_color != this->_color
                    && board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::Pawn)
                {
                    return true;
                }
            }
        }
    
    }
    else
    {
        int moveX[2] = { -1,-1 };
        int moveY[2] = { -1,1 };
        for (int i = 0; i < 2; i++)
        {
            int recentX = _x + moveX[i];
            int recentY = _y + moveY[i];
            if (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
            {
                if (board._cells[recentX][recentY]._chess
                    && board._cells[recentX][recentY]._chess->_color != this->_color
                    && board._cells[recentX][recentY]._chess->_typeChess == ChessPiece::typeChess::Pawn)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

Queen::Queen(Color color)
{
    _color = color;
    _typeChess = typeChess::Queen;
    if (isWhite(color))
    {

        if (!_texture.loadFromFile("wQueen.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
    else
    {

        if (!_texture.loadFromFile("bQueen.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void Queen::showMove(Board& board)
{
    board._cells[_x][_y].target();
    int moveX[8] = { -1,-1,-1,0,1,1,1,0 };
    int moveY[8] = { -1,0,1,1,1,0,-1,-1 };

    for (int i = 0; i < 8; i++)
    {
        int recentX = _x + moveX[i];
        int recentY = _y + moveY[i];
        while (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess == nullptr)
            {
                board._cells[recentX][recentY].canMove();
                recentX += moveX[i];
                recentY += moveY[i];
            }
            else if (board._cells[recentX][recentY]._chess)
            {
                if (board._cells[recentX][recentY]._chess->_color != this->_color)
                {
                    board._cells[recentX][recentY].canMove();
                }
                break;
            }
        }
    }
}

void Queen::move(Board& board, int x, int y)
{
}

Knight::Knight(Color color)
{
    _color = color;
    _typeChess = typeChess::Knight;
    if (isWhite(color))
    {
        if (!_texture.loadFromFile("wKnight.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
    else
    {
        if (!_texture.loadFromFile("bKnight.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void Knight::showMove(Board& board)
{
    board._cells[_x][_y].target();
    int moveX[8] = { -2,-2,-1,1,2,2,1,-1 };
    int moveY[8] = { -1,1,2,2,1,-1,-2,-2 };

    for (int i = 0; i < 8; i++)
    {
        int recentX = _x + moveX[i];
        int recentY = _y + moveY[i];
        if (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess == nullptr)
            {
                board._cells[recentX][recentY].canMove();
                recentX += moveX[i];
                recentY += moveY[i];
            }
            else if (board._cells[recentX][recentY]._chess)
            {
                if (board._cells[recentX][recentY]._chess->_color != this->_color)
                {
                    board._cells[recentX][recentY].canMove();
                }       
            }
        }
    }
}

void Knight::move(Board& board, int x, int y)
{
}

Pawn::Pawn(Color color)
{
    _typeChess = typeChess::Pawn;
    _color = color;
    if (isWhite(color))
    {
        if (!_texture.loadFromFile("wPawn.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }

    }
    else
    {
        if (!_texture.loadFromFile("bPawn.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void Pawn::showMove(Board& board)
{
    board._cells[_x][_y].target();
    if (isWhite(_color))
    {
        if (!board._cells[_x - 1][_y]._chess)
        {
            if (_isOnSpawn)
            {
                board._cells[_x - 1][_y].canMove();
                if (!board._cells[_x - 2][_y]._chess)
                    board._cells[_x - 2][_y].canMove();
            }
            else
            {
                board._cells[_x - 1][_y].canMove();
            }
        }

        if (board._cells[_x - 1][_y + 1]._chess && board._cells[_x - 1][_y + 1]._chess->_color != this->_color)
            board._cells[_x - 1][_y + 1].canMove();
        if (board._cells[_x - 1][_y - 1]._chess && board._cells[_x - 1][_y - 1]._chess->_color != this->_color)
            board._cells[_x - 1][_y - 1].canMove();
    }
    else
    {
        if (!board._cells[_x + 1][_y]._chess)
        {
            if (_isOnSpawn)
            {
                board._cells[_x + 1][_y].canMove();
                if (!board._cells[_x + 2][_y]._chess)
                    board._cells[_x + 2][_y].canMove();
            }
            else
            {
                board._cells[_x + 1][_y].canMove();
            }
        }

        if (board._cells[_x + 1][_y + 1]._chess && board._cells[_x + 1][_y + 1]._chess->_color != this->_color)
            board._cells[_x + 1][_y + 1].canMove();
        if (board._cells[_x + 1][_y - 1]._chess && board._cells[_x + 1][_y - 1]._chess->_color != this->_color)
            board._cells[_x + 1][_y - 1].canMove();
    }
}

void Pawn::move(Board& board, int x, int y)
{
    _isOnSpawn = false;
    board._target->_chess.swap(board._cells[x][y]._chess);
}

Rook::Rook(Color color)
{
    _color = color;
    _typeChess = typeChess::Rook;
    if (isWhite(color))
    {

        if (!_texture.loadFromFile("wRook.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
    else
    {
        if (!_texture.loadFromFile("bRook.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void Rook::showMove(Board& board)
{
    board._cells[_x][_y].target();
    int moveX[4] = { -1,0,1,0 };
    int moveY[4] = { 0,1,0,-1 };

    for (int i = 0; i < 4; i++)
    {
        int recentX = _x + moveX[i];
        int recentY = _y + moveY[i];
        while (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess == nullptr)
            {
                board._cells[recentX][recentY].canMove();
                recentX += moveX[i];
                recentY += moveY[i];
            }
            else if (board._cells[recentX][recentY]._chess)
            {
                if (board._cells[recentX][recentY]._chess->_color != this->_color)
                {
                    board._cells[recentX][recentY].canMove();
                }
                break;
            }
        }
    }
}

void Rook::move(Board& board, int x, int y)
{
}

Bishop::Bishop(Color color)
{
    _color = color;
    _typeChess = typeChess::Bishop;
    if (isWhite(color))
    {
        if (!_texture.loadFromFile("wBishop.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
    else
    {
        if (!_texture.loadFromFile("bBishop.png")) {
            // Handle an error.
            std::cout << "Can't load image";
        }
        else
        {
            _sprite.setTexture(_texture);
            _hasSprite = true;
        }
    }
}

void Bishop::showMove(Board& board)
{
    board._cells[_x][_y].target();
    int moveX[4] = { -1,-1,1,1 };
    int moveY[4] = { -1,1,-1,1 };

    for (int i = 0; i < 4; i++)
    {
        int recentX = _x + moveX[i];
        int recentY = _y + moveY[i];
        while (recentX >= 1 && recentX <= 8 && recentY >= 1 && recentY <= 8)
        {
            if (board._cells[recentX][recentY]._chess == nullptr)
            {
                board._cells[recentX][recentY].canMove();
                recentX += moveX[i];
                recentY += moveY[i];
            }
            else if (board._cells[recentX][recentY]._chess)
            {
                if (board._cells[recentX][recentY]._chess->_color != this->_color)
                {
                    board._cells[recentX][recentY].canMove();
                }
                break;
            }
        }
    }
}

void Bishop::move(Board& board, int x, int y)
{
}

void ChessPiece::draw(sf::RenderWindow& window)
{

    window.draw(_sprite);
}

void ChessPiece::showMove(Board& board)
{
}

bool ChessPiece::move(Cell& begin, Cell& end)
{

    begin._chess.swap(end._chess);
    end._chess->setPosition(end._x, end._y);

    if (_color == Color::White)
    {
        if (_board->_wKing.lock()->isChecked(*_board))
        {
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    if (_color == Color::Black)
    {
        if (_board->_bKing.lock()->isChecked(*_board))
        {
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    _isOnSpawn = false;
    return true;
}

void ChessPiece::move(Board& board, int x, int y)
{
    _isOnSpawn = false;
}

bool ChessPiece::eat(Cell& begin, Cell& end)
{
    begin._chess.swap(end._chess);
    end._chess->setPosition(end._x, end._y);
    auto temp = begin._chess;
    begin._chess.reset();
    if (_color == Color::White)
    {
        if (_board->_wKing.lock()->isChecked(*_board))
        {
            begin._chess = temp;
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    if (_color == Color::Black)
    {
        if (_board->_bKing.lock()->isChecked(*_board))
        {
            begin._chess = temp;
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    _isOnSpawn = false;
    return true;
}

void ChessPiece::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

bool ChessPiece::simuMove(Cell& begin, Cell& end)
{
    begin._chess.swap(end._chess);
    end._chess->setPosition(end._x, end._y);

    if (_color == Color::White)
    {
        if (_board->_wKing.lock()->isChecked(*_board))
        {
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    if (_color == Color::Black)
    {
        if (_board->_bKing.lock()->isChecked(*_board))
        {
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }

    begin._chess.swap(end._chess);
    begin._chess->setPosition(begin._x, begin._y);
    return true;
}

bool ChessPiece::simuEat(Cell& begin, Cell& end)
{
    begin._chess.swap(end._chess);
    end._chess->setPosition(end._x, end._y);
    auto temp = begin._chess;
    begin._chess.reset();
    if (_color == Color::White)
    {
        if (_board->_wKing.lock()->isChecked(*_board))
        {
            begin._chess = temp;
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }
    if (_color == Color::Black)
    {
        if (_board->_bKing.lock()->isChecked(*_board))
        {
            begin._chess = temp;
            begin._chess.swap(end._chess);
            begin._chess->setPosition(begin._x, begin._y);
            return false;
        }
    }

    begin._chess = temp;
    begin._chess.swap(end._chess);
    begin._chess->setPosition(begin._x, begin._y);
    return true;
}


