#include "stdafx.h"
#include "Defines.h"
#include "BackEnd.h"
#include <stdlib.h>		//для srand()
#include <time.h>		//для time()
#include <io.h>			//для _finddata_t

bool IsWin(const Game const * game, const char player)
{
	int playerMark;
	player == 'X' ? playerMark = 1 : playerMark = 2;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (game->field[i][j] != playerMark)
				break;
			if (j == FIELD_SIZE - 1)
				return true;
		}
	}
	for (int j = 0; j < FIELD_SIZE; j++)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			if (game->field[i][j] != playerMark)
				break;
			if (i == FIELD_SIZE - 1)
				return true;
		}
	}
	for (int i = 0, j = 0; i < FIELD_SIZE; i++, j++)
	{
		if (game->field[i][j] != playerMark)
			break;
		if (j == FIELD_SIZE - 1 && i == FIELD_SIZE - 1)
			return true;
	}
	for (int i = 0, j = FIELD_SIZE - 1; i < FIELD_SIZE; i++, j--)
	{
		if (game->field[i][j] != playerMark)
			break;
		if (j == 0 && i == FIELD_SIZE - 1)
			return true;
	}
	return false;
}

bool IsTie(const Game const * game)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (game->field[i][j] == 0)
				return false;
	return true;
}

bool CriticalTurn(Game * game, const char player)
{
	int i, j, countPlayerMarker, freeSpace;
	int playerMarker;
	player == 'O' ? playerMarker = 2 : playerMarker = 1;
	for (i = 0; i < FIELD_SIZE; i++)
	{
		freeSpace = -1;
		countPlayerMarker = 0;
		for (j = 0; j < FIELD_SIZE; j++)
		{
			if (game->field[i][j] == playerMarker)
				countPlayerMarker++;
			if (game->field[i][j] == 0)
				freeSpace = j;
		}
		if (countPlayerMarker == 2 && freeSpace != -1)
		{
			game->field[i][freeSpace] = 2;
			return true;
		}
	}
	for (j = 0; j < FIELD_SIZE; j++)
	{
		freeSpace = -1;
		countPlayerMarker = 0;
		for (i = 0; i < FIELD_SIZE; i++)
		{
			if (game->field[i][j] == playerMarker)
				countPlayerMarker++;
			if (game->field[i][j] == 0)
				freeSpace = i;
		}
		if (countPlayerMarker == 2 && freeSpace != -1)
		{
			game->field[freeSpace][j] = 2;
			return true;
		}
	}
	freeSpace = -1;
	countPlayerMarker = 0;
	for (i = 0, j = 0; i < FIELD_SIZE; i++, j++)
	{
		if (game->field[i][j] == playerMarker)
			countPlayerMarker++;
		if (game->field[i][j] == 0)
			freeSpace = i;
		if (countPlayerMarker == 2 && freeSpace != -1)
		{
			game->field[freeSpace][freeSpace] = 2;
			return true;
		}
	}
	freeSpace = -1;
	countPlayerMarker = 0;
	for (i = 0, j = FIELD_SIZE - 1; i < FIELD_SIZE; i++, j--)
	{
		if (game->field[i][j] == playerMarker)
			countPlayerMarker++;
		if (game->field[i][j] == 0)
			freeSpace = i;
		if (countPlayerMarker == 2 && freeSpace != -1)
		{
			int freeSpaceY;
			freeSpace == 0 ? freeSpaceY = FIELD_SIZE - 1 : freeSpace == 1 ? freeSpaceY = freeSpace : freeSpaceY = 0;
			game->field[freeSpace][freeSpaceY] = 2;
			return true;
		}
	}
	return false;
}

void ComputerTurn(Game * game)
{
	srand(time(NULL));
	if (game->difficult >= HARD && game->field[1][1] == 0)
		game->field[1][1] = 2;
	else
	{
		int i, j;
		if (game->difficult >= MEDIUM)
		{
			for (i = 0; i < FIELD_SIZE; i += 2)
			{
				for (j = 0; j < FIELD_SIZE; j += 2)
					if (game->field[i][j] == 0)
					{
						game->field[i][j] = 2;
						return;
					}
			}
		}
		do {
			i = rand() % 3;
			j = rand() % 3;
		} while (game->field[i][j] != 0);
		game->field[i][j] = 2;
	}
}

bool SaveGame(const Game const * game)
{
	FILE * f = 0;
	errno_t err = fopen_s(&f, "SaveGame.sav", "wb");
	if (err)
		return false;
	fwrite(game, sizeof(Game), 1, f);
	fclose(f);
	f = 0;
	return true;
}

bool LoadGame(Game * game)
{
	FILE * f = 0;
	errno_t err = fopen_s(&f, "SaveGame.sav", "rb");
	if (err)
		return false;
	fread(game, sizeof(Game), 1, f);
	fclose(f);
	f = 0;
	return true;
}

bool IsFileExists(const char * fname)
{
	_finddata_t data;
	long nFind = _findfirst(fname, &data);
	if (nFind != -1)
	{
		_findclose(nFind);
		return true;
	}
	return false;
}