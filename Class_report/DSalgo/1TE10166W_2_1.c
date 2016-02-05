#include <stdio.h>
#include <time.h>

#define MAX 100

/////////////////メイン関数/////////////////////////////////

int main () {
	int n, i, j, t;
	int s;
	int A[MAX] = {};
	int a[MAX] = {};
	int b[MAX] = {};
	printf("ロッドの長さは？\n");		/*長さを入力*/
	scanf("%d", &n);
	int p[n+1];
	a[n] = n;					/*a[n]はnのレジスタとして利用*/
	int k = sisu(n-1);			/*すべての切り出し方は2^(n-1)ある*/
	printf("長さ１から昇順にロッドの価格を入力\n");
	for (i =0; i < n; i++) {		/*長さごとのロッドの価格	p[]を入力*/
		scanf("%d", &p[i]);
	}
	
	clock_t start,end;
	start = clock();

	for (j =1; j <= k; j++) {
		judge(n,p,A,b);				/*条件判別を行う*/
		if (s < p[n]) {
			s = p[n];
			for (i = 0; i < n; i++) {
				a[i] = b[i];		/*条件適合であれば、暫定の最適解としてa[]に保存*/
			}
		}
		Increment(n-1,A);	/*部分集合を更新する*/
	}
	printf("最適な切り分け方は\n");
	for (i = n-1; i >= 0; i--) {
		if (a[i] != 0) {			/*最適解となる切り出し方を出力*/
			a[n] = a[n] - a[i];
			printf("%d", a[i]);
			if (a[n] != 0) {
				printf(",");
			}			
		}
	}
	printf("\n");
	
	end = clock();
	printf("%.2f秒かかりました\n", (double)(end-start)/1000);

    return 0;
}

/////////////////条件適合判定関数judge//////////////////////////////
void judge(int n, int p[], int A[], int b[]){
	int i;
	int t = 0;
	int j = 0;
	p[n] = 0;
	p[n+1] = 0;
	for (i=0; i < n-1; i++){	/*部分集合の要素はそれぞれカットを行う境界を表す*/
		if (A[i] == 0){	
			t = t + 1;			/*tは切り出すロッドの長さを表す*/
		}
		else if (A[i] == 1){
			p[n] = p[n] + p[t];		/*A[i]=1でi番目の境界でカットを行うとする*/
			b[j] = t + 1;			/*b[]はカットした長さを出力のために格納している*/
			j = j + 1;
			t = 0;
		}
	}
	p[n] = p[n] + p[t];
	b[j] = t + 1;
	j = j + 1;
}

/////////////////２進数の更新関数Increment//////////////////////////
void Increment(int n, int A[]){
	int i = 0;
	while (i<n && A[i]==1) {
		A[i] = 0;			/*２進数を昇順に更新する*/
		i = i + 1;
	}
	if (i <= n-1){
		A[i] = 1;
	}
}

/////////////////2^nを求める関数sisu///////////////////////////////
int sisu(int n){
	int k;				/*部分集合の数を求めることになる*/
	int m = 1;
	for (k=1; k<=n; k++){
		m = m * 2;
	}
	return m;
}

