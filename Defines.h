#pragma once

//������ ����
#define FIELD_SIZE 3
//��������� ����
/*�������� ������� ���� (������ 3 � 3),
��������� (1 - ������, 2 - �������, 3 - �������)
������� ����� (1 - �� 1 ������, 2 - �� 2� �������)
������������� ������, ������� ����� ���������*/
struct Game
{
	int field[FIELD_SIZE][FIELD_SIZE];
	int difficult;
	int gameMode;
	char nextTurn;
};
//��������� ����
enum {EASY = 1, MEDIUM, HARD};
//�������������� �������
const char playerOne = 'X';
const char playerTwo = 'O';