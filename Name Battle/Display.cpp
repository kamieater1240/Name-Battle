#define _CRT_SECURE_NO_WARNINGS
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include "Display.h"
using namespace std;

const char *startText[] =
{
	"セーブクリスタルへようこそ！！\n",
	"よろしくお願いします。\n"
};

//入力する鍵を判断する、それに今選択する選択肢の行列を戻る
int getinput(int *row, int rowNum, int * column, int columnNum, int listNum) {

	int get;
	get = _getch();
	if (get == UP) {
		if (*row > 0)
			*row -= 1;
		else {
			if (((rowNum - 1) * columnNum + *column) > listNum - 1)
				*row = rowNum - 2;
			else
				*row = rowNum - 1;
		}
	}
	else if (get == DOWN) {
		if (*row < rowNum - 1) {
			if (((*row + 1) * columnNum + *column) > listNum - 1)
				*row = 0;
			else
				*row += 1;
		}
		else {
			*row = 0;
		}
	}
	else if (get == LEFT) {
		if (*column > 0)
			*column -= 1;
		else if (*column == 0)
			if ((*row * columnNum + columnNum - 1) > listNum - 1)
				*column = *column + (listNum - 1) - (*row * columnNum);
			else
				*column = columnNum - 1;
	}
	else if (get == RIGHT) {
		if (*column < columnNum - 1 && (*row * columnNum + *column) != listNum - 1)
			*column += 1;
		else
			*column = 0;
	}
	else if (get == ENTER)
		return ENTER;

	return 0;
}

void ClearScreen(HANDLE hWindow, COORD pos, int height, int width) {

	pos = { 0, 0 };
	SetConsoleCursorPosition(hWindow, pos);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf(" ");
		}
	}
	pos = { 0, 0 };
	SetConsoleCursorPosition(hWindow, pos);
}

