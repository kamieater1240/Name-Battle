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
using namespace std;

//���͂����L�����N�^�[���O�����݂��Ă��邩�ǂ����m�F����
bool FindName(Character *input, vector<Character> loadList, int loadNum);

void PrintPlayerStatus(HANDLE hWindow, COORD pos, Character *input);

//Cursor�̍��W
COORD pos = { 0, 0 };

void main() {

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

	//--------------------------------�f�[�^���[�h------------------------------------------------
	//�t�@�C�����I�[�v������
	FILE *fp;
	fp = fopen("status.dat", "ab+");
	if (!fp) {
		printf("Fail to open file...\n");
		exit(1);
	}

	//Load saved character
	vector<Character> saved_Characters;
	Character load_Character("Fatal Crescent Flash", "Fatal Helix", "Termination Slash - Dawn", "Rebellious Sword Dance");
	int characterNum = 0;

	while (fread(&load_Character, sizeof(load_Character), 1, fp) == 1) {
		printf("%d HAHHAA\n", load_Character.hp());
		saved_Characters.push_back(load_Character);
		characterNum++;
	}
	//--------------------------------------------------------------------------------------------

	//=========================================//
	//�L�����N�^�[�ϐ���錾����
	/*STATUS input_status;
	STATUS *in_st;
	in_st = &input_status;*/
	Character input_status("Fatal Crescent Flash", "Fatal Helix", "Termination Slash - Dawn", "Rebellious Sword Dance");
	Character *in_st;
	in_st = &input_status;
	//=========================================//

	//�J�n��ʂ�\������-------------------------------------------
	int CreateorLoad;
	bool flag_finished = true;
	while (flag_finished) {
		//=========================================//
		CreateorLoad = DrawStartMenu(hWindow, pos);
		//�V�K�L�����N�^�[�𐶐�����
		if (CreateorLoad == 0) {

			int temphp, tempatk, tempdef, tempattr;
			char tempname[100];

			srand((unsigned)time(NULL));

			printf("�L�����N�^�[�̖��O����͂��Ă�������:");
			scanf("%s", tempname);
			in_st->name(tempname);

			bool HaveorNot = false;
			if (characterNum > 0) {
				HaveorNot = FindName(in_st, saved_Characters, characterNum);
			}

			if (HaveorNot == false) {
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
				fwrite(in_st, sizeof(*in_st), 1, fp);
			}

			fclose(fp);

			if (HaveorNot == false) {
				pos = { 40, 7 };
				SetConsoleCursorPosition(hWindow, pos);
				printf("���������L�����N�^�[\n");
				PrintPlayerStatus(hWindow, pos, in_st);
			}
			else {
				pos = { 32, 7 };
				SetConsoleCursorPosition(hWindow, pos);
				printf("�L�����N�^�[�͂��łɑ��݂��Ă��܂��B\n");
				PrintPlayerStatus(hWindow, pos, in_st);
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
			PrintPlayerStatus(hWindow, pos, in_st);
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

		/*for (int j = 0; j < strlen((loadList + i)->name); j++)
			check2[j] = tolower((loadList + i)->name[j]);
		check2[strlen((loadList + i)->name)] = '\0';*/
		/*for (auto i = loadList.begin(); i != loadList.end(); i++) {


		}*/
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

void PrintPlayerStatus(HANDLE hWindow, COORD pos, Character *input) {
	
	pos = { 42, 8 };
	SetConsoleCursorPosition(hWindow, pos);
	printf("�L�����N�^�[\n");
	
	for (int i = 0; i < 5; i++) {
		pos.Y = 10 + i;
		SetConsoleCursorPosition(hWindow, pos);
		if (i == 0)
			printf("���O�F%s", input->name().c_str());
		else if (i == 1)
			printf("HP�F%d", input->hp());
		else if (i == 2)
			printf("ATK�F%d", input->atk());
		else if (i == 3)
			printf("DEF�F%d", input->def());
		else {
			if(input->attribute() == 0)
				printf("ATTRIBUTE�FPhysic", input->attribute());
			else
				printf("ATTRIBUTE�FMagic", input->attribute());
		}
	}
}