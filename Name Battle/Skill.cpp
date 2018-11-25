#define _CRT_SECURE_NO_WARNINGS
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "Skill.h"
using namespace std;

Skill::Skill() {

}

Skill::Skill(const char *name, int power, int consumeMP) {
	_name = name;
	_power = power;
	_consumeMP = consumeMP;
}