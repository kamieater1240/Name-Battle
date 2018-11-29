#pragma once
#ifndef BATTLE_H
#define BATTLE_H
#include "Character.h"

void LoadingBattle(HANDLE hWindow, COORD pos);

void Battle(HANDLE hWindow, COORD pos, Character Player, Character Enemy);

#endif // !BATTLE_H
