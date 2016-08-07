#pragma once

//Размер поля
#define FIELD_SIZE 3
//Структура игры
/*Содержит игровое поле (массив 3 х 3),
сложность (1 - легкая, 2 - средняя, 3 - сложная)
игровой режим (1 - на 1 игрока, 2 - на 2х игроков)
идентификатор игрока, который ходит следующим*/
struct Game
{
	int field[FIELD_SIZE][FIELD_SIZE];
	int difficult;
	int gameMode;
	char nextTurn;
};
//Сложность игры
enum {EASY = 1, MEDIUM, HARD};
//Идентификаторы игроков
const char playerOne = 'X';
const char playerTwo = 'O';