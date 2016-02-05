#include <stdio.h>
#include <time.h>

#define MAX 100

/////////////メイン関数/////////////////////////////////////
int main () {
    int n, i, b, t, j;
	printf("集合の要素数は？\n");
	scanf("%d", &n);			/*要素数の入力*/
	int S[n+1];					/*S[n]は条件判別に用いる*/
	int A[MAX] = {};			/*A[]は集合Sに対応する２進数の配列*/
	printf("集合の要素は？\n");
	for (i=0; i<n; i++) {
		scanf("%d", &S[i]);			/*集合の要素をすべて入力*/
	}
	printf("判定したい部分和は？\n");
	scanf("%d", &b);				/*判定したい部分和を入力*/
	
	clock_t start, end;			/*時間を計測するのに用いる*/
	start = clock();			/*計測開始*/
	
	int k = sisu(n);			/*kは部分集合S’の数*/
	S[n] =0;
	t = 0;			/*正しく条件判別を行う為にS[n]とtを０に初期化*/
	
	for (j=0; j<k; j++) {			/*部分集合の数kだけ操作を繰り返す*/
		judge(n, A, S, b);			/*judge関数にて条件適合時にS[n]=1*/
	if (S[n]==1) {
		t = 1;			/*t=1とすることで、すべての部分集合を挙げた後に*/
						/*"YES"、"NO"判定を行える*/
		}
		printf(".");	/*printfの”.”で実行時間を稼がないと上のt=1が代入される前に*/
						/*下の条件分岐ifで"else"を評価してしまう。*/
		Increment(n, A);			/*次の部分集合に更新する*/
	}
	if (t==1) {
		printf("YES\n");
	}
	else {
		printf("NO\n");			/*最後に"YES"、"NO"判定が出力される*/
	}
	
	end = clock();			/*計測終了、及び計測結果を出力*/
	printf("%.2f秒かかりました\n", (double)(end-start)/1000);
	
	return 0;
}

/////////////////条件適合判定関数judge//////////////////////////////
int judge(int n, int A[], int S[], int b){
	int k, s;
	S[n] = 0;
	for (k=n-1; k >=0; k--){
		if (A[k]==1){			/*二進数が１の部分のみ評価し、和を求める*/
			s = s + S[k];
		}
		if (s == b){
			S[n] = 1;			/*条件適合ならS[n]=1とする。*/
		}
	}
}

/////////////////２進数の更新関数Increment//////////////////////////
void Increment(int n, int A[]){
		int i = 0;
		while (i<n && A[i]==1) {
			A[i] = 0;			/*２進数を昇順に更新する*/
			i = i + 1;
		}
		if (i<=n-1){
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