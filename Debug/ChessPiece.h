#pragma once
#include "Menu.h"

class Cell;
class Board;

class ChessPiece {
public:
	enum typeChess
	{
		None,
		King,
		Queen,
		Knight,
		Pawn,
		Rook,
		Bishop
	};

	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _hasSprite = false;
	sf::Color _color;
	typeChess _typeChess = typeChess::None;
	Vector2f _position;
	sf::RectangleShape _rect;
	int _x;
	int _y;
	bool _isOnSpawn = true;
	static Board* _board;

	void draw(sf::RenderWindow& window);
	virtual void showMove(Board& board);
	virtual bool move(Cell& begin, Cell& end);
	virtual void move(Board& board, int x, int y);
	virtual bool eat(Cell& begin, Cell& end);
	void setPosition(int x, int y);
	bool simuMove(Cell& begin, Cell& end);
	bool simuEat(Cell& begin, Cell& end);
};

class King : public ChessPiece
{
public:
	King(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
	bool isChecked(Board& board);

	bool _isChecked = false;

};

class Queen : public ChessPiece
{
public:
	Queen(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
};

class Knight : public ChessPiece
{
public:
	Knight(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
};

class Pawn : public ChessPiece
{
public:
	Pawn(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
	//void move(Cell& begin, Cell& end) override;
	//void eat(Cell& begin, Cell& end) override;
};

class Rook : public ChessPiece
{
public:
	Rook(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
	bool _isCanCastle = false;
};

class Bishop : public ChessPiece
{
public:
	Bishop(Color color);
	void showMove(Board& board) override;
	void move(Board& board, int x, int y) override;
};