//make the window by position size type
int makeWindow(HANDLE hwindow, BEGINPOSITION bposition, WINDOWSIZE wsize, WINDOWSTYLE windowStyle)
{
	SetConsoleTextAttribute(hwindow, windowStyle.WindowColor);
	COORD cursorPosition;
	cursorPosition.X = bposition.x;
	cursorPosition.Y = bposition.y;
	string upLine = "";
	string leftAndRightLineWide = "";
	for (size_t uplongi = 0; uplongi < wsize.x; uplongi++)
	{
		upLine += windowStyle.WindowFrameStyle;
	}
	for (size_t uplongsize = 0; uplongsize < wsize.wide; uplongsize++)
	{
		leftAndRightLineWide += windowStyle.WindowFrameStyle;
		SetConsoleCursorPosition(hwindow, cursorPosition);
		cout << upLine;
		cursorPosition.Y++;
	}
	if (wsize.y > wsize.wide * 2)
	{
		for (size_t lArlongi = 0; lArlongi < (wsize.y - wsize.wide * 2); lArlongi++)
		{
			SetConsoleCursorPosition(hwindow, cursorPosition);
			cout << leftAndRightLineWide;
			cursorPosition.X += windowStyle.WindowFrameStyle.length() * (wsize.x - wsize.wide);
			SetConsoleCursorPosition(hwindow, cursorPosition);
			cout << leftAndRightLineWide;
			cursorPosition.X = bposition.x;
			cursorPosition.Y++;
		}
	}
	SetConsoleCursorPosition(hwindow, cursorPosition);
	for (size_t uplongsize = 0; uplongsize < wsize.wide; uplongsize++)
	{
		SetConsoleCursorPosition(hwindow, cursorPosition);
		cout << upLine;
		cursorPosition.Y++;
	}
	cursorPosition.X = bposition.x + windowStyle.WindowFrameStyle.length() * wsize.wide;
	cursorPosition.Y = bposition.y + wsize.wide;
	SetConsoleCursorPosition(hwindow, cursorPosition);
	SetConsoleTextAttribute(hwindow, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	return 0;
}

//選択肢を描く
void drawchoices(HANDLE hWindow, COORD pos, char(*choice)[100], int listNum, int index) {

	COORD Moto_pos = pos;
	int strlength;

	SetConsoleCursorPosition(hWindow, pos);
	for (int i = 0; i < listNum; i++) {
		if (i == index) {
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		}
		else {
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		SetConsoleCursorPosition(hWindow, pos);
		pos.Y++;
		printf("%s", choice[i]);
	}
	return;
}

//既存キャラクターを画面に表示する
void drawchoices_forLoad(HANDLE hWindow, COORD pos, vector<Character> loadList, int listNum, int indexsize, int columnsize, int index, int column) {


	pos = { 2, 4 };
	SetConsoleCursorPosition(hWindow, pos);

	for (int i = 0; i < indexsize; i++) {
		pos.X = 2;
		pos.Y = 4 + i * 2;
		SetConsoleCursorPosition(hWindow, pos);
		for (int j = 0; j < columnsize; j++) {
			pos.X = 2 + j * 10;
			SetConsoleCursorPosition(hWindow, pos);

			if (i == index && j == column) {
				SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}

			printf("%s", loadList[i * 3 + j].name());

			if ((i * 3 + j) == listNum - 1)
				break;
		}
	}
}

//開始画面を描く
int DrawStartMenu(HANDLE hWindow, COORD pos) {
	int strlength, press, row = 0, column = 0;
	char choices[2][100] = {
	"新規生成\n",
	"既存ロード"
	};

	SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
	system("cls");

	Sleep(400);
	BEGINPOSITION LoadCharWindowBeginPosition = { 25,6 };
	WINDOWSIZE LoadCharWindowSize = { 50, 8, 1 };
	WINDOWSTYLE LoadCharWindowStyle = { "*",0xB };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

	for (int i = 0; i < objectnum(startText); i++) {
		strlength = strlen(startText[i]);
		pos.X = 50 - strlength / 2;
		pos.Y = 9 + i;
		SetConsoleCursorPosition(hWindow, pos);
		Sleep(400);
		printf("%s", startText[i]);
		Sleep(400);
	}

	pos = { 41, 29 };
	SetConsoleCursorPosition(hWindow, pos);
	printf("Copyright (c) 2018 Josh, All rights reserved.");

	//選択を描く
	LoadCharWindowBeginPosition = { 40, 15 };
	LoadCharWindowSize = { 20, 4, 1 };
	LoadCharWindowStyle = { "*",0xB };
	makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);
	while (1) {
		pos = { 41, 16 };
		drawchoices(hWindow, pos, choices, 2, row);
		press = getinput(&row, 2, &column, 1, 2);
		if (press == ENTER) {
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
			system("cls");
			return row;
		}
	}
}

//既存キャラクターをロードする
int LoadCharacter(HANDLE hWindow, COORD pos, vector<Character> loadList, int listNum) {
	int press, row = 0, column = 0;

	while (1) {
		pos = { 0, 0 };
		SetConsoleCursorPosition(hWindow, pos);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		BEGINPOSITION LoadCharWindowBeginPosition = { 0,0 };
		WINDOWSIZE LoadCharWindowSize = { 50,29,1 };
		WINDOWSTYLE LoadCharWindowStyle = { "■",0xB };
		makeWindow(hWindow, LoadCharWindowBeginPosition, LoadCharWindowSize, LoadCharWindowStyle);

		pos = { 4, 2 };
		SetConsoleCursorPosition(hWindow, pos);
		printf("どのキャラクターを選びますか？");
		drawchoices_forLoad(hWindow, pos, loadList, listNum, ((listNum - 1) / 3) + 1, 3, row, column);
		press = getinput(&row, ((listNum - 1) / 3) + 1, &column, 3, listNum);
		if (press == ENTER) {
			return row * 3 + column;
		}
	}

	return 0;
}