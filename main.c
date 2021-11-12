#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int x, y, i = 0;
int width = 30, height = 30, gameover, score;
int fruitX = 0, fruitY = 0;
char line[30];

void draw() {
	for(x = 0; x < width; x++) {
		for(y = 0; y < height; y++) {
			if(x == fruitX && y == fruitY) {
				line[i] = '$';
			} else if(x == 0 || x == width-1 || y == 0 || y == height-1) {
				line[i] = '#';
			} else {
				line[i] = ' ';
			}
			i++;
		}
		printf(line);
		printf("\n");
		i = 0;
	}
}

void spawnFruit() {
	while(!fruitX) {
		fruitX = rand()%width;
	}
	while(!fruitY) {
		fruitY = rand()%height;
	}
	
}

void startGame() {
	gameover = 0;
	score = 0;

	spawnFruit();
}

void logic() {
	draw();
}

int main() {
	startGame();
	logic();

	return 0;
}