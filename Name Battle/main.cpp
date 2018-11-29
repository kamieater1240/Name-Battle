#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Display.h"
#include "Battle.h"
#include "Character.h"
#include "Color.h"
using namespace std;

//Cursorの座標
COORD pos = { 0, 0 };

void main() {
	//--------------------------------------コンソール変数-------------------------------------------
	//window handleを掴む
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	//Cursor情報を取る
	CONSOLE_CURSOR_INFO CCI;

	//windowのcursorを隠す
	CCI.dwSize = 1;
	CCI.bVisible = false;
	SetConsoleCursorInfo(hWindow, &CCI);

	//window titleを設定する
	SetConsoleTitleA("ネーム　バトラー");
	//-----------------------------------------------------------------------------------------------

	//-----------------------------------------データロード------------------------------------------------
	//ファイルをオープンする
	ifstream fload;
	fload.open("status.dat", ios::binary | ios::in);
	
	//Load saved character
	vector<Character> saved_Characters;
	Character load_Character("Fatal Crescent Flash", "Fatal Helix", "Termination Slash - Dawn", "Rebellious Sword Dance");
	string load_name;
	int characterNum = 0;
	
	while (!fload.eof()) {
		fload >> load_name;
		if (load_name == "\0")
			continue;
		
		int temphp, tempatk, tempdef, tempattr;
		char copy[100];
		strcpy(copy, load_name.c_str());
		for (int i = 0; i < strlen(copy); i++)
			copy[i] = tolower(copy[i]);
		copy[strlen(copy)] = '\0';
		int sum = 0;
		for (int i = 0; i < strlen(copy); i++) {
			sum = sum + copy[i];
		}
		srand(sum);

		for (int i = 0; i < 4; i++) {
			if (i == 0)
				temphp = (rand() % (500 - 100 + 1)) + 100;
			else if (i == 1)
				tempatk = (rand() % (100 - 10 + 1)) + 10;
			else if (i == 2)
				tempdef = (rand() % (100 - 10 + 1)) + 10;
			else if (i == 3)
				tempattr = (rand() % (1 - 0 + 1)) + 0;
		}
		load_Character.setproperties(load_name, temphp, tempatk, tempdef, tempattr, 200);
		saved_Characters.push_back(load_Character);
		characterNum++;
	}
	fload.close();
	//--------------------------------------------------------------------------------------------

	//=========================================//
	//キャラクター変数を宣言する
	Character input_status("Fatal Crescent Flash", "Fatal Helix", "Termination Slash - Dawn", "Rebellious Sword Dance");
	Character *in_st;
	in_st = &input_status;
	//=========================================//

	//--------------------------------------開始画面を表示する-------------------------------------------
	int CreateorLoad;
	bool flag_finished = true;

	while (flag_finished) {
		//=========================================//
		CreateorLoad = DrawStartMenu(hWindow, pos);
		//新規キャラクターを生成する
		if (CreateorLoad == 0) {

			int temphp, tempatk, tempdef, tempattr;
			char tempname[100];

			//srand((unsigned)time(NULL));

			printf("キャラクターの名前を入力してください:");
			scanf("%s", tempname);
			in_st->name(tempname);

			char copy[100];
			strcpy(copy, in_st->name().c_str());
			for (int i = 0; i < strlen(copy); i++)
				copy[i] = tolower(copy[i]);
			copy[strlen(copy)] = '\0';
			int sum = 0;
			for (int i = 0; i < strlen(copy); i++) {
				sum = sum + copy[i];
			}
			srand(sum);

			bool HaveorNot = false;
			if (characterNum > 0) {
				HaveorNot = FindName(in_st, saved_Characters, characterNum);
			}

			if (HaveorNot == false) {
				ofstream fsave;
				fsave.open("status.dat", ios::binary | ios::app);
				for (int i = 0; i < 4; i++) {
					if (i == 0)
						temphp = (rand() % (500 - 100 + 1)) + 100;
					else if (i == 1)
						tempatk = (rand() % (100 - 10 + 1)) + 10;
					else if (i == 2)
						tempdef = (rand() % (100 - 10 + 1)) + 10;
					else if (i == 3)
						tempattr = (rand() % (1 - 0 + 1)) + 0;
				}
				in_st->setproperties(tempname, temphp, tempatk, tempdef, tempattr, 200);
				fsave << "\n" << in_st->name();
				fload.close();
			}

			if (HaveorNot == false) {
				pos = { 40, 7 };
				SetConsoleCursorPosition(hWindow, pos);
				printf("自動生成キャラクター\n");
				pos = { 40, 8 };
				PrintCharacterStatus(hWindow, pos, *in_st);
			}
			else {
				pos = { 32, 7 };
				SetConsoleCursorPosition(hWindow, pos);
				printf("キャラクターはすでに存在しています。\n");
				pos = { 40, 8 };
				PrintCharacterStatus(hWindow, pos, *in_st);
			}
		}
		//=========================================//

		//=========================================//
		//既存キャラクターをロードする
		else {
			if (characterNum == 0) {
				SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
				system("cls");
				printf("まだキャラクターがいないから、新規生成してください...");
				Sleep(2000);
				continue;
			}

			int getNum = 0;
			getNum = LoadCharacter(hWindow, pos, saved_Characters, characterNum);
			if (getNum == -1)
				continue;
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
			system("cls");

			pos = { 32, 7 };
			SetConsoleCursorPosition(hWindow, pos);
			printf("%d番目キャラクターをゲットします!!!!!\n", getNum + 1);

			*in_st = saved_Characters[getNum];
			pos = { 42, 8 };
			PrintCharacterStatus(hWindow, pos, *in_st);
		}
		flag_finished = false;
		rewind(stdin);
		getchar();
		rewind(stdin);
		_getch();
	}

	//============================================START GAME !!!!!!!!!!!!!!!!!!!!!!!!=======================================//
	//例として敵、この後他のタイプを増えるのを予定します
	Character Enemy("Slime", 100, 10, 10, 0, 10);
	//バトル準備画面を表示する
	ClearScreen(hWindow, pos, 30, 100);
	LoadingBattle(hWindow, pos);
	//バトルスタート
	Battle(hWindow, pos, *in_st, Enemy);

	rewind(stdin);
	_getch();
	system("cls");
	pos = { 35, 11 };
	SetConsoleCursorPosition(hWindow, pos);
	SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("はい、バトル～終了！！d(`･∀･)b");
	//====================================================================================================================//
	system("cls");
	pos = { 25, 12 };
	SetConsoleCursorPosition(hWindow, pos);
	printf("以上は私のネームバトラーのプロトタイプです。");

	rewind(stdin);
	getchar();
	return;
}