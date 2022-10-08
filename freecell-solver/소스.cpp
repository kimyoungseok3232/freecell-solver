#include <iostream>
#include <chrono>

#define swap(a,b) {int t; t=a; a=b; b=t;}

// black card <= 26

// spade 1~13
int s(int a) {
	return a;
}
// clover 14~26
int c(int a) {
	return a+13;
}
// red card > 26

// heart 27~39 
int h(int a) {
	return a + 26;
}
// diamond 40~52
int d(int a) {
	return a + 39;
}

int board[10][20] = {
	//freecell
	{0,0,0,0},
	//homecell
	{0,0,0,0},
	//stack
	{h(6),s(7),c(8),c(7),c(1),h(7),d(11)},
	{d(2),c(12),h(4),d(8),s(12),s(10),s(5)},
	{d(9),h(2),d(3),s(6),d(4),s(4),c(11)},
	{h(11),c(2),h(13),h(9),s(2),c(3),c(5)},
	{h(10),s(3),d(1),d(6),h(3),d(12)},
	{s(1),s(9),c(10),c(6),c(13),h(1)},
	{s(11),h(12),d(5),c(4),d(13),d(10)},
	{c(9),s(13),h(5),d(7),s(8),h(8)}
};

struct node {
	int board[10][20] = {NULL};
	int depth; // ÀÌµ¿ È½¼ö
	int hscore;// ÈÞ¸®½ºÆ½ ½ºÄÚ¾î
	int fscore;// ÃÑ ½ºÄÚ¾î = ÀÌµ¿ È½¼ö + ÈÞ¸®½ºÆ½ ½ºÄÚ¾î
	node* prev = NULL;
	node* listnext = NULL;
	node* samefend = NULL;
};

struct list {
	node* head = NULL;
}open;

void check_board(int board[10][20]) {
	int checker[53] = { 0 };
	for (int i = 2; i < 10; i++) {
		int j = 0;
		while (board[i][j] != NULL) {
			if (checker[board[i][j]] != 1) {
				checker[board[i][j]] = 1;
			}
			else {
				printf("same card exist.");
				break;
			}
			j++;
		}
	}

	for (int i = 1; i < 53; i++) {
		printf("%d ", checker[i]);
		if (checker[i] = 0) {
			printf("doesn't exist card %d", i);
			return;
		}
	}

	printf("\nevery card exist.\n");
	printf("same card doesn't exist.\n\n");
}

void print_board(int board[10][20]) {
	for (int i = 2; i < 10; i++) {
		int j = 0;
		while (board[i][j] != NULL) {

			if (board[i][j] <= 13)
				printf("¢¼%2d", board[i][j]);
			else if (board[i][j] <= 26)
				printf("¢À%2d", board[i][j]-13);
			else if (board[i][j] <= 39)
				printf("¢¾%2d", board[i][j]-26);
			else
				printf("¡ß%2d", board[i][j]-39);

			j++;
		}
		printf("\n");
	}
}

int h_score(int board[10][20]) {



	return 0;
}

node initnode(int board[10][20]) {
	node init;
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; board[i][j] != NULL; j++) {
			int num = board[i][j];
			init.board[i][j] = num;
		}
	}

	init.depth = 0;
	init.hscore = h_score(init.board);
	init.fscore = 0;

	return init;
}

void main() {
	check_board(board);
	print_board(board);

	node a = initnode(board);

	check_board(a.board);
	print_board(a.board);
}