#include <stdio.h>
#include <time.h>
#define MAX 100

/////////////////////メイン関数/////////////////////////////
int main () {
	int n, i, r, s;
	int j = -1;					/*jはリカージョンの深みを表す*/
	int b[MAX] = {};			/*b[]及びl[]は出力のためのトレースに用いる*/
	int l[MAX] = {};
	printf("ロッドの長さは？\n");	/*長さnの入力*/
	scanf("%d", &n);	
	int p[n];
	int a = n;					/*aはリカージョンにおいてnの値が変わってもいいようにnのレジスタとして用いる*/
	printf("長さ１から昇順にロッドの価格を入力\n");
	for (i =0; i < n; i++) {		/*長さごとのロッドの価格p[]を入力*/
		scanf("%d", &p[i]);
	}
	
	clock_t start,end;
	start = clock();

	r = cut_rod(n, p, b, j, l, a);	/*再帰を行う*/
	s = n;
	
	printf("最適な切り分け方は\n");
	for (i = 0; s > 0; i++) {
			s = s - l[i];			/*出力のためにトレースを行っている*/
			printf("%d", l[i]);
		if (s != 0) {
			printf(",");
		}
	}
	printf("\n");
	
	end = clock();
	printf("%.2f秒かかりました\n", (double)(end-start)/1000);

       return 0;
}

/////////////////////リカージョンのロッド切り出し関数///////////////

int cut_rod(int n, int p[], int b[], int j, int l[], int a){
	int i, s, k;
	int q = -1;		/*暫定の最大値を表す*/
	if (n == 0) {
		return 0;	/*nが０になったら、０を返す*/
	}
	j = j + 1;		/*jはリカージョンの深み*/
	
	for (i = 0; i < n; i++) {
		s = p[i] + cut_rod(n-1-i, p, b, j, l, a); /*ここで再帰*/
		if (q < s) {		
			q = s;			/*条件適合ならqを更新*/
			b[j] = i + 1;	/*現在のトレース状況*/
		}
		if (l[a] < q) {		
			l[a] = q;		/*暫定の最適解の出力を行う為のトレース用配列*/
			for (k = j; k < a; k++) {		/*条件適合で更新を行う*/
				l[k] = b[k];
			}
		}
	}
	j = j - 1;
	return q;
}
