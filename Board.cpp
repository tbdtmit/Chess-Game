
#include "Board.h"
#include "ChessPiece.h"


void Cell::draw(sf::RenderWindow& window) const
{
	window.draw(_shape);
	if(_isTarget || _isCanMove)
		window.draw(_circle);
	if (_chess != nullptr && _chess->_hasSprite)
	{
		//_chess->_x = this->_x;
		//_chess->_y = this->_y;
		_chess->_texture.setSmooth(true);
		_chess->_sprite.setTexture(_chess->_texture);
		_chess->_sprite.setPosition(this->_shape.getPosition());
		_chess->_sprite.setScale(1.6, 1.6);

		window.draw(_chess->_sprite);
	}

}

void Cell::target()
{
	_isTarget = !_isTarget;
	if (_isTarget)
	{
		_circle.setOutlineThickness(10);
		_circle.setOutlineColor(Color::Red);
	}
	else
	{
		_circle.setOutlineThickness(0);
		_circle.setOutlineColor(_color);
	}
}

void Cell::canMove()
{
	if (_board->_target)
	{
		if (this->_chess == nullptr)
		{
			if (_board->_target->_chess->simuMove(*_board->_target, *this))
			{
				_isCanMove = !_isCanMove;
			}
		}
		else if (this->_chess)
		{
			if (_board->_target->_chess->simuEat(*_board->_target, *this))
			{
				_isCanMove = !_isCanMove;
			}
		}
	}
	if (_isCanMove)
	{
		_circle.setOutlineThickness(10);
		_circle.setOutlineColor(Color::Cyan);
	}
	else
	{
		_circle.setOutlineThickness(0);
		_circle.setOutlineColor(_color);
	}


}

Cell::Cell()
{
}

Cell::Cell(sf::RectangleShape shape) : _shape(shape)
{

}



Cell::~Cell()
{
}

Board::Board(Cell templateCell, sf::RenderWindow& window) :
_templateCell(templateCell),
_window(window)

{

	auto heightCell = _templateCell._shape.getSize().y;
	auto widthCell = _templateCell._shape.getSize().x;
	_window.setSize(sf::Vector2u(widthCell * 8, heightCell * 8));
	auto heightBoard = _window.getSize().y;
	auto widthBoard = _window.getSize().x;
	int cellIndex = 0;
	int indexRow = 0;
	int indexColumn = 0;

	ChessPiece::typeChess spawnChessPiece[8] = { ChessPiece::typeChess::Rook, ChessPiece::typeChess::Knight,
		ChessPiece::typeChess::Bishop, ChessPiece::typeChess::Queen, ChessPiece::typeChess::King,
		ChessPiece::typeChess::Bishop, ChessPiece::typeChess::Knight, ChessPiece::typeChess::Rook };


	for (auto y = 0; y <= widthBoard; y += widthCell)
	{
		indexRow++;
		indexColumn = 0;
		for (auto x = 0; x <= heightBoard; x += heightCell)
		{
			indexColumn++;
			cellIndex++;
			Cell cell;
			cell._shape.setSize(_templateCell._shape.getSize());
			cell._shape.setPosition(x, y);
			cell._circle.setRadius(_templateCell._shape.getSize().x / 2 - 10);
			cell._circle.setPosition(x + 10, y + 10);
			cell._circle.setFillColor(Color::Transparent);
			if (cellIndex % 2 == 0)
			{
				cell._color = Color(8,168,10);
			}
			else
			{
				cell._color = Color::White;
			}
			cell._shape.setFillColor(cell._color);
			cell._x = indexRow;
			cell._y = indexColumn;


			
			_cells[indexRow][indexColumn] = cell;
		}
	}

	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			if (x == 2 || x == 7)
			{
				if (x == 2)
				{

					_cells[x][y]._chess = createChessPiece(sf::Color::Black, ChessPiece::typeChess::Pawn, _cells[x][y]._shape);
					_cells[x][y]._chess->setPosition(x, y);
				}
				else
				{
					_cells[x][y]._chess = createChessPiece(sf::Color::White, ChessPiece::typeChess::Pawn, _cells[x][y]._shape);
					_cells[x][y]._chess->setPosition(x, y);
				}
			}

			else if (x == 1 || x == 8)
			{
				for (int i = 0; i <= 7; i++)
				{
					if (x == 1)
					{
						_cells[x][y]._chess = createChessPiece(sf::Color::Black, spawnChessPiece[i], _cells[x][y]._shape);
						_cells[x][y]._chess->setPosition(x, y);
						y++;
					}
					else
					{
						_cells[x][y]._chess = createChessPiece(sf::Color::White, spawnChessPiece[i], _cells[x][y]._shape);
						_cells[x][y]._chess->setPosition(x, y);
						y++;
					}
				}
				break;
			}
		}
	}

}

