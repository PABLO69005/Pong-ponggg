#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
const int maxX = 90;
const int maxY = 20;
int roue[maxX][maxY];


void fill(int array[maxX][maxY], int dX, int dY, int fX, int fY, int nb) { // /
	int dimX = dX;
	int dimY = dY;
	for (int i = 0; i < (fX - dX) * (fY - dY); i++) {
		array[dimX][dimY] = nb;
		if (dimX == fX - 1)						
			dimY++, dimX = dX;											// Clean and write fonction
		else										
			dimX++;
	}
}																		// /

int ball() {
	int Bframe = 3;
	int V = 1;
	int D = 0; 
	int minX = 30;
	int maxX = 31;
	int minY = 10; 
	int maxY = 11;
	Bframe++;
	if (D == 0)
		fill(roue, minX + V, minY, maxX + V, maxY, Bframe);
	else if (D == 90)
		fill(roue, minX, minY + V, maxX, maxY + V, Bframe);
	else if (D == 180)
		fill(roue, minX - V, minY, maxX - V, maxY, Bframe);
	else if (D == 270)
		fill(roue, minX, minY - V, maxX, maxY - V, Bframe);
	return Bframe;
}
int main() {


	fill(roue, 0, 0, maxX, maxY, 0);
	fill(roue, 44, 0, 45, maxY, 1);



	int	dimX = 0;
	int	dimY = 0;

	for (int j = 0; j < 10000; j++) {  // -- frame generator
		dimX = 0;
		dimY = 0;


		for (int i = 0; i < maxX * maxY; i++) {													// --/-- map generation 
			int Bframe = ball();
			if (roue[dimX][dimY] == 0)
				printf (" ");
			else if (roue[dimX][dimY] == 1)
				printf ( "| |");
			else if (roue[dimX][dimY] == Bframe)
				printf ("O");
			else
				std::cout << "ERR";
			if (dimX == maxX - 1)
				dimY++, dimX = 0, std::cout << "\n";
			else
				dimX++;
		}																						// --/--
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "\033[H";
	}		
}

