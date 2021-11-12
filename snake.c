#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int x, y, i = 0;
int width = 30, height = 30, gameover = 0;
int score = 0;
int fruitX = 0, fruitY = 0;
char line[30];
int snake[2] = {15, 15};
int direction = 1; //1 = top, 2 = right, 3 = bottom, 4 = left

void moveSnake() {
	int moveBy[2] = {0, 0};
	switch (direction) {
		case 1:
			moveBy[0] = -1;
			moveBy[1] = 0;
			break;
		case 2:
			moveBy[0] = 0;
			moveBy[1] = 1;
			break;
		case 3:
			moveBy[0] = 1;
			moveBy[1] = 0;
			break;
		case 4:
			moveBy[0] = 0;
			moveBy[1] = -1;
			break;
	}
	snake[0] += moveBy[0];
	snake[1] += moveBy[1];
}

void draw() {
	system("cls");
	for(x = 0; x < width; x++) {
		for(y = 0; y < height; y++) {
			if(x == snake[0] && y == snake[1]) {
				line[i] = 'O';
			} else if(x == fruitX && y == fruitY) {
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
	if(!gameover) {
		printf("Score: %d", score);
		printf("\n");
		printf("Press X to quit the game");
	}
}

void spawnFruit() {
	do {
		fruitX = rand()%width;
	} while(fruitX == 0 || fruitX == width-1);
	do {
		fruitY = rand()%height;
	} while(fruitY == 0 || fruitY == height-1);
}

void startGame() {
	gameover = 0;
	score = 0;

	spawnFruit();
}

void input() {
    if (kbhit()) {
        switch (getch()) {
			case 'w':
				direction = 1;
				break;
			case 'a':
				direction = 4;
				break;
			case 's':
				direction = 3;
				break;
			case 'd':
				direction = 2;
				break;
			case 'x':
				gameover = 1;
				break;
        }
    }
}

void logic() {
	Sleep(250);
	input();
	if(snake[0] == fruitX && snake[1] == fruitY) {
		score += 1;
		while(snake[0] == fruitX && snake[1] == fruitY) {
			spawnFruit();
		}
	}
	moveSnake();
	if(snake[0] == 0 || snake[0] == width-1 || snake[1] == 0 || snake[1] == height-1) {
		gameover = 1;
	} else {
		draw();
	}
}

int main() {
	srand (time(NULL));
	startGame();
	while(!gameover) {
		logic();
	}
	draw();
	printf("Game Over!\n");
	printf("Final score: %d", score);

	return 0;
}