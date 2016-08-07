#include "Defines.h"
#include "FrontEnd.h"
#include <ctype.h>		// Äëÿ ôóíêöèè toupper()

void PrintField(const Game const * game)
{
	printf("\n\n");
	printf("\t   A  B  C\n");
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		printf("\t%d|", i + 1);
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (game->field[i][j] == 1)
				printf(" X ");
			else if (game->field[i][j] == 2)
				printf(" O ");
			else
				printf("   ");
		}
		printf("|\n");
	}
	printf("\n");
}

void PlayerTurn(Game * game, const char const * player)
{

	char positionX;
	char positionY;
	do {
		printf("Enter position X: ");
		do {
			scanf_s("%c", &positionX);
			positionX = toupper(positionX);
			ClearStdIn();
			if (positionX < 'A' || positionX > 'C')
				printf("Wrong position - try again: ");
		} while (positionX < 'A' || positionX > 'C');
		printf("Enter position Y: ");
		do {
			scanf_s("%c", &positionY);
			ClearStdIn();
			if (positionY < '1' || positionY > '3')
				printf("Wrong position - try again: ");
		} while (positionY < '1' || positionY > '3');
		if (game->field[int(positionY) - 49][int(positionX) - 65] != 0)
			printf("Wrong position, try again!\n");
	} while (game->field[int(positionY) - 49][int(positionX) - 65] != 0);
	if (*player == 'X')
		game->field[int(positionY) - 49][int(positionX) - 65] = 1;
	else
		game->field[int(positionY) - 49][int(positionX) - 65] = 2;
}

void FillGameSettings(Game * game)
{
	printf("Choose game type (1 - one player, 2 - two players): ");
	scanf_s("%d", &game->gameMode);
	while (game->gameMode < 1 || game->gameMode > 2)
	{
		printf("Wrong type!\nChoose game type (1 - one player, 2 - two players): ");
		scanf_s("%d", &game->gameMode);
	}
	if (game->gameMode == 1)
	{
		printf("Choose game difficult\n1 - Easy\n2 - Medium\n3 - Hard\nYour choice: ");
		scanf_s("%d", &game->difficult);
		while (game->difficult < EASY || game->difficult > HARD)
		{
			printf("Wrong difficult!\nChoose game difficult\n1 - Easy\n2 - Medium\n3 - Hard\nYour choice: ");
			scanf_s("%d", &game->difficult);
		}
	}
	ClearStdIn();
}

bool ContinuneGame()
{
	char choice;
	printf("Do you want continune game?(y/n): ");
	scanf_s("%c", &choice);
	ClearStdIn();
	while (true)
	{
		if (toupper(choice) == 'Y' || toupper(choice) == 'N')
			break;
		printf("Wrong choice!\nDo you want continune game?(y/n): ");
		scanf_s("%c", &choice);
		ClearStdIn();
	}
	return toupper(choice) == 'Y' ? true : false;
}

bool IsReadManual()
{
	printf("Do you want read manual?(y/n): ");
	char choice;
	scanf_s("%c", &choice);
	while (true)
	{
		ClearStdIn();
		if (toupper(choice) == 'Y')
			return true;
		else if (toupper(choice) == 'N')
			return false;
		else
		{
			printf("Wrong choice!\nDo you want read manual?(y/n): ");
			scanf_s("%c", &choice);
		}
	}
}
