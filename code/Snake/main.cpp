#include "Snake.h"
#include <iostream>

void main()
{
	Snake s(5,5);
	s.CreateFood();
	s.CreateSnake();

	char c;
	cin >> c;
}