#pragma once

#include "Menu.h"
#include <memory.h>
#include "ChessPiece.h"


using namespace std;
using namespace sf;


class Cell {
public:
	Cell();
	Cell(sf::RectangleShape shape);
	Cell(int color, ChessPiece chess);
	~Cell();
	void draw(sf::RenderWindow& window) const;
	void target();
	void canMove();


	//private:
	Color _color;
	sf::RectangleShape _shape;
	sf::CircleShape _circle;
	shared_ptr<ChessPiece> _chess;
	int _x;
	int _y;
	bool _isTarget = false;
	bool _isCanMove = false;
	static Board* _board;
};


class Board
{
public:
	Board(Cell templateCell, sf::RenderWindow& window);
	void draw();
	shared_ptr<ChessPiece> createChessPiece(Color color, ChessPiece::typeChess tyChess, sf::RectangleShape shape);
	void inputHandle();
	void lauch();
	void clearCanMove();
	void clearTarget();
	void setTarget(Cell& target);
	void checkUpgradePawn();
	void switchTurn();
	bool checkEndGame();
	void castling();
//private:
	sf::RenderWindow& _window;
	Cell _cells[10][10];
	Cell _templateCell;
	Color _turn = Color::White;
	Cell* _target;
	weak_ptr<King> _wKing, _bKing;
};