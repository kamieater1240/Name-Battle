#define _CRT_SECURE_NO_WARNINGS
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "Battle.h"
#include "Display.h"
#include "Color.h"
using namespace std;

char choices[4][100] = {
		"�U��",
		"��Z",
		"����",
		"���E"
};

//�퓬�������
void LoadingBattle(HANDLE hWindow, COORD pos) {

	while (1) {
		pos = { 34, 11 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("�����Ƃ̃o�g���A�����͂������I�I");
		pos = { 37, 18 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("Press any key to start....");
		if (_kbhit())
			break;
		Sleep(600);

		pos = { 34, 11 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("�����Ƃ̃o�g���A�����͂������I�I");
		pos = { 37, 18 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("Press any key to start....");
		if (_kbhit())
			break;
		Sleep(600);
	}
	system("cls");
}

//�퓬�֐�
void Battle(HANDLE hWindow, COORD pos, Character Player, Character Enemy) {
	bool battleFinish = false, myTurn = true;
	int row = 0, col = 0, press = 0;
	//=====================================�퓬��ʃ{�[�_�[��`��=====================================
	BEGINPOSITION LoadCharWindowBeginPosition = { 0, 0 };
	WINDOWSIZE LoadCharWindowSize = { 50, 7, 1 };
	WINDOWSTYLE LoadCharWindowStyle = { "��", COL_CYAN, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

	LoadCharWindowBeginPosition = { 0, 7 };
	LoadCharWindowSize = { 50, 17, 1 };
	LoadCharWindowStyle = { "��", COL_DARK_RED, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

	LoadCharWindowBeginPosition = { 0, 24 };
	LoadCharWindowSize = { 50, 7, 1 };
	LoadCharWindowStyle = { "��", COL_RED, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);
	setColor(COL_RED, COL_LIGHT_GRAY);
	for (int i = 0; i < 5; i++) {
		pos.X = 38; pos.Y = 25 + i;
		SetConsoleCursorPosition(hWindow, pos);
		printf("��");
	}
	setColor(COL_WHITE);
	//================================================================================================
	while (!battleFinish) {

		//=============================�L�����N�^�[�̃X�e�[�^�X�Ɖ摜��`��===============================
		pos = { 4, 10 };
		PrintCharacterStatus(hWindow, pos, Player);
		//=============================================================================================
		//================================Enemy�̃X�e�[�^�X�Ɖ摜��`��==================================
		pos = { 80, 10 };
		PrintCharacterStatus(hWindow, pos, Enemy);
		//=============================================================================================
		//=====================================���상�j���[��`��========================================
		row = 0, col = 0;
		while (press != ENTER) {

			pos = { 10, 26 };
			drawchoices(hWindow, pos, choices, 4, 2, 2, row, col);
			press = getinput(&row, 2, &col, 2, 4);
			if (press == ENTER) {
				pos = { 55, 26 };
				SetConsoleCursorPosition(hWindow, pos);
				if (row == 0 && col == 0) {							//���ʍU��
					printf("%s slash the enemy!\n", Player.name().c_str());
					pos.Y++;
					SetConsoleCursorPosition(hWindow, pos);
					printf("The enemy get %d damages!", Player.atk());
					Enemy.getDamage(Player.atk());
				}
				else if (row == 0 && col == 1) {					//��Z
					printf("Use craft!");
				}
				else if (row == 1 && col == 0) {					//������g��
					printf("Use item!");
				}
				else {												//�퓬���痣�E
					printf("Successfully escape from the battle!");
					battleFinish = true;
				}
				Sleep(800);
				pos = { 55, 26 };
				ClearScreen(hWindow, pos, 3, 30);
			}
			if (Enemy.hp() <= 0)
				battleFinish = true;
		}
		//================================================================================================
		press = 0;
	}

}