// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <numeric>
#include <ios>
#include <conio.h>
#include "Game.h"

using namespace std;

template<typename TypeName>
void Check_Func(TypeName _var) {
	while (true) {
		if (cin.get() == '\n' && cin) break;
		else cin.clear();
		cout << "Wrong enter, try again\n";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> _var;
	}
}

int main()
{
	
	int size;

 	while (true) {
		system("CLS");
		cout << "Select field size:\n1 - 10x10\n2 - 20x20(default)\n3 - 30x30\nEsc - Exit\n";
		switch (_getch())
		{
		case 49: size = 10; break;
		case 50: size = 20; break;
		case 51: size = 30; break;
		case 27: return 0;
		default:
			size = 20;
			break;
		}
		system("CLS");
		Game game(size, size);
		if (game.StartGame()) {
			system("CLS");
			cout << "Thank's for play\n";
			return 0;
		}
	}
}