void Board::draw()
{
	Clock tim;
	int id = 0;
	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			id++;
			_cells[x][y].draw(_window);
		}
	}
	_window.display();
	tim.restart();
	while (tim.getElapsedTime().asMilliseconds() <= 100);

}

shared_ptr<ChessPiece> Board::createChessPiece(Color color, ChessPiece::typeChess tyChess, sf::RectangleShape shape)
{
	shared_ptr<ChessPiece> newChess;
	if (tyChess == ChessPiece::typeChess::Rook)
	{
		newChess = make_shared<Rook>(Rook(color));
	}
	else if (tyChess == ChessPiece::typeChess::King)
	{
		newChess = make_shared<King>(King(color));
		if (color == Color::White) {
			_wKing = static_pointer_cast<King>(newChess);
		}
		else
		{
			_bKing = static_pointer_cast<King>(newChess);
		}
	}
	else if (tyChess == ChessPiece::typeChess::Queen)
	{
		newChess = make_shared<Queen>(Queen(color));
	}
	else if (tyChess == ChessPiece::typeChess::Knight)
	{
		newChess = make_shared<Knight>(Knight(color));
	}
	else if (tyChess == ChessPiece::typeChess::Pawn)
	{
		newChess = make_shared<Pawn>(Pawn(color));
	}
	else if (tyChess == ChessPiece::typeChess::Bishop)
	{
		newChess = make_shared<Bishop>(Bishop(color));

	}

	newChess->_rect = shape;
	newChess->_position = shape.getPosition();

	return newChess;
}

void Board::inputHandle()
{
	checkUpgradePawn();
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			auto pos = Vector2f(event.mouseButton.x, event.mouseButton.y);
			for (int x = 1; x <= 8; x++)
			{
				for (int y = 1; y <= 8; y++)
				{
					if (_cells[x][y]._shape.getGlobalBounds().contains(pos))
					{
						if (_cells[x][y]._chess)
						{
							if (!_cells[x][y]._isCanMove && !_cells[x][y]._isTarget)
							{
								clearCanMove();
								clearTarget();
								setTarget(_cells[x][y]);
								if(_target->_chess->_color == _turn)
									_cells[x][y]._chess->showMove(*this);
							}
							else if (_cells[x][y]._isCanMove && _cells[x][y]._chess->_color != _target->_chess->_color)
							{
								if (_target->_chess->eat(*_target, _cells[x][y]))
								{
									clearCanMove();
									clearTarget();
									switchTurn();
									if (checkEndGame())
										exit(1);
								}
							}
							else if (_cells[x][y]._isTarget)
							{
								_cells[x][y]._chess->showMove(*this);
							}						
						}
						else
						{
							if (_cells[x][y]._isCanMove)
							{
								if (_target->_chess->move(*_target, _cells[x][y]))
								{
									clearCanMove();
									clearTarget();
									switchTurn();
									if (checkEndGame())
										exit(1);
								}
							}
						}

					}
				}
			}
		}
	
	}
}

void Board::lauch()
{
	while (_window.isOpen())
	{

		draw();
		inputHandle();


	}

}

void Board::clearCanMove()
{
	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			if (_cells[x][y]._isCanMove == true)
			{
				_cells[x][y]._isCanMove = false;
			}
		}
	}
}

void Board::clearTarget()
{
	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			if (_cells[x][y]._isTarget == true)
			{
				_cells[x][y].target();
			}
		}
	}
}

void Board::setTarget(Cell& target)
{
	_target = &target;
}

