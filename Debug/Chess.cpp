#pragma once
#include "Snake.h"
#include "Food.h"
#include "Menu.h"
#include "Board.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Game");
sf::RectangleShape templateCell(Vector2f(100, 100));
Board board(templateCell, window);
Board* Cell::_board = &board;
Board* ChessPiece::_board = &board;

int main() {


    board.lauch();

    return 0;
}

// bug sinh fruit de len ran
