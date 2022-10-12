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
	int empty_freecell;
	int empty_cell;
	int last_move = 0;
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
void print_card(int num) {
	
	if (num == 0) {
		printf("%5d", num);
		return;
	}
	if ((num-1) / 13 == 0)
		printf("¢¼");
	else if ((num - 1) / 13 == 1)
		printf("¢À");
	else if ((num - 1) / 13 == 2)
		printf("¢¾");
	else
		printf("¡ß");

	if (num % 13 == 11)
		printf(" J  ");
	else if (num % 13 == 12)
		printf(" Q  ");
	else if (num % 13 == 0)
		printf(" K  ");
	else
		printf("%2d  ", num % 13);

}
void print_board(node no) {

	int count = 52 - no.board[1][0] % 13 - no.board[1][1] % 13 - no.board[1][2] % 13 - no.board[1][3] % 13 + no.empty_freecell - 4;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			print_card(no.board[i][j]);
		}
		printf("    ");
	}
	printf("\n\n");
	for (int j = 0; j < 20; j++) {
		for (int i = 2; i < 10; i++) {

			if (no.board[i][j] == NULL)
				continue;
			int num = no.board[i][j];

			print_card(num);


			count--;
		}
		printf("\n");
		if (count == 0)
			break;
	}
}
int find_top(int board[10][20],int n) {
	if (n < 2)
		return NULL;
	int temp = 0;
	int count = 0;
	for (int j = 19; j >= 0; j--) {
		if (board[n][j] != NULL) {
			if (temp == 0) {
				temp = board[n][j];
				count++;
			}
			else if (temp < 27 && board[n][j]>26 && (temp + 1) % 13 == board[n][j] % 13) {
				count++;
			}
			else if (temp > 26 && board[n][j]<27 && (temp + 1) % 13 == board[n][j] % 13) {
				count++;
			}
			else
				break;
		}
	}
	return count*100+temp;
}
void find_move(node no) {
	int top[8][2];

	for (int i = 0; i < 8; i++) {
		int t = find_top(no.board, i + 2);
		top[i][0] = t % 100;
		top[i][1] = t / 100;
		print_card(top[i][0]);
		printf("%d ", top[i][1]);
	}

	for (int i = 0; i < 8; i++) {

	}
}
int h_score(int board[10][20]) {

	int score = 0;

	score = board[1][0] + board[1][1] - 13 + board[1][2] - 26 + board[1][3] - 39;

	return score;
}

node initnode(int board[10][20]) {
	node init;
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; board[i][j] != NULL; j++) {
			int num = board[i][j];
			init.board[i][j] = num;
		}
	}
	init.empty_freecell = 4;
	init.empty_cell = 0;
	init.depth = 0;
	init.hscore = 0;
	init.fscore = init.depth-init.hscore;

	return init;
}

void setnode(node no) {

}

void main() {


	node a = initnode(board);
	list open;
	open.head = &a;

	check_board(open.head->board);
	print_board(*open.head);

	find_move(*open.head);
}