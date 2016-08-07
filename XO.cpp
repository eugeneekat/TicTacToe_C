// XO.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include "Defines.h"
#include "FrontEnd.h"
#include "BackEnd.h"

int main()
{
	//������ ������ �� ����� ��������� ����������
	if (IsReadManual())
	{
		//���� ���� ���� �� ��������� ��� ����� ������� ��������� �� ������
		if (IsFileExists("ReadMe.txt"))
			system("ReadMe.txt");
		else
			printf("Error. Not found ReadMe.txt\n");
	}
	Game game = { 0 };
	//���� ���� ���� ��� �������� � ����� ������ ����������
	if (LoadGame(&game) && ContinuneGame())
	{
		PrintField(&game);
		//��������� ����� ����� ����� � ������� ���������� ���
		if (game.nextTurn == 'O')
		{
			printf("Player two (O) Turn!\n");
			goto playerTwoTurn;
		}
		printf("Player one (X) Turn!\n");
	}
	//����� ��������� ����� ����
	else
	{
		game = { 0 };
		//��������������� ��������� ����
		FillGameSettings(&game);
		PrintField(&game);
	}
	//GamePlay
	while (true)
	{
		//Player One Turn
		PlayerTurn(&game, &playerOne);
		//�������� �������� 2�� ������
		game.nextTurn = playerTwo;
		//���������� ����
		SaveGame(&game);
		PrintField(&game);
		//�������� �� ������ ��� ����� ����� ���� 1�� ������
		if (IsWin(&game, playerOne) || IsTie(&game))
			break;
		//Player Two Turn
	playerTwoTurn:
		//�������� ��� ������, ���� ���������
		if (game.gameMode == 1)
		{
			//���� ���� ����������� ��������
			if (!CriticalTurn(&game, playerOne))
			//�� ��������� ������ ��� �� ������
				ComputerTurn(&game);
		}
		//���� ������ �����
		else
		{
			//��� ������
			PlayerTurn(&game, &playerTwo);
			//�������� �������� 1�� ������
			game.nextTurn = playerOne;
			//���������� ����
			SaveGame(&game);
		}
		PrintField(&game);
		//�������� �� ����� ��� ������ ����� ���� 2�� ������
		if (IsWin(&game, playerTwo) || IsTie(&game))
			break;
	}
	PrintField(&game);
	//Winner Message (�������� ������� � ��������� ���������)
	IsTie(&game) ? printf("Tie!\n") : IsWin(&game, playerOne) ? printf("Player One Win!!!\n") : 
																printf("Player Two Win!!!\n");
	//Delete savegame
	remove("SaveGame.sav");
    return 0;
}