void Board::checkUpgradePawn()
{
	sf::RenderWindow _windowUpgrade;

	ChessPiece::typeChess spawnChessPiece[4] = { 
		ChessPiece::typeChess::Rook, 
		ChessPiece::typeChess::Knight,
		ChessPiece::typeChess::Bishop, 
		ChessPiece::typeChess::Queen};

	vector<shared_ptr<ChessPiece>> temp;
	RectangleShape rect;
	rect.setSize(Vector2f( 60, 60));
	for (int i = 0; i < 4; i++)
	{
		rect.setPosition(Vector2f(rect.getSize().x * i, 0));
		auto newChess = createChessPiece(Color::White, spawnChessPiece[i], rect);
		newChess->_sprite.setPosition(rect.getPosition());
		temp.push_back(newChess);
	}

	for (int i = 1; i <= 8; i += 7)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (_cells[i][j]._chess)
			{
				if (_cells[i][j]._chess->_typeChess == ChessPiece::typeChess::Pawn)
				{
					_windowUpgrade.create(sf::VideoMode(240, 60), "Upgrade Pawn");
					if (i == 1)
					{
						_windowUpgrade.setPosition(Vector2i(_window.getPosition().x, _window.getPosition().y - 100));
					}
					else
					{
						_windowUpgrade.setPosition(Vector2i(_window.getPosition().x - _windowUpgrade.getSize().x, _window.getPosition().y + _window.getSize().y - _windowUpgrade.getSize().y));
					}

					while (_windowUpgrade.isOpen())
					{
						_window.setActive(false);

						for (auto chess : temp)
						{
							chess->_texture.setSmooth(true);
							chess->_sprite.setTexture(chess->_texture);
							_windowUpgrade.draw(chess->_sprite);
						}
						_windowUpgrade.display();

						sf::Event event;
						while (_windowUpgrade.pollEvent(event)) {
							if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
							{
								auto pos = Vector2f(event.mouseButton.x, event.mouseButton.y);

								for (auto chess : temp)
								{
									if (chess->_sprite.getGlobalBounds().contains(pos))
									{
										_window.setActive(true);
										_cells[i][j]._chess = createChessPiece(_cells[i][j]._chess->_color, chess->_typeChess, _cells[i][j]._shape);
										_cells[i][j]._chess->setPosition(i, j);
										_cells[i][j]._chess->_isOnSpawn = false;
										_windowUpgrade.close();
									}
								}

							}
						}
					}
				}
			}
		}
	}
}

void Board::switchTurn()
{
	if (_turn == Color::White)
	{
		_turn = Color::Black;
	}
	else
	{
		_turn = Color::White;
	}
}

bool Board::checkEndGame()
{
	if (_bKing.expired() || _wKing.expired())
		return true;
	else
	{
		if (_wKing.lock()->isChecked(*this))
		{
			cout << "White King got a check" << endl;
		}
		if (_bKing.lock()->isChecked(*this))
		{
			cout << "Black King got a check" << endl;
		}
	}

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (_cells[i][j]._chess && _cells[i][j]._chess->_color ==_turn)
			{
				//check king be checked all ???
				setTarget(_cells[i][j]);
				_cells[i][j]._chess->showMove(*this);
				for (int x = 1; x <= 8; x++)
				{
					for (int y = 1; y <= 8; y++)
					{
						if (_cells[x][y]._isCanMove)
						{
							clearCanMove();
							clearTarget();
							return false;
						}
					}
				}
				clearCanMove();
				clearTarget();
			}

		}
	}

	sf::RenderWindow window(sf::VideoMode(800, 100), "End Game");
	window.setPosition(Vector2i(_window.getPosition().x, _window.getPosition().y - 100));
	Text text;
	if (_turn == Color::White)
	{
		text.setString("BLACK WIN");
	}
	else
	{
		text.setString("WHITE WIN");
	}
	sf::Font font;
	font.loadFromFile("arial.ttf");
	text.setFillColor(Color::Green);
	text.setCharacterSize(100);
	text.setFont(font);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				window.close();
			}
			window.draw(text);
			window.display();
		}


	}
	return true;

}

void Board::castling()
{
}
