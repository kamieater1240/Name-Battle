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

//���͂����L�����N�^�[���O�����݂��Ă��邩�ǂ����m�F����
bool FindName(Character *input, vector<Character> loadList, int loadNum);

//Cursor�̍��W
COORD pos = { 0, 0 };

void main() {
	//--------------------------------------�R���\�[���ϐ�-------------------------------------------
	//window handle��͂�
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	//Cursor�������
	CONSOLE_CURSOR_INFO CCI;

	//window��cursor���B��
	CCI.dwSize = 1;
	CCI.bVisible = false;
	SetConsoleCursorInfo(hWindow, &CCI);

	//window title��ݒ肷��
	SetConsoleTitleA("�l�[���@�o�g���[");
	//-----------------------------------------------------------------------------------------------

	//-----------------------------------------�f�[�^���[�h------------------------------------------------
	//�t�@�C�����I�[�v������
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
	//�L�����N�^�[�ϐ���錾����
	Character input_status("Fatal Crescent Flash", "Fatal Helix", "Termination Slash - Dawn", "Rebellious Sword Dance");
	Character *in_st;
	in_st = &input_status;
	//=========================================//

	//--------------------------------------�J�n��ʂ�\������-------------------------------------------
	int CreateorLoad;
	bool flag_finished = true;

	while (flag_finished) {
		//=========================================//
		CreateorLoad = DrawStartMenu(hWindow, pos);
		//�V�K�L�����N�^�[�𐶐�����
		if (CreateorLoad == 0) {

			int temphp, tempatk, tempdef, tempattr;
			char tempname[100];

			//srand((unsigned)time(NULL));

			printf("�L�����N�^�[�̖��O����͂��Ă�������:");
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
				printf("���������L�����N�^�[\n");
				pos = { 40, 8 };
				PrintPlayerStatus(hWindow, pos, *in_st);
			}
			else {
				pos = { 32, 7 };
				SetConsoleCursorPosition(hWindow, pos);
				printf("�L�����N�^�[�͂��łɑ��݂��Ă��܂��B\n");
				pos = { 40, 8 };
				PrintPlayerStatus(hWindow, pos, *in_st);
			}
		}
		//=========================================//

		//=========================================//
		//�����L�����N�^�[�����[�h����
		else {
			if (characterNum == 0) {
				SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
				system("cls");
				printf("�܂��L�����N�^�[�����Ȃ�����A�V�K�������Ă�������...");
				Sleep(2000);
				continue;
			}

			int getNum = 0;
			getNum = LoadCharacter(hWindow, pos, saved_Characters, characterNum);
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0x0);
			system("cls");

			pos = { 32, 7 };
			SetConsoleCursorPosition(hWindow, pos);
			printf("%d�ԖڃL�����N�^�[���Q�b�g���܂�!!!!!\n", getNum + 1);

			*in_st = saved_Characters[getNum];
			pos = { 42, 8 };
			PrintPlayerStatus(hWindow, pos, *in_st);
		}
		flag_finished = false;
		rewind(stdin);
		getchar();
		rewind(stdin);
		_getch();
	}

	//START BATTLE !!!!!!!!!!!!!!!!!!!!!!!!======================================================//
	//�o�g��������ʂ�\������
	ClearScreen(hWindow, pos, 30, 100);
	LoadingBattle(hWindow, pos);
	
	rewind(stdin);
	_getch();
	system("cls");

	pos = { 35, 11 };
	SetConsoleCursorPosition(hWindow, pos);
	SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("�͂��A�o�g���`�I���I�Id(`��ͥ)b");
	pos = { 25, 12 };
	SetConsoleCursorPosition(hWindow, pos);
	printf("�i�o�g���̕����͂܂��ł��Ă��Ȃ��A���߂�Ȃ����B�j");

	//===========================================================================================//

	rewind(stdin);
	getchar();
	return;
}

bool FindName(Character *input, vector<Character> loadList, int loadNum) {

	char check1[100], check2[100];

	for (int i = 0; i < input->name().length(); i++)
		check1[i] = tolower(input->name()[i]);
	check1[input->name().length()] = '\0';

	for (int i = 0; i < loadNum; i++) {

		for (int j = 0; j < loadList[i].name().length(); j++)
			check2[j] = tolower(loadList[i].name()[j]);
		check2[loadList[i].name().length()] = '\0';

		//���Ƃ����͂��ꂽ���O�̃A���t�@�x�b�g�̑召������Ă��������O�𔻒f�ł���
		if (!strcmp(check1, check2)) {
			input->setproperties(input->name(), loadList[i].hp(), loadList[i].atk(), loadList[i].def(), loadList[i].attribute(), 200);
			return true;
		}
	}
	return false;
}