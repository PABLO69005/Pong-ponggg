#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
const int limX = 100;
const int limY = 21;
int ballmX = 20; int ballmY = 10; int ballfX = 21; int ballfY = 10;
char roue[limY][limX];


void fill(char array[limY][limX], int dX, int dY, int fX, int fY, char sgn) { // / à ne pas toucher, tout est inversé (x /y)
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

void ball() {
	int minX = ballmX; int maxX = ballfX; int minY = ballmY; int maxY = ballfY;
	int V = 1;
	int D = 0; 
	if (D == 0)
		fill(roue, minX + V, minY, maxX + V, maxY, '0');
	else if (D == 90)
		fill(roue, minX, minY + V, maxX, maxY + V, 0);
	else if (D == 180)
		fill(roue, minX - V, minY, maxX - V, maxY, 0);
	else if (D == 270)
		fill(roue, minX, minY - V, maxX, maxY - V, 0);
}



int main() {
	fill(roue, 0, 0, limX, limY, 32);
	fill(roue, limX / 2 - 1, 0, limX / 2, limY, '|');
	
	for (int j = 0; j < 10000; j++) {  // -- frame generator
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "\033[H";
		ball();
		for (int row = 0; row < limY; ++row) {
			fwrite(roue[row], sizeof roue[row], 1, stdout);
			putchar('\n');
		}
	}
}
