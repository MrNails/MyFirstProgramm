#include "Game.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

/*
_coord[?][0] - x
_coord[?][1] - y
_coord[?][2] - state of motion
*/

/*Constructors that initialize the field and array of coordinates*/
Game::Game() : _gameover(false), _form_x(20), _form_y(20) {
	_fruit_x = 1 + rand() % (_form_x - 2);
	_fruit_y = 1 + rand() % (_form_y - 2);
	srand(time(NULL));
	_coord = new int* [(_form_x * _form_y) - 2 * (_form_x + _form_y) + 4];
	for (int i = 0; i < (_form_x * _form_y) - 2 * (_form_x + _form_y) + 4; i++) {
		_coord[i] = new int[3];
	}
	_coord[0][0] = _form_x / 2;
	_coord[0][1] = _form_y / 2;
	_coord[0][2] = -1;
}

Game::Game(const int _form_x_, const int _form_y_) : _gameover(false), _form_x(_form_x_), _form_y(_form_y_) {
	_fruit_x = 1 + rand() % (_form_x - 2);
	_fruit_y = 1 + rand() % (_form_y - 2);
	srand(time(NULL));
	_coord = new int* [(_form_x * _form_y) - 2 * (_form_x + _form_y) + 4];
	for (int i = 0; i < (_form_x * _form_y) - 2 * (_form_x + _form_y) + 4; i++) {
		_coord[i] = new int[3];
	}
	_coord[0][0] = _form_x / 2;
	_coord[0][1] = _form_y / 2;
	_coord[0][2] = -1;
}

/*Displaying the field and the snake on the screen*/
void Game::Display() {
	COORD coord = { 0, 0 };											
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	//It is necessary so that the screen does not flicker when overwriting a field

	cout << "Points: " << _points << ", Esc -> Exit, Backspace -> Main menu\nMove -> wasd(in English layout)\n";
	for (int i = 0; i < _form_y; i++) {
		for (int j = 0; j < _form_x; j++) {
			if (i == 0 || i == _form_y - 1) cout << char(254);
			else if (j == 0 || j == _form_x - 1) cout << char(254);
			else if (j == _fruit_x && i == _fruit_y) cout << "@";
			else if (CheckMethod(i, j)) cout << "*";
			else cout << " ";
		}
		cout << endl;
	}
}


/*Check tail matching with coordinates*/
 bool Game::CheckMethod(int i, int j) {
	for (int count = 0; count < _length; count++) {
		if (_coord[count][0] == j && _coord[count][1] == i) return 1;
	}
	return 0;
}

void Game::Touch() {	
	for (int i = _length - 1; i > 0; i--) {						//Snake Direction Status
		_coord[i][2] = _coord[i - 1][2];
	}

	Sleep(370);
	if (_kbhit()) {												//automatic snake movement
		comand = tolower(_getch());
	}

	switch (comand)
	{
	case 'a':
		if (_coord[0][2] != 2 || _length == 1) {
			_coord[0][2] = 0; _coord[0][0]--;
		}
		else _coord[0][0]++;
		break;													//move left
	case 's':
		if (_coord[0][2] != 3 || _length == 1) {
			_coord[0][2] = 1; 
			_coord[0][1]++;
		} 
		else _coord[0][1]--;
		break;													//move dawn
	case 'd':
		if (_coord[0][2] != 0 || _length == 1) {
			_coord[0][2] = 2;
			_coord[0][0]++;
		}
		else _coord[0][0]--;
		break;													//move rigth
	case 'w':
		if (_coord[0][2] != 1 || _length == 1) {
			_coord[0][2] = 3;
			_coord[0][1]--;
		}
		else _coord[0][1]++;
		break;													//move up
	case 27: _gameover = true; _exit_flag = 1; break;
	case 8: _gameover = true; _exit_flag = 0;
		default:
			if (_coord[0][2] == 0) _coord[0][0]--;				//default head movement
			else if (_coord[0][2] == 1) _coord[0][1]++;
			else if (_coord[0][2] == 2) _coord[0][0]++;
			else if (_coord[0][2] == 3) _coord[0][1]--;
			break;
	}

	while (_kbhit())											//clear input buffer
	{
		_getch();
	}
}

/*Snake behavior logic*/ 
void Game::Logic() {
	if (_coord[0][0] == 0 || _coord[0][1] == 0 || _coord[0][1] == _form_y - 1 || _coord[0][0] == _form_x - 1) _gameover = true;		
	for (int i = 1; i < _length; i++) {																								
		if (_coord[0][0] == _coord[i][0] && _coord[0][1] == _coord[i][1]) {
			_gameover = true;
			break;
		}
	}
	if (_coord[0][0] == _fruit_x && _coord[0][1] == _fruit_y) {
		_points += 10;
		_length++;
		if (_coord[0][2] == 0 && _length == 2) { _coord[1][0] = _coord[0][0] + 1;  _coord[1][1] = _coord[0][1]; }			//These 4 lines are needed in order
		else if (_coord[0][2] == 1 && _length == 2) { _coord[1][1] = _coord[0][1] - 1;	_coord[1][0] = _coord[0][0]; }		//for the tail to work normally and
		else if (_coord[0][2] == 2 && _length == 2) { _coord[1][0] = _coord[0][0] - 1;	_coord[1][1] = _coord[0][1]; }		//they work 1 time
		else if (_coord[0][2] == 3 && _length == 2) { _coord[1][1] = _coord[0][1] + 1;	_coord[1][0] = _coord[0][0]; }
		else {
			_coord[_length - 1][0] = _coord[_length - 2][0];
			_coord[_length - 1][1] = _coord[_length - 2][1];
		}
		_coord[_length - 1][2] = -1;
	}
	if(_length == (_form_x * _form_y) - 2 * (_form_x + _form_y) +4) {
		_gameover = true;	
		cout << "My congratulation, you finished this fucking game(It's my first game)";
		Sleep(5000);
	}
}


void Game::FoodSpawn() {
	for (int i = 0; i < _length && !_gameover; i++) {
		if (_coord[i][0] == _fruit_x && _coord[i][1] == _fruit_y) {
			_fruit_x = 1 + rand() % (_form_x - 2);
			_fruit_y = 1 + rand() % (_form_y - 2);
			FoodSpawn();
		}
	}
}

/*Changing the coordinates of tail objects*/
void Game::Snake_Tail() {
	for (int i = 1; i < _length; i++) {
		if (_coord[i][2] == 0) _coord[i][0]--;
		else if (_coord[i][2] == 1) _coord[i][1]++;
		else if (_coord[i][2] == 2) _coord[i][0]++;
		else if (_coord[i][2] == 3) _coord[i][1]--;
	}
}

bool Game::StartGame() {
	while (!_gameover) {
		Display();
		Touch();
		Logic();
		Snake_Tail();
		FoodSpawn();
	}
	return _exit_flag;
}

/*Delete _coord*/
Game::~Game() {
	for (int i = 0; i < _length; i++) {
		delete _coord[i];
	}
	delete[] _coord;
};