// Pong.cpp : définit le point d'entrée de l'application.
//

#include "main.h"

void interruption() {
		if (GetAsyncKeyState(0x57) & 0x0001 || GetAsyncKeyState(0x4C) & 0x0001) {
			pause = true;

		}
		if (GetAsyncKeyState(0x57) & 0x0001 || GetAsyncKeyState(0x4C) & 0x0001) {
			pause = false;
		}
	}


int main() {
	std::thread t_interr(interruption);
	main_game();

}