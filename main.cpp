#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <conio.h>

const int limX = 100;							// Max lengh of the arena
const int limY = 21;							// Max Height of the arena

int ballX = 47; int ballY = 18;					// location of the ball
int U = 1; int D = 0; int L = 0; int R = 1;		// orientation of the ball

int V = 1;										// environnemental speed

char roue[limY][limX];


void fill(char array[limY][limX], int dX, int dY, int fX, int fY, char sgn) { // fonction à ne pas modifier, tout est inversé (x /y)
	int localY = dX; 
	int localX = dY;
	for (int i = 0; i < (fX - dX) * (fY - dY)+1; i++) {
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

void collision_test(int &up, int &down, int &left, int &right, int V) {
	if (ballY - V * up < 0 || V * down + ballY >= limY) {
		down = !down; up = !up;
	}
	if (check(ballX - V * left -1, ballY) == 41 || check(V * right + ballX +1, ballY) == 40 ) {
		left = !left; right = !right;
	}
}

void ball(int Texture,int V) {
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
	int size = 4;
	fill(roue, locX, locY, locX+1, locY + size, '#');
	while (true) {
		char touch = ' ';
		touch = _getch(); 

		if (touch == 'z') {
			if (locY + V > 1) {
				for (int i = 0; i <= size; i++) {
					fill(roue, locX, locY, locX+1, locY + i, 32);
				}
					fill(roue, locX, locY -= V, locX + 1, locY + size, '#'); // ne marche pas
			}
		}

	}
	}

int main() {
	fill(roue, 0, 0, limX, limY, 32);			// clear array
	fill(roue, 0, 0, 1, limY, '(');				// left barrer
	fill(roue, limX - 1, 0, limX, limY, ')');		// right barrer
	std::thread t(rakette1, 2, V);

	for (int j = 0; j < 10000; j++) {  // -- frame generator
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		std::cout << "\033[H";
		//ball(' ', 0);
		fill(roue, limX / 2 - 1, 0, limX / 2, limY, '|');
		//ball('0', V);
		for (int row = 0; row < limY; ++row) {
			fwrite(roue[row], sizeof roue[row], 1, stdout);
			putchar('\n');
		}
	}
}
