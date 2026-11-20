#include "main.h"

char Lp1 = '0'; char Lp2 = '0'; char Rp1 = '0'; char Rp2 = '0'; // score


int ballX = 37; int ballY = 3;					// location of the ball
int U = 1; int D = 0; int L = 0; int R = 1;		// orientation of the ball

int V = 1;										// environnemental speed

void fill(char array[limY][limX], int dX, int dY, int fX, int fY, char sgn) { // fonction à ne pas modifier, tout est inversé (x /y)
	int localY = dX;
	int localX = dY;
	for (int i = 0; i < (fX - dX) * (fY - dY) + 1; i++) {
		array[localX][localY] = sgn;
		if (localY == fX - 1)
			localX++, localY = dX;
		else
			localY++;
	}
}

int check(int localX, int localY) {
	char sgnA;
	sgnA = roue[localY][localX];
	return sgnA;
}

void score(char T) {


	if (T == 'L') {
		if (Lp1 == 9) {
			fill(roue, 5, 3, 6, 3, Lp2 += 1);
			Lp1 = -1;
		}
		fill(roue, 6, 3, 7, 3, Lp1 += 1);
	}
	if (T == 'R') {
		if (Rp1 == 9) {
			fill(roue, limX - 5, 3, limX - 4, 3, Rp2 += 1);
			Rp1 = -1;
		}
		fill(roue, limX - 7, 3, limX - 6, 3, Rp1 += 1);
	}
}

void collision_test(int& up, int& down, int& left, int& right, int V) {
	if (check(ballX - V * left - 1, ballY) == '#' || check(V * right + ballX + 1, ballY) == '#') {
		left = !left; right = !right;
	}
	if (check(ballX, ballY - V * up) == '#' || check(ballX, ballY + V * down) == '#') {
		up = !up; down = !down;
	}
	if (check(V * right + ballX + 1, ballY) == 40) {
		left = !left; right = !right;
		score('L');
	}
	if (check(ballX - V * left - 1, ballY) == 41) {
		left = !left; right = !right;
		score('R');
	}
	if (ballY - V * up < 0 || V * down + ballY >= limY) {
		down = !down; up = !up;
	}
}

void ball(int Texture, int V) {
	if (Texture != ' ') {
		collision_test(U, D, L, R, V);
	}
	if (R > 0)
		ballX += V;
	if (L > 0)
		ballX -= V;
	if (U > 0)
		ballY -= V;
	if (D > 0)
		ballY += V;

	fill(roue, ballX, ballY, ballX, ballY, Texture);
}


void rakette1(int locX, int V) {
	int locY = 10;
	int size = 5;
	while (true) {
		if (GetAsyncKeyState(0x41) & 0x0001) {
			if (locY - V > 1) {
				fill(roue, locX, locY, locX + 1, locY + size, 32);
				fill(roue, locX, locY -= V, locX + 1, locY + size - V, '#');
			}
		}
		if (GetAsyncKeyState(0x51) & 0x0001) {
			if (locY + V < limY - size) {
				fill(roue, locX, locY, locX + 1, locY + size, 32);
				fill(roue, locX, locY += V, locX + 1, locY + size + V, '#');
			}
		}
		while (pause == true) {

		}
	}
}

void rakette2(int locX, int V) {
	int locY = 10;
	int size = 5;
	while (true) {
		if (GetAsyncKeyState(0x50) & 0x0001) {
			if (locY - V > 1) {
				fill(roue, locX, locY, locX + 1, locY + size, 32);
				fill(roue, locX, locY -= V, locX + 1, locY + size - V, '#');
			}
		}
		if (GetAsyncKeyState(0x4D) & 0x0001) {
			if (locY + V < limY - size) {
				fill(roue, locX, locY, locX + 1, locY + size, 32);
				fill(roue, locX, locY += V, locX + 1, locY + size + V, '#');
			}
		}
		while (pause == true) {

		}
	}
}



void main_game() {								// ez
	fill(roue, 0, 0, limX, limY, 32);			// clear array
	fill(roue, 0, 0, 1, limY, '(');				// left barrer
	fill(roue, limX - 1, 0, limX, limY, ')');		// right barrer
	std::thread t1(rakette1, 2, V + 1);
	std::thread t2(rakette2, limX - 3, V + 1);

	for (int j = 0; j < 10000; j++) {  // -- frame generator
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		std::cout << "\033[H";

		ball(' ', 0);
		//fill(roue, limX / 2 - 1, 0, limX / 2, limY, '|');
		ball('0', V);
		for (int row = 0; row < limY; ++row) {
			fwrite(roue[row], sizeof roue[row], 1, stdout);
			putchar('\n');
		}
		while (pause == true) {

		}
	}
}