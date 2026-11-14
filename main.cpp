#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
const int limX = 100;
const int limY = 21;
int ballX = 47; int ballY = 18;
int U = 1; int D = 0; int L = 0; int R = 1;
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



int main() {
	fill(roue, 0, 0, limX, limY, 32);			// clear array
	fill(roue, 0, 0, 1, limY, '(');				// left barrer
	fill(roue, limX - 1, 0, limX, limY, ')');		// right barrer

	
	for (int j = 0; j < 10000; j++) {  // -- frame generator
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		std::cout << "\033[H";
		ball(' ', 0);
		fill(roue, limX / 2 - 1, 0, limX / 2, limY, '|');
		ball('0', 1);
		for (int row = 0; row < limY; ++row) {
			fwrite(roue[row], sizeof roue[row], 1, stdout);
			putchar('\n');
		}
	}
}
