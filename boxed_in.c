/*
Academic project - Boxed In
C console puzzle game

This file contains a complete playable version of the project.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

// Project function implementations:

void MakeBox(char *design, int width, int height) {

	int widthEven = !(width % 2);
	int heightEven = !(height % 2);

	for (int i = 0; i < width; i++) {

		strcat(design, "#");

	}

	strcat(design, "\n");

	if ((!(widthEven)) && (!(heightEven))) {

		for (int i = 1; i < height-1; i++) {

			strcat(design, "#");

			for (int j = 1; j < width-1; j++) {

				if ((i == height/2) && (j == width/2)) {

					strcat(design, "X");

				} else {

					strcat(design, " ");

				}

			}

			strcat(design, "#\n");

		}

	} else if (widthEven && heightEven) {

		for (int i = 1; i < height-1; i++) {

			strcat(design, "#");

			for (int j = 1; j < width-1; j++) {

				if (((i == height/2) && (j == width/2)) || ((i == (height/2 - 1)) && (j == (width/2 - 1))) || ((i == height/2) && (j == (width/2 - 1))) || ((i == (height/2 - 1)) && (j == width/2))) {

					strcat(design, "X");

				} else {

					strcat(design, " ");

				}

			}

			strcat(design, "#\n");
			
		}

	} else if ((!(widthEven)) && (heightEven)) {

		for (int i = 1; i < height-1; i++) {

			strcat(design, "#");

			for (int j = 1; j < width-1; j++) {

				if (((i == height/2) && (j == width/2)) || ((i == (height/2 - 1)) && (j == width/2))) {

					strcat(design, "X");

				} else {

					strcat(design, " ");

				}

			}

			strcat(design, "#\n");

		}

	} else if ((widthEven) && (!(heightEven))) {

		for (int i = 1; i < height-1; i++) {

			strcat(design, "#");

			for (int j = 1; j < width-1; j++) {

				if (((i == height/2) && (j == width/2)) || ((i == height/2) && (j == (width/2 - 1)))) {

					strcat(design, "X");

				} else {

					strcat(design, " ");

				}

			}

			strcat(design, "#\n");

		}

	}

	for (int i = 0; i < width; i++) {

		strcat(design, "#");

	}

	strcat(design, "\n");
		
}

// Task Two ///////////////////////////////////////////////////////////////
void PrintRoom(int room[ROWS][COLS]) {

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS; j++) {

			if (room[i][j] == SPACE) {

				printf(" ");

			} else if (room[i][j] == WALL) {

				printf("#");

			} else if (room[i][j] == TARGET) {

				printf("*");

			} else if (room[i][j] == BOX) {

				printf("O");

			} else if (room[i][j] == BOX_ON_TARGET) {

				printf("@");

			} else if (room[i][j] == PERSON) {

				printf("X");

			} else if (room[i][j] == PERSON_ON_TARGET) {

				printf("X");

			}

		}

		printf("\n");

	}

}

// Task Three ///////////////////////////////////////////////////////////////
void InitialiseRoom(int room[ROWS][COLS], char *layout) {

	int len = strlen(layout);
	int roomSize = (ROWS * COLS);

	int counter = 0;

	for (int i = 0; i < ROWS; i++) {
	
		for (int j = 0; j < COLS; j++) {

			if ((counter >= len) && (len < roomSize)) {

				room[i][j] = WALL;
				counter++;

			} else if (counter == len) {

				break;

			} else {

				room[i][j] = layout[counter] - '0';
				counter++;

			}

		}

		if (counter == len) {

			break;

		}

	}

}

// Task Four ///////////////////////////////////////////////////////////////
void LocatePerson(int room[ROWS][COLS], int *row, int *col) {

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS; j++) {

			if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {

				*row = i;
				*col = j;
				return;

			}

		}

	}

}

// Task Five - Task Eight ////////////////////////////////////////////////////////
void MakeMove(int room[ROWS][COLS], char move, char *allMoves) {

	int row;
	int col;
	char *wNoBox = "w0";
	char *aNoBox = "a0";
	char *sNoBox = "s0";
	char *dNoBox = "d0";
	char *wBox = "w1";
	char *aBox = "a1";
	char *sBox = "s1";
	char *dBox = "d1";
	int numBoxes = 0;
	int numTargets = 0;
	int numBoxesOnTargets = 0;
	int personIsOnTarget = 0;

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS; j++) {

			if (room[i][j] == BOX) {

				numBoxes++;

			}

			if (room[i][j] == TARGET) {

				numTargets++;

			}

			if (room[i][j] == PERSON_ON_TARGET) {

				personIsOnTarget = 1;

			}

		}

	}

	LocatePerson(room, &row, &col);

	if (move == 'z') {

		UndoMove(room, allMoves);
		return;

	}
	
	if (move == 'w') {

		if (((room[row-1][col] == BOX) || (room[row-1][col] == BOX_ON_TARGET)) && ((room[row-2][col] != SPACE) && (room[row-2][col] != TARGET))) {

			return;

		}

	} else if (move == 'a') {

		if (((room[row][col-1] == BOX) || (room[row][col-1] == BOX_ON_TARGET)) && ((room[row][col-2] != SPACE) && (room[row][col-2] != TARGET))) {

			return;

		}

	} else if (move == 's') {

		if (((room[row+1][col] == BOX) || (room[row+1][col] == BOX_ON_TARGET)) && ((room[row+2][col] != SPACE) && (room[row+2][col] != TARGET))) {

			return;

		}

	} else if (move == 'd') {

		if (((room[row][col+1] == BOX) || (room[row][col+1] == BOX_ON_TARGET)) && ((room[row][col+2] != SPACE) && (room[row][col+2] != TARGET))) {

			return;

		}

	}

	if (!(personIsOnTarget)) {

		if (move == 'w') {

			if ((((room[row-1][col]) == BOX) || ((room[row-1][col]) == BOX_ON_TARGET))) {

				if ((room[row-2][col]) == TARGET && (!((room[row-1][col]) == BOX_ON_TARGET))) {

					room[row-2][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, wBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row-2][col]) == TARGET && ((room[row-1][col]) == BOX_ON_TARGET)) {

					room[row-2][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, wBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row-2][col]) != WALL) && ((room[row-2][col]) != BOX) && ((room[row-1][col]) != BOX_ON_TARGET)) {

					room[row-2][col] = BOX;
					room[row-1][col] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, wBox);
					return;

				} else if (((room[row-2][col]) != WALL) && ((room[row-2][col]) != BOX) && ((room[row-1][col]) == BOX_ON_TARGET)) {

					room[row-2][col] = BOX;
					room[row-1][col] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, wBox);
					return;

				}

			} else if ((room[row-1][col]) == TARGET) {

				room[row-1][col] = PERSON_ON_TARGET;
				room[row][col] = SPACE;
				strcat(allMoves, wNoBox);
				personIsOnTarget = 1;
				return;

			
			} else if (!((room[row-1][col]) == WALL)) {

				room[row-1][col] = PERSON;
				room[row][col] = SPACE;
				strcat(allMoves, wNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 'a') {

			if (((room[row][col-1]) == BOX) || ((room[row][col-1]) == BOX_ON_TARGET)) {

				if ((room[row][col-2]) == TARGET && (!((room[row][col-1]) == BOX_ON_TARGET))) {

					room[row][col-2] = BOX_ON_TARGET;
					room[row][col-1] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, aBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row][col-2]) == TARGET && ((room[row][col-1]) == BOX_ON_TARGET)) {

					room[row][col-2] = BOX_ON_TARGET;
					room[row][col-1] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, aBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row][col-2]) != WALL) && ((room[row][col-2]) != BOX) && ((room[row][col-1]) != BOX_ON_TARGET)) {

					room[row][col-2] = BOX;
					room[row][col-1] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, aBox);
					return;

				} else if (((room[row][col-2]) != WALL) && ((room[row][col-2]) != BOX) && ((room[row][col-1]) == BOX_ON_TARGET)) {

					room[row][col-2] = BOX;
					room[row][col-1] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, aBox);
					return;

				}

			} else if ((room[row][col-1]) == TARGET) {

				room[row][col-1] = PERSON_ON_TARGET;
				room[row][col] = SPACE;
				strcat(allMoves, aNoBox);
				personIsOnTarget = 1;
				return;
			
			} else if (!((room[row][col-1]) == WALL)) {

				room[row][col-1] = PERSON;
				room[row][col] = SPACE;
				strcat(allMoves, aNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 's') {

			if (((room[row+1][col]) == BOX) || ((room[row+1][col]) == BOX_ON_TARGET)) {
				

				if ((room[row+2][col]) == TARGET && (!((room[row+1][col]) == BOX_ON_TARGET))) {

					room[row+2][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, sBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row+2][col]) == TARGET && ((room[row+1][col]) == BOX_ON_TARGET)) {

					room[row+2][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, sBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row+2][col]) != WALL) && ((room[row+2][col]) != BOX) && ((room[row+1][col]) != BOX_ON_TARGET)) {

					room[row+2][col] = BOX;
					room[row+1][col] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, sBox);
					return;

				} else if (((room[row+2][col]) != WALL) && ((room[row+2][col]) != BOX) && ((room[row+1][col]) == BOX_ON_TARGET)) {

					room[row+2][col] = BOX;
					room[row+1][col] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, sBox);
					return;

				}

			} else if ((room[row+1][col]) == TARGET) {

				room[row+1][col] = PERSON_ON_TARGET;
				room[row][col] = SPACE;
				strcat(allMoves, sNoBox);
				personIsOnTarget = 1;
				return;

			} else if (!((room[row+1][col]) == WALL)) {

				room[row+1][col] = PERSON;
				room[row][col] = SPACE;
				strcat(allMoves, sNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 'd') {

			if (((room[row][col+1]) == BOX) || ((room[row][col+1]) == BOX_ON_TARGET)) {

				if ((room[row][col+2]) == TARGET && (!((room[row][col+1]) == BOX_ON_TARGET))) {

					room[row][col+2] = BOX_ON_TARGET;
					room[row][col+1] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, dBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row][col+2]) == TARGET && ((room[row][col+1]) == BOX_ON_TARGET)) {

					room[row][col+2] = BOX_ON_TARGET;
					room[row][col+1] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, dBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;


				} else if (((room[row][col+2]) != WALL) && ((room[row][col+2]) != BOX) && ((room[row][col+1]) != BOX_ON_TARGET)) {

					room[row][col+2] = BOX;
					room[row][col+1] = PERSON;
					room[row][col] = SPACE;
					strcat(allMoves, dBox);
					return;

				} else if (((room[row][col+2]) != WALL) && ((room[row][col+2]) != BOX) && ((room[row][col+1]) == BOX_ON_TARGET)) {

					room[row][col+2] = BOX;
					room[row][col+1] = PERSON_ON_TARGET;
					room[row][col] = SPACE;
					strcat(allMoves, dBox);
					return;

				}
				
			} else if ((room[row][col+1]) == TARGET) {

				room[row][col+1] = PERSON_ON_TARGET;
				room[row][col] = SPACE;
				strcat(allMoves, dNoBox);
				personIsOnTarget = 1;
				return;

			} else if (!((room[row][col+1]) == WALL)) {

				room[row][col+1] = PERSON;
				room[row][col] = SPACE;
				strcat(allMoves, dNoBox);
				return;

			} else {

				return;

			}

		}

	} else if (personIsOnTarget) {

		if (move == 'w') {

			if (((room[row-1][col]) == BOX) || ((room[row-1][col]) == BOX_ON_TARGET)) {

				if ((room[row-2][col]) == TARGET && (!((room[row-1][col]) == BOX_ON_TARGET))) {

					room[row-2][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, wBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row-2][col]) == TARGET && ((room[row-1][col]) == BOX_ON_TARGET)) {

					room[row-2][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, wBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row-2][col]) != WALL) && ((room[row-2][col]) != BOX) && ((room[row-1][col]) != BOX_ON_TARGET)) {

					room[row-2][col] = BOX;
					room[row-1][col] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, wBox);
					return;

				} else if (((room[row-2][col]) != WALL) && ((room[row-2][col]) != BOX) && ((room[row-1][col]) == BOX_ON_TARGET)) {

					room[row-2][col] = BOX;
					room[row-1][col] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, wBox);
					return;

				}

			} else if ((room[row-1][col]) == TARGET) {

				room[row-1][col] = PERSON_ON_TARGET;
				room[row][col] = TARGET;
				strcat(allMoves, wNoBox);
				personIsOnTarget = 1;
				return;
			
			} else if (!((room[row-1][col]) == WALL)) {

				room[row-1][col] = PERSON;
				room[row][col] = TARGET;
				strcat(allMoves, wNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 'a') {

			if (((room[row][col-1]) == BOX) || ((room[row][col-1]) == BOX_ON_TARGET)) {

				if ((room[row][col-2]) == TARGET && (!((room[row][col-1]) == BOX_ON_TARGET))) {

					room[row][col-2] = BOX_ON_TARGET;
					room[row][col-1] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, aBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row][col-2]) == TARGET && ((room[row][col-1]) == BOX_ON_TARGET)) {

					room[row][col-2] = BOX_ON_TARGET;
					room[row][col-1] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, aBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row][col-2]) != WALL) && ((room[row][col-2]) != BOX) && ((room[row][col-1]) != BOX_ON_TARGET)) {

					room[row][col-2] = BOX;
					room[row][col-1] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, aBox);
					return;

				} else if (((room[row][col-2]) != WALL) && ((room[row][col-2]) != BOX) && ((room[row][col-1]) == BOX_ON_TARGET)) {

					room[row][col-2] = BOX;
					room[row][col-1] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, aBox);
					return;

				}

			} else if ((room[row][col-1]) == TARGET) {

				room[row][col-1] = PERSON_ON_TARGET;
				room[row][col] = TARGET;
				strcat(allMoves, aNoBox);
				personIsOnTarget = 1;
				return;
			
			} else if (!((room[row][col-1]) == WALL)) {

				room[row][col-1] = PERSON;
				room[row][col] = TARGET;
				strcat(allMoves, aNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 's') {
			
			if (((room[row+1][col]) == BOX) || ((room[row+1][col]) == BOX_ON_TARGET)) {

				if ((room[row+2][col]) == TARGET && (!((room[row+1][col]) == BOX_ON_TARGET))) {

					room[row+2][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, sBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row+2][col]) == TARGET && ((room[row+1][col]) == BOX_ON_TARGET)) {

					room[row+2][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, sBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;

				} else if (((room[row+2][col]) != WALL) && ((room[row+2][col]) != BOX) && ((room[row+1][col]) != BOX_ON_TARGET)) {

					room[row+2][col] = BOX;
					room[row+1][col] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, sBox);
					return;

				} else if (((room[row+2][col]) != WALL) && ((room[row+2][col]) != BOX) && ((room[row+1][col]) == BOX_ON_TARGET)) {

					room[row+2][col] = BOX;
					room[row+1][col] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, sBox);
					return;

				}

			} else if ((room[row+1][col]) == TARGET) {

				room[row+1][col] = PERSON_ON_TARGET;
				room[row][col] = TARGET;
				strcat(allMoves, sNoBox);
				personIsOnTarget = 1;
				return;

			} else if (!((room[row+1][col]) == WALL)) {

				room[row+1][col] = PERSON;
				room[row][col] = TARGET;
				strcat(allMoves, sNoBox);
				return;

			} else {

				return;

			}

		} else if (move == 'd') {

			if (((room[row][col+1]) == BOX) || ((room[row][col+1]) == BOX_ON_TARGET)) {

				if ((room[row][col+2]) == TARGET && (!((room[row][col+1]) == BOX_ON_TARGET))) {

					room[row][col+2] = BOX_ON_TARGET;
					room[row][col+1] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, dBox);
					numBoxesOnTargets++;
					
					return;

				} else if ((room[row][col+2]) == TARGET && ((room[row][col+1]) == BOX_ON_TARGET)) {

					room[row][col+2] = BOX_ON_TARGET;
					room[row][col+1] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, dBox);
					numBoxesOnTargets++;
					
					personIsOnTarget = 1;
					return;


				} else if (((room[row][col+2]) != WALL) && ((room[row][col+2]) != BOX) && ((room[row][col+1]) != BOX_ON_TARGET)) {

					room[row][col+2] = BOX;
					room[row][col+1] = PERSON;
					room[row][col] = TARGET;
					strcat(allMoves, dBox);
					return;

				} else if (((room[row][col+2]) != WALL) && ((room[row][col+2]) != BOX) && ((room[row][col+1]) == BOX_ON_TARGET)) {

					room[row][col+2] = BOX;
					room[row][col+1] = PERSON_ON_TARGET;
					room[row][col] = TARGET;
					strcat(allMoves, dBox);
					return;

				}
				
			} else if ((room[row][col+1]) == TARGET) {

				room[row][col+1] = PERSON_ON_TARGET;
				room[row][col] = TARGET;
				strcat(allMoves, dNoBox);
				personIsOnTarget = 1;
				return;

			} else if (!((room[row][col+1]) == WALL)) {

				room[row][col+1] = PERSON;
				room[row][col] = TARGET;
				strcat(allMoves, dNoBox);
				return;

			} else {

				return;

			}

		}

	} else {

		return;

	}

}

// Task Nine /////////////////////////////////////////////////////////////////
int CheckGameOver(int room[ROWS][COLS]) {

	int targets = 0;
	int boxesOnTargets = 0;
	int personOnTarget = 0;

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS; j++) {

			if (room[i][j] == TARGET) {

				targets++;

			} else if (room[i][j] == BOX_ON_TARGET) {

				boxesOnTargets++;
				targets++;

			} else if (room[i][j] == PERSON_ON_TARGET) {

				personOnTarget++;
				targets++;

			}

		}

	}

	if ((targets == 0) && (boxesOnTargets == 0)) {

		return 0;

	} else if (personOnTarget > 0) {

		return 0;

	} else if (boxesOnTargets == targets) {

		return 1;

	} else {

		return 0;

	}

	return 0;

}

void UndoMove(int room[ROWS][COLS], char *allMoves) {

	int personIsOnTarget = 0;
	int row;
	int col;
	int length = strlen(allMoves);
	LocatePerson(room, &row, &col);

	if (length < 2) {

		return;

	}

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS; j++) {

			if (room[i][j] == PERSON_ON_TARGET) {

				personIsOnTarget++;

			}

		}

	}

	int targetAbovePerson = 0;
	int targetBelowPerson = 0;
	int targetLeftPerson = 0;
	int targetRightPerson = 0;
	
	if (room[row-1][col] == TARGET) {

		targetAbovePerson = 1;

	} 
	
	if (room[row][col-1] == TARGET) {

		targetLeftPerson = 1;

	} 
	
	if (room[row+1][col] == TARGET) {

		targetBelowPerson = 1;

	} 
	
	if (room[row][col+1] == TARGET) {

		targetRightPerson = 1;

	}

	int len = strlen(allMoves);

	char moved[2];
	char box[2];

	moved[0] = allMoves[len-2];
	moved[1] = '\0';

	box[0] = allMoves[len-1];
	box[1] = '\0';

	char w = strcmp(moved, "w") + 'w';
	char a = strcmp(moved, "a") + 'a';
	char s = strcmp(moved, "s") + 's';
	char d = strcmp(moved, "d") + 'd';
	int boxMoved = (!(strcmp(box, "1")));

	allMoves[len-2] = '\0';

	char directionMoved;

	if (w == 'w') {

		directionMoved = 'w';

	} else if (a == 'a') {

		directionMoved = 'a';

	} else if (s == 's') {

		directionMoved = 's';

	} else if (d == 'd') {

		directionMoved = 'd';

	}

	if (boxMoved == 1) { // A box was moved in the previous move

		if (directionMoved == 'w') {//Previous move was up

			if (personIsOnTarget) { //Player is on a target

				if ((room[row-1][col] == BOX_ON_TARGET) && (targetBelowPerson)) {
					
					// Box and player were on target and a target was behind player
					room[row-1][col] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row-1][col] == BOX_ON_TARGET)) {

					//Box and player were on target but no target was behind player
					room[row-1][col] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON;
					return;

				} else if ((room[row-1][col] == BOX) && (targetBelowPerson)) {

					//Player was on target and a target was behind player
					room[row-1][col] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row-1][col] == BOX)) {

					//Player was on target but no target was behind player
					room[row-1][col] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row+1][col] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((room[row-1][col] == BOX_ON_TARGET) && (targetBelowPerson)) {
					
					// Box was on target and a target was behind player
					room[row-1][col] = TARGET;
					room[row][col] = BOX;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row-1][col] == BOX_ON_TARGET)) {

					//Box was on target but no target was behind player
					room[row-1][col] = TARGET;
					room[row][col] = BOX;
					room[row+1][col] = PERSON;
					return;

				} else if ((room[row-1][col] == BOX) && (targetBelowPerson)) {

					//target was behind player
					room[row-1][col] = SPACE;
					room[row][col] = BOX;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row-1][col] == BOX)) {

					//no target was behind player
					room[row-1][col] = SPACE;
					room[row][col] = BOX;
					room[row+1][col] = PERSON;
					return;

				}

			}

		} else if (directionMoved == 'a') {

			if (personIsOnTarget) { 

				if ((room[row][col-1] == BOX_ON_TARGET) && (targetRightPerson)) {

					room[row][col-1] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col-1] == BOX_ON_TARGET)) {

					room[row][col-1] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row][col+1] = PERSON;
					return;

				} else if ((room[row][col-1] == BOX) && (targetRightPerson)) {

					room[row][col-1] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col-1] == BOX)) {

					room[row][col-1] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row][col+1] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((room[row][col-1] == BOX_ON_TARGET) && (targetRightPerson)) {

					room[row][col-1] = TARGET;
					room[row][col] = BOX;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col-1] == BOX_ON_TARGET)) {

					room[row][col-1] = TARGET;
					room[row][col] = BOX;
					room[row][col+1] = PERSON;
					return;

				} else if ((room[row][col-1] == BOX) && (targetRightPerson)) {

					room[row][col-1] = SPACE;
					room[row][col] = BOX;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col-1] == BOX)) {

					room[row][col-1] = SPACE;
					room[row][col] = BOX;
					room[row][col+1] = PERSON;
					return;

				}

			}
			
		} else if (directionMoved == 's') {

			if (personIsOnTarget) {

				if ((room[row+1][col] == BOX_ON_TARGET) && (targetAbovePerson)) {

					room[row+1][col] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row+1][col] == BOX_ON_TARGET)) {

					room[row+1][col] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON;
					return;

				} else if ((room[row+1][col] == BOX) && (targetAbovePerson)) {
					
					room[row+1][col] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row+1][col] == BOX)) {

					room[row+1][col] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row-1][col] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((room[row+1][col] == BOX_ON_TARGET) && (targetAbovePerson)) {
					
					room[row+1][col] = TARGET;
					room[row][col] = BOX;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row+1][col] == BOX_ON_TARGET)) {

					room[row+1][col] = TARGET;
					room[row][col] = BOX;
					room[row-1][col] = PERSON;
					return;

				} else if ((room[row+1][col] == BOX) && (targetAbovePerson)) {

					room[row+1][col] = SPACE;
					room[row][col] = BOX;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else if ((room[row+1][col] == BOX)) {

					room[row+1][col] = SPACE;
					room[row][col] = BOX;
					room[row-1][col] = PERSON;
					return;

				}
			}
		} else if (directionMoved == 'd') {

			if (personIsOnTarget) {

				if ((room[row][col+1] == BOX_ON_TARGET) && (targetLeftPerson)) {

					room[row][col+1] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col+1] == BOX_ON_TARGET)) {

					room[row][col+1] = TARGET;
					room[row][col] = BOX_ON_TARGET;
					room[row][col-1] = PERSON;
					return;

				} else if ((room[row][col+1] == BOX) && (targetLeftPerson)) {

					room[row][col+1] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col+1] == BOX)) {

					room[row][col+1] = SPACE;
					room[row][col] = BOX_ON_TARGET;
					room[row][col-1] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((room[row][col+1] == BOX_ON_TARGET) && (targetLeftPerson)) {
					
					room[row][col+1] = TARGET;
					room[row][col] = BOX;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col+1] == BOX_ON_TARGET)) {

					room[row][col+1] = TARGET;
					room[row][col] = BOX;
					room[row][col-1] = PERSON;
					return;

				} else if ((room[row][col+1] == BOX) && (targetLeftPerson)) {

					room[row][col+1] = SPACE;
					room[row][col] = BOX;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else if ((room[row][col+1] == BOX)) {

					room[row][col+1] = SPACE;
					room[row][col] = BOX;
					room[row][col-1] = PERSON;
					return;

				}
				
			}

		}

	} else if (boxMoved == 0) {

		if (directionMoved == 'w') {//Previous move was up

			if (personIsOnTarget) { //Player is on a target

				if ((targetBelowPerson)) {
					
					// Box and player were on target and a target was behind player
					room[row][col] = TARGET;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else {

					//Box and player were on target but no target was behind player
					room[row][col] = TARGET;
					room[row+1][col] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((targetBelowPerson)) {
					
					// Box was on target and a target was behind player
					room[row][col] = SPACE;
					room[row+1][col] = PERSON_ON_TARGET;
					return;

				} else {

					//Box was on target but no target was behind player
					room[row][col] = SPACE;
					room[row+1][col] = PERSON;
					return;

				}

			}

		} else if (directionMoved == 'a') {

			if (personIsOnTarget) { 

				if ((targetRightPerson)) {

					room[row][col] = TARGET;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = TARGET;
					room[row][col+1] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((targetRightPerson)) {

					room[row][col] = SPACE;
					room[row][col+1] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = SPACE;
					room[row][col+1] = PERSON;
					return;

				}

			}
			
		} else if (directionMoved == 's') {

			if (personIsOnTarget) {

				if ((targetAbovePerson)) {

					room[row][col] = TARGET;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = TARGET;
					room[row-1][col] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((targetAbovePerson)) {
					
					room[row][col] = SPACE;
					room[row-1][col] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = SPACE;
					room[row-1][col] = PERSON;
					return;

				}
			}

		} else if (directionMoved == 'd') {

			if (personIsOnTarget) {

				if ((targetLeftPerson)) {

					room[row][col] = TARGET;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = TARGET;
					room[row][col-1] = PERSON;
					return;

				}

			} else if (!(personIsOnTarget)) {

				if ((targetLeftPerson)) {
					
					room[row][col] = SPACE;
					room[row][col-1] = PERSON_ON_TARGET;
					return;

				} else {

					room[row][col] = SPACE;
					room[row][col-1] = PERSON;
					return;

				}
				
			}

		}

	} else {

		return;

	}

}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z')) {
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{

	/*char layout[200] = "11111111111111" // Row 1: walls
					   "10000000000001"
                       "10343422234001"   // Row 2: O@O@**O@*
                       "10334434222001"   // Row 3: OO@@O@***O
                       "10500000000001"    // Row 4: X with spaces
				       "10000000000001"
                       "11111111111111"; Row 5: walls*/
	char layout[200] = "0011111000111005100010032011001002320100111043010000100011000011111000000000000000000000000000000000";
	int room[ROWS][COLS] = {0};
	char allMoves[1000]  = {0};

	printf("A 2024 Academic project\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room)) {
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	
	return 0;
}


