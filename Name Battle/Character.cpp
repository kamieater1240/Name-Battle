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

Character::Character(const char *SkillName1, const char *SkillName2, const char *SkillName3, const char *SkillName4) {
	_name = "No name character";
	_hp = 100;
	_atk = 10;
	_def = 10;
	_attribute = 0;
	_mp = 200;
	skill1 = Skill(SkillName1, 50, 40);
	skill2 = Skill(SkillName2, 80, 60);
	skill3 = Skill(SkillName3, 120, 100);
	skill4 = Skill(SkillName4, 200, 200);
}

Character::Character(const char *name, int HP, int ATK, int DEF, int ATTR, int MP)
	:_name(name), _hp(HP), _atk(ATK), _def(DEF), _attribute(ATTR), _mp(MP)
{

}

Character::Character(const char *name, int HP, int ATK, int DEF, int ATTR, int MP, const char *SkillName1, const char *SkillName2, const char *SkillName3, const char *SkillName4)
	:_name(name), _hp(HP), _atk(ATK), _def(DEF), _attribute(ATTR), _mp(MP)
{
	skill1 = Skill(SkillName1, 50, 20);
	skill2 = Skill(SkillName2, 80, 60);
	skill3 = Skill(SkillName3, 120, 100);
	skill4 = Skill(SkillName4, 200, 200);
}

void Character::getDamage(int damage) {
	_hp -= damage;
	if (_hp < 0)
		_hp = 0;
}

void Character::consumeMP(int consumedMP) {
	_mp -= consumedMP;
	if (_mp < 0)
		_mp = 0;
}

void Character::MPrecover(int recoveredMP) {
	_mp += recoveredMP;
	if (_mp > 200)
		_mp = 200;
}