// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Game.h"

using namespace std;


int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	int size;

 	while (true) {
		system("CLS");
		cout << "Select field size:\n1 - 10x10\n2 - 20x20(default)\n3 - 30x30\n4 - 50x50\n5 - 60x60\nEsc - Exit\n";
		switch (_getch())
		{
		case 49: size = 10; break;
		case 50: size = 20; break;
		case 51: size = 30; break;
		case 52: size = 50; break;
		case 53: size = 60; break;
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

