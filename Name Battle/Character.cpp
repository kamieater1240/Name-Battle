#define _CRT_SECURE_NO_WARNINGS
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "Character.h"
using namespace std;

Character::Character() {
	_name = "No name character";
	_hp = 100;
	_atk = 10;
	_def = 10;
	_attribute = 0;
}

Character::Character(string &name, int HP, int ATK, int DEF, int ATTR) 
	:_name(name), _hp(HP), _atk(ATK), _def(DEF), _attribute(ATTR)
{
	
}