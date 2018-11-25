#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Skill.h"
using namespace std;

class Character {
public:
	Character(const char *, const char *, const char *, const char *);
	Character(string&, int, int, int, int, int, const char *, const char *, const char *, const char *);

	string name() {
		return _name;
	}

	int hp() {
		return _hp;
	}

	int atk() {
		return _atk;
	}

	int def() {
		return _def;
	}

	int attribute() {
		return _attribute;
	}

	int mp() {
		return _mp;
	}

	void name(string& name) {
		_name = name;
	}

	void name(const char *name) {
		_name = name;
	}

	void setproperties(string name, int hp, int atk, int def, int attr, int mp) {
		_name = name;
		_hp = hp;
		_atk = atk;
		_def = def;
		_attribute = attr;
		_mp = mp;
	}

private:
	string _name;
	int _hp, _atk, _def, _attribute, _mp;
	Skill skill1, skill2, skill3, skill4;
};

#endif // !CHARACTER_H