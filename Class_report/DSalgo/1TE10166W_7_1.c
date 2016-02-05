#include <stdio.h>
#include <stdlib.h>


int *p, *rank;

//////////森を用いた互いに素な集合の為のデータ構造を構築////////////////////////

/////単一節点からなる木を生成
void make_set(int x) {
	p[x] = x;
	rank[x] = 0;
}

/////２つの節点を結合
void Union(int x, int y) {
	link(find_set(x), find_set(y));
}

/////ランクによる合併戦略
void link(int x, int y) {
	if (rank[x] > rank[y]) {
	p[y] = x;
	}else {
		p[x] = y;
		if (rank[x] == rank[y]) {
		rank[y]++;
		}
	}
}

/////経路圧縮戦略を持った経路探査
int find_set(int x) {
	if (x != p[x]) {
		p[x] = find_set(p[x]);
	}
	return p[x];
}

////////////////////////////////////////////////////////////////////////

//////////////////クイックソート/////////////////////////////////////////////

void q_sort(int weight[], int s[], int t[], int left, int right) {
	//leftはソート対象配列の最左要素、rightは最右要素
    int pivot, l_hold, r_hold, sp, tp;	//pivotは比較点、各hold及びsp,tpはレジスタ
    l_hold = left;
    r_hold = right;
    pivot = weight[left];
	sp = s[left];
	tp = t[left];
    while (left < right)
    {
        while ((weight[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            s[left] = s[right];
            t[left] = t[right];
            weight[left] = weight[right];
            left++;
        }
        while ((weight[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            s[right] = s[left];
            t[right] = t[left];
			weight[right] = weight[left];
			right--;
        }
    }
    weight[left] = pivot;
	s[left] = sp;
	t[left] = tp;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        q_sort(weight, s, t, left, pivot-1);
    if (right > pivot)
        q_sort(weight, s, t, pivot+1, right);
}


/////////////////////////////////////////////////////////////////////////

/////メイン関数 
int main() {
	int i, n, m;
	int weight_sum = 0;
	int *weight, *s, *t;
//	int *p, *rank;
	
	//節点と枝の個数を設定する
	printf("節点の個数nは？\n");
	scanf("%d", &n);
	printf("枝の個数mは？\n");
	scanf("%d", &m);
	
	//各配列のメモリ確保
	weight = (int *)malloc(sizeof(int) * m);
	if (weight == NULL) {
		return EXIT_FAILURE;
	}
	s = (int *)malloc(sizeof(int) * m);
	if (s == NULL) {
		return EXIT_FAILURE;
	}	
	t = (int *)malloc(sizeof(int) * m);
	if (t == NULL) {
		return EXIT_FAILURE;
	}
	p = (int *)malloc(sizeof(int) * n);
	if (p == NULL) {
		return EXIT_FAILURE;
	}
	rank = (int *)malloc(sizeof(int) * n);
	if (rank == NULL) {
		return EXIT_FAILURE;
	}	
	//
		
	
	// 重み付きの枝を設定する 
	for (i = 0; i < m; i++) {
		printf("%d個目の枝を定義してください\n", i+1);
		printf("１つ目の節点は？\t");
		scanf("%d", &s[i]);
		if (s[i] < 1 || s[i] > n) {
			printf("存在しない節点です\n\n");
			i--;
			continue;
		}		
		printf("2つ目の節点は？\t");
		scanf("%d", &t[i]);
		if (t[i] < 1 || t[i] > n) {
			printf("存在しない節点です\n\n");
			i--;
			continue;
		}
		printf("枝の重みは？\t");
		scanf("%d", &weight[i]);
	}
	//
	
	//全ての節点に対してmake_setを行う
	for (i = 1; i <= n; i++) {
		make_set(i);
	}
	
	// ソート処理	
	q_sort(weight, s, t, 0, m-1);	 //重さの昇順に枝をソート	

	//ソートされた順に閉路を含まないように木同士を連結する。
	for (i = 0; i < m; i++) {
		//お互いの根が違えば、違う木に属しているので連結を行う
		if ( find_set(s[i]) != find_set(t[i]) ) { 
			Union(s[i], t[i]);
			//重みの合計を更新
			weight_sum = weight_sum + weight[i];
		}
	}
	
	printf("\n重さの合計は\t%d\n", weight_sum);
	
	//メモリの解放
	free(weight);
	free(s);
	free(t);
	free(p);
	return EXIT_SUCCESS;
}
	



