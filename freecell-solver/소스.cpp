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
	{d(2),c(12),s(2),d(8),s(12),s(10),s(5)},
	{d(9),h(8),d(3),s(6),d(4),s(4),c(11)},
	{h(11),c(2),h(13),h(9),h(4),c(3),h(3)},
	{h(10),s(3),d(1),d(6),c(5),d(12)},
	{s(1),s(9),c(10),c(6),c(13),h(1)},
	{s(11),h(12),d(5),c(4),d(13),d(10)},
	{c(9),s(13),h(5),d(7),s(8),h(2)}
};

struct node {
	int board[10][20] = {NULL};
	int depth; // �̵� Ƚ��
	int hscore;// �޸���ƽ ���ھ�
	int fscore;// �� ���ھ� = �̵� Ƚ�� + �޸���ƽ ���ھ�
	int empty_freecell;
	int empty_cell;
	int last_move = 0;
	node* prev = NULL;
	node* listnext = NULL;
};

node* samefend[200] = {NULL};

struct list {
	node* head = NULL;
}open;
int max_movable_card(node* no) {
	return (no->empty_freecell + 1) * (no->empty_cell + 1);
}
int h_score(int board[10][20]) {

	int score = 0;

	score = board[1][0] + (board[1][1] - 1) % 13 + 1 + (board[1][2] - 1) % 13 + 1 + (board[1][3] - 1) % 13 + 1;

	return score;
}
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
		printf("  %d   ", num);
		return;
	}
	if ((num-1) / 13 == 0)
		printf("��");
	else if ((num - 1) / 13 == 1)
		printf("��");
	else if ((num - 1) / 13 == 2)
		printf("��");
	else
		printf("��");

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
	printf("\n");
	int count = 52 - no.board[1][0] % 13 - no.board[1][1] % 13 - no.board[1][2] % 13 - no.board[1][3] % 13 + no.empty_freecell - 4;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			print_card(no.board[i][j]);
		}
	}
	printf("\n\n");
	for (int j = 0; j < 20; j++) {
		for (int i = 2; i < 10; i++) {

			int num = no.board[i][j];

			if (no.board[i][j] == NULL)
				printf(" emp  ");
			else
			{
				print_card(num);
				count--;
			}
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
	int height = 0;
	for (int j = 19; j >= 0; j--) {
		if (board[n][j] != NULL) {
			if (temp == 0) {
				temp = board[n][j];
				count++;
				height = j;
			}
			else if (temp < 27 && board[n][j]>26 && (temp + 1) % 13 == board[n][j] % 13) {
				count++;
			}
			else if (temp > 26 && board[n][j]<27 && (temp + 1) % 13 == board[n][j] % 13) {
				count++;
			}
			else {
				break;
			}
		}
	}
	return height*10000+count*100+temp;
}
void putopenlist(node* no) {
	if (open.head->fscore == no->fscore) {
		no->listnext = open.head->listnext;
		open.head->listnext = no;
		if (samefend[open.head->fscore] == open.head) {
			samefend[open.head->fscore] = open.head->listnext;
		}
	}
	else if (open.head->fscore < no->fscore) {
		no->listnext = samefend[open.head->fscore]->listnext;
		samefend[open.head->fscore]->listnext = no;
		if (samefend[no->fscore] == NULL) {
			samefend[no->fscore] = no;
		}
	}
}
node setnode(int board[10][20]) {

	node no;
	int empty_f = 0;
	int empty_c = 0;

	if (board[0][0] == 0)
		empty_f = 4;
	else if (board[0][1] == 0)
		empty_f = 3;
	else if (board[0][2] == 0)
		empty_f = 2;
	else if (board[0][3] == 0)
		empty_f = 1;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			no.board[i][j] = board[i][j];
		}
	}

	for (int i = 2; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (i > 1 && board[i][0] == NULL)
				empty_c++;
			if (board[i][j] == NULL)
				break;
			no.board[i][j] = board[i][j];
		}
	}
	no.empty_freecell = empty_f;
	no.empty_cell = empty_c;
	no.hscore = h_score(no.board);

	return no;
}
node move(node no, int move) {

	node nextno;

	int from = move / 10000;
	int to = move / 100 % 100;
	int howmany = move % 100;
	int from_r = from / 10;
	int from_c = from % 10;
	int to_r = to / 10;
	int to_c = to % 10;

	int nboard[10][20] = { NULL };

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			nboard[i][j] = no.board[i][j];
		}
	}

	for (int i = 0; i < howmany; i++) {
		if (to_r < 2)
			howmany--;
		nboard[to / 10][(to % 10) + howmany - i] = nboard[from / 10][(from % 10) - i];

		if (from / 10 > 2)
			nboard[from / 10][(from % 10) - i] = NULL;
		else
			nboard[from / 10][(from % 10) - i] = 0;

	}

	
	nextno = setnode(nboard);

	nextno.prev = &no;
	nextno.last_move = move;
	nextno.depth = nextno.prev->depth + 1;
	nextno.fscore = nextno.depth - nextno.hscore;

	return nextno;
}
void find_move(node no) {
	int top[8][3];
	printf("\n");
	for (int i = 0; i < 8; i++) {
		int t = find_top(no.board, i + 2);
		top[i][0] = t % 100;
		top[i][1] = t / 100 % 10;
		top[i][2] = t / 10000;
		print_card(top[i][0]);
		printf("%d ", top[i][1]);
		if ((top[i][0] - 1) % 13 == 0) {
			int mo = (i + 2) * 100000 + top[i][2] * 10000 + 1000 + (top[i][0] - 1) / 13 * 100 + 1;
			printf("\n %d \n", mo);
			node *next = new node;
			*next = move(no, mo);
			putopenlist(next);
			return;
		}
		else if ((top[i][0] - 1) % 13 == 1 && (no.board[1][(top[i][0] - 1) / 13]-1) % 13 == 0) {
			int mo = (i + 2) * 100000 + top[i][2] * 10000 + 1000 + (top[i][0] - 1) / 13 * 100 + 1;
			printf("\n %d \n", mo);
			node* next = new node;
			*next = move(no, mo);
			putopenlist(next);
			return;
		}
	}

	printf("\n\n");
	for (int i = 0; i < 8; i++) {
		if (top[i][0] % 13 == (no.board[1][(top[i][0] - 1) / 13] + 1)%13) {
			int mo = (i + 2) * 100000 + top[i][2] * 10000 + 1000 + (top[i][0] - 1) / 13 * 100 + 1;
			print_card(top[i][0]);
			printf("to   homecell\n");
			printf("\n %d \n", mo);
			node* next = new node;
			*next = move(no, mo);
			putopenlist(next);

		}
	}

	if (no.empty_freecell != 0) {
		printf("      to   freecell\n");
		for (int i = 0; i < 8; i++) {
			int mo = (i + 2) * 100000 + top[i][2] * 10000 + 0 + (4-no.empty_freecell)*100 + 1;
			printf("\n %d \n", mo);
			node* next = new node;
			*next = move(no, mo);
			putopenlist(next);
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j == i)
				continue;
			for (int k = 0; k < top[i][1] && k <= max_movable_card(&no); k++) {
				int fc = no.board[i + 2][top[i][2] - k];
				int tc = top[j][0];
				if (((fc > 26 && tc < 27) || (fc < 27 && tc > 26)) && ((fc + 1) % 13 == tc % 13)) {
					int mo = (i + 2) * 100000 + top[i][2] * 10000 + (j + 2) * 1000 + top[j][2] * 100 + k+1;
					printf("\n %d \n", mo);
					node* next = new node;
					*next = move(no, mo);
					putopenlist(next);
					print_card(fc);
					printf("to   ");
					print_card(top[j][0]);
					printf("\n");
				}
			}
		}
		for (int k = 0; k < 4-no.empty_freecell; k++) {
			if ((no.board[0][k] > 26 && top[i][0] < 27) || (no.board[0][k] < 27 && top[i][0]>26) && ((no.board[0][k] + 1) % 13 == top[i][0] % 13)) {
				int mo = 0 * 100000 + k * 10000 + (i + 2) * 1000 + top[i][2] * 100 + 1;
				node* next = new node;
				*next = move(no, mo);
				putopenlist(next);
				print_card(no.board[0][k]);
				printf("to   ");
				print_card(top[i][0]);
				printf("\n");
			}
		}
	}
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
	init.fscore = 0;

	return init;
}
bool finish(node* no) {
	bool finish = false;

	for (int i = 0; i < 4; i++){
		if ((no->board[1][i] - 1) % 13 != 12)
			break;
		if (i == 3)
			finish = true;
	}
	return finish;
}
int main() {


	node a = initnode(board);
	open.head = &a;
	samefend[0] = &a;
	if (finish(open.head))
		printf("finished\n");
	else
		printf("not finished\n");
	check_board(open.head->board);
	print_board(*open.head);

	find_move(*open.head);
	printf("\n");
	//node *b = open.head->listnext;
	if (samefend[open.head->fscore] == open.head) {
		if(open.head->fscore == open.head->listnext->fscore)
			samefend[open.head->fscore] = open.head->listnext;
	}

	open.head = open.head->listnext;
	//check_board(b->board);
	print_board(*open.head);

	find_move(*open.head);

	if (samefend[open.head->fscore] == open.head) {
		if (open.head->fscore == open.head->listnext->fscore)
			samefend[open.head->fscore] = open.head->listnext;
	}

	open.head = open.head->listnext;

	print_board(*open.head);

	find_move(*open.head);

	if (samefend[open.head->fscore] == open.head) {
		if (open.head->fscore == open.head->listnext->fscore)
			samefend[open.head->fscore] = open.head->listnext;
	}

	open.head = open.head->listnext;

	print_board(*open.head);

	find_move(*open.head);

	if (samefend[open.head->fscore] == open.head) {
		if (open.head->fscore == open.head->listnext->fscore)
			samefend[open.head->fscore] = open.head->listnext;
	}

	open.head = open.head->listnext;

	print_board(*open.head);
	//print_board(*open.head->listnext->listnext->listnext->listnext->listnext->listnext->listnext->listnext);

	print_board(*open.head->listnext->listnext);



}