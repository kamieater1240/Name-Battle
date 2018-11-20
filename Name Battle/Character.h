#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
using namespace std;

class Character {
public:
	Character();
	Character(string&, int, int, int, int);

	string& name() {
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

	void name(string& name) {
		_name = name;
	}

	void setproperties(int hp, int atk, int def, int attr) {
		_hp = hp;
		_atk = atk;
		_def = def;
		_attribute = attr;
	}

private:
	string _name;
	int _hp, _atk, _def, _attribute;
};

#endif // !CHARACTER_H