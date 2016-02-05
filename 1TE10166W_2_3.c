#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main () {
	int i, n, t;
	printf("ロッドの長さは？\n");
	scanf("%d", &n);						/*長さnの入力*/
	
	int p[n+1];
	printf("長さ１から昇順にロッドの価格を入力\n");
	for (i =1; i <= n; i++) {				/*長さごとのロッドの価格p[i]の入力*/
		scanf("%d", &p[i]);
	}
	
	clock_t start,end;
	start = clock();

	printf("ロッドの価格の最大値は\n");	
	t = Memoized_cut_rod(p, n);		/*Top_downのDP関数を呼び出す*/
	printf("%d\n", t);
	
	end = clock();
	printf("%.2f秒かかりました\n", (double)(end-start)/1000);

	
	return 0;
}

int Memoized_cut_rod(int p[],int n) {
	int i, *r;
	r = (int *)malloc(sizeof(int) * n);		/*rのメモリ確保*/
	if (r == NULL)
	 free(r);
	 for(i=0; i<=n; i++){				/*r[]の初期化*/
		r[i] = -1;
	}
	
	return Memoized_cut_rod_aux(p, n, r);	/*Top_downのDP開始*/
}


int Memoized_cut_rod_aux(int p[], int n, int r[]){
	int i, s, q;
	if (r[n] >= 0) {		/*r[n]が更新済みならば値を返す*/
		return r[n];
	}
	if (n == 0) {			/*n=0ならば0を返す*/
		q = 0;
	}
	else {
		q = -1;				/*記憶してるr[i]を利用して再帰的に最適解を求める*/
		for (i = 1; i <= n; i++) {
			s = p[i] + Memoized_cut_rod_aux(p, n-i, r);
			if (q < s) {
				q = s;
			}
		}
	}
	r[n] = q;
	return q;
}




