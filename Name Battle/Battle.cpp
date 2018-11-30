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
		"攻撃",
		"戦技",
		"道具",
		"離脱"
};

char skills[4][100];

//戦闘準備画面
void LoadingBattle(HANDLE hWindow, COORD pos) {

	while (1) {
		pos = { 34, 11 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("魔王とのバトル、準備はいいか！！");
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
		printf("魔王とのバトル、準備はいいか！！");
		pos = { 37, 18 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("Press any key to start....");
		if (_kbhit())
			break;
		Sleep(600);
	}
	system("cls");
	rewind(stdin);
	_getch();
}

//戦闘関数
void Battle(HANDLE hWindow, COORD pos, Character Player, Character Enemy) {
	bool battleFinish = false, myTurn = true, craftChoosing = false;
	int row = 0, col = 0, press = 0, successEscape = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			strcpy(skills[i], Player.skill1.name().c_str());
		else if (i == 1)
			strcpy(skills[i], Player.skill2.name().c_str());
		else if (i == 2)
			strcpy(skills[i], Player.skill3.name().c_str());
		else if (i == 3)
			strcpy(skills[i], Player.skill4.name().c_str());
	}

	//=====================================戦闘画面ボーダーを描く=====================================
	BEGINPOSITION LoadCharWindowBeginPosition = { 0, 0 };
	WINDOWSIZE LoadCharWindowSize = { 50, 7, 1 };
	WINDOWSTYLE LoadCharWindowStyle = { "■", COL_CYAN, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

	LoadCharWindowBeginPosition = { 0, 7 };
	LoadCharWindowSize = { 50, 17, 1 };
	LoadCharWindowStyle = { "■", COL_DARK_RED, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

	LoadCharWindowBeginPosition = { 0, 24 };
	LoadCharWindowSize = { 50, 7, 1 };
	LoadCharWindowStyle = { "■", COL_RED, COL_LIGHT_GRAY };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);
	setColor(COL_RED, COL_LIGHT_GRAY);
	for (int i = 0; i < 5; i++) {
		pos.X = 38; pos.Y = 25 + i;
		SetConsoleCursorPosition(hWindow, pos);
		printf("■");
	}
	setColor(COL_WHITE);
	//=================================================================================================

	//==========================================戦闘スタート===========================================
	while (!battleFinish) {

		//=============================キャラクターのステータスと画像を描く============================
		pos = { 4, 10 };
		PrintCharacterStatus(hWindow, pos, Player);
		//=============================================================================================

		//================================Enemyのステータスと画像を描く================================
		pos = { 80, 10 };
		PrintCharacterStatus(hWindow, pos, Enemy);
		//=============================================================================================

		//=====================================プレイヤーのターン======================================
		//===================動作メニューを描く、動作を選択したらその効果を実現する====================
		row = 0, col = 0; press = 0;
		while (press != ENTER) {

			pos = { 10, 26 };
			drawchoices(hWindow, pos, choices, 4, 2, 2, row, col);
			press = getinput(&row, 2, &col, 2, 4);
			if (press == ENTER) {
				pos = { 55, 26 };
				SetConsoleCursorPosition(hWindow, pos);
				if (row == 0 && col == 0) {							//普通攻撃
					printf("%s slash the enemy!\n", Player.name().c_str());
					pos.Y++;
					SetConsoleCursorPosition(hWindow, pos);
					printf("The enemy gets %d damages!", Player.atk());
					Enemy.getDamage(Player.atk());
					Sleep(1200);
					pos = { 55, 26 };
					ClearScreen(hWindow, pos, 3, 30);
				}
				else if (row == 0 && col == 1) {					//戦技
					craftChoosing = true;
					pos = { 10, 26 };
					ClearScreen(hWindow, pos, 3, 20);
					row = 0; col = 0; press = 0;
					while (craftChoosing) {

						pos = { 10, 26 };
						drawchoices(hWindow, pos, skills, 4, 2, 2, row, col);
						pos = { 44, 27 };
						if (row == 0 && col == 0)
							PrintSkillStatus(hWindow, pos, Player.skill1);
						else if (row == 0 && col == 1)
							PrintSkillStatus(hWindow, pos, Player.skill2);
						else if (row == 1 && col == 0)
							PrintSkillStatus(hWindow, pos, Player.skill3);
						else if (row == 1 && col == 1)
							PrintSkillStatus(hWindow, pos, Player.skill4);
						press = getinput(&row, 2, &col, 2, 4);
						if (press == ENTER) {
							pos = { 44, 27 };
							ClearScreen(hWindow, pos, 1, 45);
							pos = { 55, 26 };
							SetConsoleCursorPosition(hWindow, pos);
							if (row == 0 && col == 0) {				//戦技一番目
								if (Player.mp() >= Player.skill1.costMP()) {
									printf("%s used %s\n", Player.name().c_str(), Player.skill1.name().c_str());
									pos.Y++;
									SetConsoleCursorPosition(hWindow, pos);
									printf("The enemy gets %d damages!", Player.skill1.damage());
									Enemy.getDamage(Player.skill1.damage());
									Player.consumeMP(Player.skill1.costMP());
								}
								else {
									printf("MP is not enough to use the craft!");
									Sleep(1200);
									pos = { 55, 26 };
									ClearScreen(hWindow, pos, 3, 40);
									continue;
								}
							}
							else if (row == 0 && col == 1) {		//戦技二番目
								if (Player.mp() >= Player.skill2.costMP()) {
									printf("%s used %s\n", Player.name().c_str(), Player.skill2.name().c_str());
									pos.Y++;
									SetConsoleCursorPosition(hWindow, pos);
									printf("The enemy gets %d damages!", Player.skill2.damage());
									Enemy.getDamage(Player.skill2.damage());
									Player.consumeMP(Player.skill2.costMP());
								}
								else {
									printf("MP is not enough to use the craft!");
									Sleep(1200);
									pos = { 55, 26 };
									ClearScreen(hWindow, pos, 3, 40);
									continue;
								}
							}
							else if (row == 1 && col == 0) {		//戦技三番目
								if (Player.mp() >= Player.skill3.costMP()) {
									printf("%s used %s\n", Player.name().c_str(), Player.skill3.name().c_str());
									pos.Y++;
									SetConsoleCursorPosition(hWindow, pos);
									printf("The enemy gets %d damages!", Player.skill3.damage());
									Enemy.getDamage(Player.skill3.damage());
									Player.consumeMP(Player.skill3.costMP());
								}
								else {
									printf("MP is not enough to use the craft!");
									Sleep(1200);
									pos = { 55, 26 };
									ClearScreen(hWindow, pos, 3, 40);
									continue;
									
								}
							}
							else if (row == 1 && col == 1) {		//戦技四番目
								if (Player.mp() >= Player.skill4.costMP()) {
									printf("%s used %s\n", Player.name().c_str(), Player.skill4.name().c_str());
									pos.Y++;
									SetConsoleCursorPosition(hWindow, pos);
									printf("The enemy gets %d damages!", Player.skill4.damage());
									Enemy.getDamage(Player.skill4.damage());
									Player.consumeMP(Player.skill4.costMP());
								}
								else {
									printf("MP is not enough to use the craft!");
									Sleep(1200);
									pos = { 55, 26 };
									ClearScreen(hWindow, pos, 3, 40);
									continue;
								}
							}
							craftChoosing = false;
							Sleep(1200);
							pos = { 55, 26 };
							ClearScreen(hWindow, pos, 3, 40);
						}
						else if (press == ESC) {
							craftChoosing = false;
							pos = { 44, 27 };
							SetConsoleCursorPosition(hWindow, pos);
							printf("                                            ");
						}
							
						pos = { 10, 26 };
						ClearScreen(hWindow, pos, 3, 25);
					}
				}
				else if (row == 1 && col == 0) {					//道具を使う
					printf("Use item! Not Finish yet.");
					Sleep(1200);
					pos = { 55, 26 };
					ClearScreen(hWindow, pos, 3, 30);
				}
				else {												//戦闘から離脱する
					srand(time(NULL));
					successEscape = (rand() % (100 - 1 + 1)) + 1;
					if (successEscape > 60) {
						printf("Successfully escaped from the battle!");
						battleFinish = true;
					}
					else {
						printf("AHH! Fail to escape from the battle!><");
					}
					Sleep(1200);
					pos = { 55, 26 };
					ClearScreen(hWindow, pos, 3, 40);
				}
				Player.MPrecover(30);
			}
			if (Enemy.hp() <= 0)
				battleFinish = true;
		}
		//================================================================================================

		//=========================================敵のターン=============================================
		pos = { 55, 26 };
		SetConsoleCursorPosition(hWindow, pos);
		printf("%s attacked %s!!", Enemy.name().c_str(), Player.name().c_str());
		pos.Y++;
		SetConsoleCursorPosition(hWindow, pos);
		printf("%s gets %d damages!", Player.name().c_str(), Enemy.atk());
		Player.getDamage(Enemy.atk());
		Sleep(1200);
		pos = { 55, 26 };
		ClearScreen(hWindow, pos, 3, 30);
		//================================================================================================
	}
	//=================================================================================================

}