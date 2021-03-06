#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>
using namespace std;

class Skill {
public:
	Skill();
	Skill(const char*, int, int);

	string name() {
		return _name;
	}

	int damage() {
		return _power;
	}

	int costMP() {
		return _consumeMP;
	}

private:
	string _name;
	int _power;
	int _consumeMP;
};

#endif // !SKILL_H