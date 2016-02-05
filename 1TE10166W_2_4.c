#include <stdio.h>
#include <time.h>


int main () {
	int n, i;
	printf("ロッドの長さは？\n");
	scanf("%d", &n);						/*長さnの入力*/
	int p[n];
	printf("長さ１から昇順にロッドの価格を入力\n");
	for (i =0; i < n; i++) {				/*長さごとのロッドの価格p[i]の入力*/
		scanf("%d", &p[i]);
	}
	
	clock_t start,end;
	start = clock();

	int v;			/*暫定の価格の最大値を表す*/
	int b[n+1];		/*長さiごとの暫定の価値の最大値b[i]を表す*/
	int c[n+1];		/*ロッドの切り方を表示する際のトレースとして用いる*/
	int s, l, m;
	
	for (s = 0; s <= n; s++) {		/*b[]の初期値を設定*/
		b[s] = 0;
	}	
	for (l = 1; l <= n; l++) {		/*Bottom_UpでDPを行う*/
		for (s = l; s <= n; s++) {	/*すなわち長さ１のロッドから考察を進め、b[1]を記憶させる*/
			m = s -l;
			v = b[m] + p[l-1];		/*vは暫定の最大値*/
			if (v > b[s]) {
				b[s] = v;			/*条件判別を行い、必要ならb[s]を更新*/
				c[s] = l;			/*lは行ったカットの絶対値*/
			}
		}
	}
	printf("最適な切り分け方は\n");
	for (s = n; s >= 1; s = s - c[s]) {
		printf("%d,", c[s]);		/*トレースを行い、切り出し方を出力*/
	}
	printf("\n");
	
	end = clock();
	printf("%.2f秒かかりました\n", (double)(end-start)/1000);

   return 0;
}
