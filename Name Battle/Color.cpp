#include <iostream>
#include <Windows.h>
#include "Color.h"
using namespace std;

// �����F�w�� for Windows Console
void setColor(int col)
{
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);     // �R���\�[���n���h���擾
	WORD attr = 0;     //  API �ɓn���A�g���r���[�g
	if (col & COL_INTENSITY)       // ���P�x�r�b�g�������Ă����
		attr |= FOREGROUND_INTENSITY;      //  �A�g���r���[�g�̍��P�x�r�b�g�𗧂Ă�
	if (col & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (col & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (col & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;
	SetConsoleTextAttribute(hCons, attr);        // �F�w��
}

void setColor(int fg, int bg)
{
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attr = 0;
	if (fg & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (fg & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (fg & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (fg & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;

	if (bg & COL_INTENSITY)
		attr |= BACKGROUND_INTENSITY;
	if (bg & COL_RED_MASK)
		attr |= BACKGROUND_RED;
	if (bg & COL_GREEN_MASK)
		attr |= BACKGROUND_GREEN;
	if (bg & COL_BLUE_MASK)
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(hCons, attr);
}