#include <stdio.h>
#include <stdlib.h>


//隣接リストの定義
typedef struct ltag{
	int dest;		//隣接する点
	int weight;		//辺の重み
	struct ltag *next;	//リストの次のノードへのポインタ
} elist;

//グラフの各点の属性を定義
struct {
	int state;		//頂点の走査状態(0:未走査,1:既走査)
	int d;		//始点からの暫定の重み和
	int p;		//先行点
	elist *adj;		//隣接リストへのポインタ
} *V;			


//簡易のmin優先付きキュー
int extract_min(int n) {
	int i;
	int q = -1;
	int a = 1001;
	//全ての点の重みの和に対して、最小であるものを抽出->q
	for (i = 0; i < n; i++) {
		if ( V[i].d < a && V[i].state == 0) {
			a = V[i].d;
			q = i;
		}
	}
	return q;
}
	
	
//隣接リストの新しいノードを作成する
elist *newadj() {
	elist *e;		//ノードへのポインタ
	e = malloc(sizeof (elist));
	if (e == NULL) {
		exit (EXIT_FAILURE);
	}
	return e;
}

//各頂点を初期化する
void initialize_single_source(int s, int n) {
	int i;
	for (i = 0; i < n; i++) {
		V[i].state = 0;		//全て未走査
		V[i].d = 1000;		//非常に大きな重み
		V[i].p = 0;			//先行点はnil
	}
	V[s].d = 0;				//sは始点
}

//緩和を行う(Qはmin優先度付きキューより取り出された)
void relax(int Q) {
	elist *e;	//ノードへのポインタ
	int x;
	//隣接リストに属する全ての点に対して緩和を行う
	for (e = V[Q].adj; e != NULL; e = e->next) {
		x = e->dest;
		if (V[x].d > V[Q].d + e->weight) {
			V[x].d = V[Q].d + e->weight;
			V[x].p = Q;
		}
	}
	//既走査とする
	V[Q].state = 1;
}

//ダイクストラ本体
void dijkstra(int s, int n) {
	initialize_single_source(s, n);		//初期化
	int Q = 0;		//最初は始点(s=0)から走査
	//全ての頂点が既走査ならQ=-1となり終了
	while (Q >= 0) {
		relax(Q);
		Q = extract_min(n);		//キューから値を取り出す
	}
}

//main関数
int main() {
	int i, s, n, m;
	int w, u, v;
	elist *e;	//ノードへのポインタ
	
		//頂点と辺の個数を設定する
	printf("頂点の個数nは？\n");
	scanf("%d", &n);
	printf("辺の個数mは？\n");
	scanf("%d", &m);
	
	//配列のメモリ確保
	V = malloc(sizeof(*V) * n);
	if (V == NULL) {
		return EXIT_FAILURE;
	}
	
	//隣接リストの初期化
	for (i = 0; i < n; i++) {
		V[i].adj = newadj();
	}
	
	//グラフの定義
	for (i = 0; i < m; i++) {
		printf("%d個目の枝を定義してください\n", i+1);
		printf("１つ目の節点は？\t");
		scanf("%d", &u);
		if (u < 0 || u > n-1) {
			printf("存在しない節点です\n\n");
			i--;
			continue;
		}
		printf("2つ目の節点は？\t");
		scanf("%d", &v);
		if (v < 0 || v > n-1) {
			printf("存在しない節点です\n\n");
			i--;
			continue;
		}
		printf("枝の重みは？\t");
		scanf("%d", &w);
		
		//頂点の各属性及び、隣接リストへの値の代入
		e = V[u].adj;
		s = 0;		//sは隣接リストの深み「
	while (  e->next != NULL ) {
		e = e->next;	//NULLの手前まで移動
		s++;
	}		
//	e = newadj();
	//隣接リストの各属性に代入
	e->dest = v;
	e->weight = w;
	e->next = newadj();
		printf("eは%d\n", s);
	}

	s = 0;	//始点sを頂点０とする
	//ダイクストラ開始
	dijkstra(s, n);
	
	//出力
	for (i = 1; i < n; i++) {
		printf("始点から点%dまでの距離は\t%d\n\n", i, V[i].d);
	}
	free(V);
	return EXIT_SUCCESS;
}



