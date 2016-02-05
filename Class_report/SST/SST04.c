#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 10000000

//スタック定義
typedef struct {
	int idno;
	int data;
}_stack;

//グラフ定義
typedef struct {
	int m[9];
	int open;
	int deg;
} graph_t;


_stack stack[STACK_MAX];

int spt = -1;

//隣接リスト定義
int adjacent[9][5] = {
	1, 3, -1, -1, -1,
	0, 2, 4, -1, -1,
	1, 5, -1, -1, -1,
	0, 4, 6, -1, -1,
	1, 3, 5, 7, -1,
	2, 4, 8, -1, -1,
	3, 7, -1, -1, -1,
	4, 6, 8, -1, -1,
	5, 7, -1, -1, -1,
};

//push関数
int push(int no, int dt) {
	if(spt >= STACK_MAX -1 ) {
		printf("Stack overflow!!\n");
		return -1;
	}
	spt++;
	stack[spt].idno = no;
	stack[spt].data = dt;
	printf("Push %d into stack\n", stack[spt].data);
	return 0;
}

//pop関数
int pop(int *no, int *dt) {
	if( spt < 0) {
		printf("stack underflow!!\n");
		return -1;
	}
	*no = stack[spt].idno;
	*dt = stack[spt].data;
	spt--;
	printf("Pop %d from stack\n", *dt);
	return *dt;
}


int main (int argc, const char * argv[]) {
	int no = 0;
	int d = 0;
	int a, s, t, p, i, x;
	//入力
	graph_t graph;
    graph.m[0] = 1;
    graph.m[1] = 4;
    graph.m[2] = 6;
    graph.m[3] = 8;
    graph.m[4] = 2;
    graph.m[5] = 3;
    graph.m[6] = 7;
    graph.m[7] = 5;
    graph.m[8] = 9;
	graph.open = 8;
	graph.deg = 1000;
	
	for (i = 0; i < 5 && adjacent[graph.open][i] != -1; i++) {
		push(no, adjacent[graph.open][i]);
		no++;
	}
		
	while (1) {
		x = pop(&s, &t);
		if (x == -1) {
			break;
		}
		no--;
		d++;
		a = graph.m[graph.open];
		graph.m[graph.open] = graph.m[x];
		graph.m[x] = a;
		p = graph.open;
		graph.open = x;
		for (i = 0; i < 9; i++) {
			if (graph.m[i] != i + 1) {
				a = -1;
				break;
			}
		}
		if (a >= 0) {
			if (graph.deg > d) {
				graph.deg = d;
				printf("This moving : %dn", d);
			}
			d--;
			a = graph.m[graph.open];
			graph.m[graph.open] = graph.m[p];
			graph.m[p] = a;
			graph.open = p;
		}
		else {
			for (i = 0; i < 5 && adjacent[graph.open][i] != -1; i++) {
				if (adjacent[graph.open][i] == x) {
					continue;
				}
				p = push(no, adjacent[graph.open][i]);
				no++;
			}
			if (p == -1) {
				printf("No memory\n");
				break;
			}
		}
	}
	
	//出力
	printf("Minimum moving : %d\n", graph.deg);
	
    return 0;
}
