#include "main.h"

char menu[limY][limX];

void printM() {
	for (int row = 0; row < limY; ++row) {
		fwrite(menu[row], sizeof menu[row], 1, stdout);
		putchar('\n');
	}
}


void printG() {
	for (int row = 0; row < limY; ++row) {
		fwrite(roue[row], sizeof roue[row], 1, stdout);
		putchar('\n');
	}
}

void modify_grid(int startX, int endX, int startY, int endY, char sgn) {
	int localY = startX; int localX = startY;
	for (int i = 0; i <= (endX - startX) * (endY - startY); i++) {
		menu[localX][localY] = sgn;
		if (localY == endX) {
			localX++;
			localY = 0;
		}
		else
			localY++;
	}
}

void black_out() {
	modify_grid(0, limX, 0, limY, 32);
}

void back_in_game() {
	printG();
}

void writeTXT(std::string txt_input, int startX, int startY) {
	int length = txt_input.length();
	for (int i = 0; i <= length; i++)
 		modify_grid(startX + i, startX + i + 1, startY, startY, txt_input[i]);
}



void menu_main() {
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	black_out();
	writeTXT("appuyer sur 'W' ou sur ':' pour relancer !",0.3 * limX,0.8 *limY);
	printM();
	while (true) {
		if (GetAsyncKeyState(0x57) & 0x0001 || GetAsyncKeyState(0xBF) & 0x0001) {
			back_in_game();
			pause = false;
			break;
		}
	}
}