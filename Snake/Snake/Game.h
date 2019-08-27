#pragma once
#ifndef _GAME_H
#define _GAME_H

class Game {
private:
	bool _gameover, 
		_exif_flag = 0;
	const int _form_x, 
		_form_y;
	int _fruit_x,
		_fruit_y,
		_points = 0,
		_length = 1,
		**_coord;
public:
	Game();
	Game(const int, const int);
	~Game();
	void Display();
	void Touch();
	void Logic();
	void Snake_Tail();
	void FoodSpawn();
	bool StartGame();
	bool CheckMethod(int, int);
};
#endif  _GAME_H

