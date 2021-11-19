#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int x, y;
int width = 30, height = 30, gameover = 0;
int score = 0, snakeLength = 1;
int fruitX = 0, fruitY = 0;
char row[31];
int snake[900][2] = {{15, 15}};
int direction = 0; //1 = top, 2 = right, -1 = bottom, -2 = left

int isSnakeBody(int coordinates[2], int snakeBody[900][2], int snakeLength, int startIndex) {
	for(int i = startIndex; i < snakeLength; i++) {
        if(snakeBody[i][0] == coordinates[0] && snakeBody[i][1] == coordinates[1]) {
            return 1;
		}
    }
    return 0;
}

void moveSnakeCell(int snake[900][2], int cellPos, int dir) {
	int moveBy[2] = {0, 0};
	switch (dir) {
		case 1:
			moveBy[0] = 0;
			moveBy[1] = -1;
			break;
		case 2:
			moveBy[0] = 1;
			moveBy[1] = 0;
			break;
		case -1:
			moveBy[0] = 0;
			moveBy[1] = 1;
			break;
		case -2:
			moveBy[0] = -1;
			moveBy[1] = 0;
			break;
	}
	snake[cellPos][0] += moveBy[0];
	snake[cellPos][1] += moveBy[1];
}

void moveSnake() {
	for(int i = snakeLength; i >= 1; i--) {
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
	}
	moveSnakeCell(snake, 0, direction);
	if(isSnakeBody(snake[0], snake, snakeLength, 1)) {
		gameover = 1;
	}
}

void draw() {
	system("cls");
	row[30] = '\0';
	for(y = 0; y < height; y++) {
		int i = 0;
		for(x = 0; x < width; x++) {
			int coord[2] = {x, y};
			if(isSnakeBody(coord, snake, snakeLength, 0)) {
				row[i] = 'O';
			} else if(x == fruitX && y == fruitY) {
				row[i] = '$';
			} else if(x == 0 || x == width-1 || y == 0 || y == height-1) {
				row[i] = '#';
			} else {
				row[i] = ' ';
			}
			i++;
		}
		printf("%s\n", row);
	}
	if(!gameover) {
		printf("Score: %d\n", score);
		printf("Press W, A, S, or D to move the snake\n");
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

void spawnSnake() {
	do {
		snake[0][0] = rand()%width;
	} while(snake[0][0] == 0 || snake[0][0] == width-1);
	do {
		snake[0][1] = rand()%height;
	} while(snake[0][1] == 0 || snake[0][1] == height-1);
}

void startGame() {
	gameover = 0;
	score = 0;

	spawnFruit();
	spawnSnake();
}

void input() {
    if (kbhit()) {
		int newDirection = direction;
        switch (getch()) {
			case 'w':
			case 'W':
				newDirection = 1;
				break;
			case 'a':
			case 'A':
				newDirection = -2;
				break;
			case 's':
			case 'S':
				newDirection = -1;
				break;
			case 'd':
			case 'D':
				newDirection = 2;
				break;
			case 'x':
			case 'X':
				gameover = 1;
				break;
        }
		if(newDirection != -direction || snakeLength == 1) {
			direction = newDirection;
		}
    }
}

void logic() {
	Sleep(250);
	input();
	if(snake[0][0] == fruitX && snake[0][1] == fruitY) {
		snake[snakeLength][0] = snake[snakeLength-1][0];
		snake[snakeLength][1] = snake[snakeLength-1][1];
		moveSnakeCell(snake, snakeLength, -direction);
		score += 1;
		snakeLength += 1;
		while(snake[0][0] == fruitX && snake[0][1] == fruitY) {
			spawnFruit();
		}
	}
	moveSnake();
	if(snake[0][0] == 0 || snake[0][0] == width-1 || snake[0][1] == 0 || snake[0][1] == height-1) {
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