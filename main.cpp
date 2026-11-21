// Pong.cpp : définit le point d'entrée de l'application.
//

#include "main.h"

void menuinit() {
	while (true) {
		if (GetAsyncKeyState(0x57) & 0x0001 && pause == false || GetAsyncKeyState(0xBF) & 0x0001 && pause == false) {
			pause = true;
			menu_main();
		}
	}
}


int main() {
	std::thread t_menu(menuinit);
	main_game();
}