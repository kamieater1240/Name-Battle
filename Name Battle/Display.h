#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <vector>
#include "Character.h"
using namespace std;

//キーボードの入力コードのENUM
enum INPUTCOMMAND {
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};

//windowのサイズ
typedef struct {
	int x;
	int y;
	int wide;
} WINDOWSIZE;

//Windowsのposition
typedef struct {
	int x;
	int y;
} BEGINPOSITION;

//Windowsの形
typedef struct {
	string WindowFrameStyle;
	short WindowTextColor;
	short WindowBGColor;
} WINDOWSTYLE;

int getinput(int *row, int rowNum, int * column, int columnNum, int listNum);

void ClearScreen(HANDLE hWindow, COORD pos, int height, int width);

int makeWindow(HANDLE hwindow, BEGINPOSITION bposition, WINDOWSIZE wsize, WINDOWSTYLE windowStyle);

void drawchoices(HANDLE hWindow, COORD pos, char(*choice)[100], int listNum, int index);

void drawchoices(HANDLE hWindow, COORD pos, char(*choice)[100], int listNum, int indexsize, int columnsize, int index, int column);

void drawchoices_forLoad(HANDLE hWindow, COORD pos, vector<Character> loadList, int listNum, int indexsize, int columnsize, int index, int column);

int DrawStartMenu(HANDLE hWindow, COORD pos);

int LoadCharacter(HANDLE hWindow, COORD pos, vector<Character> loadList, int listNum);

void PrintPlayerStatus(HANDLE hWindow, COORD pos, Character input);

#endif // !DISPLAY_H