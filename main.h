// Pong.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>

#ifndef CONFIG_H
#define CONFIG_H

inline bool pause = false;


const int limX = 100;							// Max lengh of the arena
const int limY = 24;							// Max Height of the arena
inline char roue[limY][limX];

void main_game();
void menu_main();
#endif

// TODO: Référencez ici les en-têtes supplémentaires nécessaires à votre programme.