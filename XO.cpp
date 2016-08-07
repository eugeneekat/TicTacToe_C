// XO.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include "Defines.h"
#include "FrontEnd.h"
#include "BackEnd.h"

int main()
{
	//Узнаем желает ли игрок прочитать руковоство
	if (IsReadManual())
	{
		//Если файл есть то открываем его иначе выводим сообщение об ошибке
		if (IsFileExists("ReadMe.txt"))
			system("ReadMe.txt");
		else
			printf("Error. Not found ReadMe.txt\n");
	}
	Game game = { 0 };
	//Если есть файл для загрузки и игрок желает продолжить
	if (LoadGame(&game) && ContinuneGame())
	{
		PrintField(&game);
		//Определяю какой игрок ходит и передаю управление ему
		if (game.nextTurn == 'O')
		{
			printf("Player two (O) Turn!\n");
			goto playerTwoTurn;
		}
		printf("Player one (X) Turn!\n");
	}
	//Иначе создается новая игра
	else
	{
		game = { 0 };
		//Устанавливаются параметры игры
		FillGameSettings(&game);
		PrintField(&game);
	}
	//GamePlay
	while (true)
	{
		//Player One Turn
		PlayerTurn(&game, &playerOne);
		//Передача контроля 2му игроку
		game.nextTurn = playerTwo;
		//Сохранение игры
		SaveGame(&game);
		PrintField(&game);
		//Проверка на победу или ничью после хода 1го игрока
		if (IsWin(&game, playerOne) || IsTie(&game))
			break;
		//Player Two Turn
	playerTwoTurn:
		//Проверка кто играет, если компьютер
		if (game.gameMode == 1)
		{
			//Если нету критической ситуации
			if (!CriticalTurn(&game, playerOne))
			//то компьютер делает ход по логике
				ComputerTurn(&game);
		}
		//Если играет игрок
		else
		{
			//Ход игрока
			PlayerTurn(&game, &playerTwo);
			//Передача контроля 1му игроку
			game.nextTurn = playerOne;
			//Сохранение игры
			SaveGame(&game);
		}
		PrintField(&game);
		//Проверка на ничью или победу после хода 2го игрока
		if (IsWin(&game, playerTwo) || IsTie(&game))
			break;
	}
	PrintField(&game);
	//Winner Message (тренарый опертор в тренарном операторе)
	IsTie(&game) ? printf("Tie!\n") : IsWin(&game, playerOne) ? printf("Player One Win!!!\n") : 
																printf("Player Two Win!!!\n");
	//Delete savegame
	remove("SaveGame.sav");
    return 0;
}
