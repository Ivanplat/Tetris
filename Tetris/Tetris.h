#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Structs.h"
class Tetris
{
public:

	Tetris();


	Point a[4] = {0,0,0,0};
	Point b[4] = { 0,0,0,0 };

	sf::Texture t1;
	sf::Texture t2;
	sf::Texture t3;

	sf::Sprite s;
	sf::Sprite background;
	sf::Sprite frame;

	const static int M = 20;
	const static int N = 10;
	int field[M][N] = { 0 };
	int figures[7][4] = { 
	1,3,5,7, // The form  I
	2,4,5,7, // The form  Z
	3,5,4,6, // The form  S
	3,5,4,7, // The form  T
	2,3,5,7, // The form  L
	3,5,7,6, // The form  J
	2,3,4,5, // The form O
	};


	int dx;
	bool rotate;
	int colorNum;
	float timer;
	float delay;

	sf::Clock clock;

	sf::Event e;

	bool Check();

	virtual void Start();

	virtual void UpdateTime();
	virtual void CheckForKeyboard(sf::RenderWindow& window);
	virtual void Move();
	virtual void Rotate();
	virtual void Tick();
	virtual void CheckLines();
	virtual void Draw(sf::RenderWindow& window);
};

