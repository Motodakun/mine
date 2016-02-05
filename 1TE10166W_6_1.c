#include <stdio.h>
#include <stdlib.h>

#define MAXt 50
/////ツリーの作成
typedef enum {FALSE, TRUE} boolean;
typedef int key_t;	//キー
typedef int dtn_t;	//データ数
typedef struct node {	//ノードを定義
	dtn_t dtn;
	key_t key[2*MAXt];		//キーは最大2t個
	struct node *branch[2*MAXt+1];	//枝は最大2t+1個
} node_t;

node_t *root = NULL;	//根の初期値
key_t Key;				//操作を行うキー
boolean done, deleted, undersize;	//操作に対して論理型変数を定義	
node_t *newn;		//新しいノード
char *message;		//メッセージ出力用

/////新しいノードの作成
node_t *nodenew(void) {
	node_t *ndptr;		//ノードに対するポインタ	
	ndptr = malloc(sizeof (node_t));	//メモリ確保
	if (ndptr == NULL){
		printf("メモリが不足しています\n");
		exit(EXIT_FAILURE);			//失敗なら強制終了
	}
	return ndptr;		//成功ならノードの先頭アドレスを返す
}
////////////////キーの探索///////////////////////////////////
void search(void){
	node_t *ndptr;
	int i;
	ndptr = root;	//最初はrootから
	while (ndptr !=NULL) {	//ノードが存在しなくなったら終了
		i = 0;
		//キーのデータ数に至る、または探索キーよりも大きくなるノードキーの手前まで移動
		while (i < ndptr->dtn && ndptr->key[i] < Key) {	
			i++;
		}
		//キーが見つかる
		if (i < ndptr->dtn && ndptr->key[i] == Key) {
			message = "見つかりました";
			return;
		}
		//現ノードでキーが見つからない場合、次のノードを探索する。
		ndptr = ndptr->branch[i];
	}
message = "見つかりません";	//すべてのノードで見つからない
}

///////////////////////////////////////////////////////////////////////


///////////キーの挿入////////////////////////////////////////////////////

/////ノードとノードキーを指定して挿入する(分割なし)
void insertitem(node_t *ndptr, int k){
	int i;
	//k以降のノードキーに関して、各要素を１つずつ左にずらしている
	for (i = ndptr->dtn; i >k; i--) {		
		ndptr->key[i] = ndptr->key[i-1];
		ndptr->branch[i+1] = ndptr->branch[i];
	}
	//キーの挿入操作
	ndptr->key[k] = Key;
	ndptr->branch[k+1] = newn;
	ndptr->dtn++;
}

/////ノードとノードキーを指定して挿入する(分割あり)
void split(node_t *ndptr, int k, int t) {
	int i, m;
	node_t *newndptr;	//別のノードへのポインタ
	m = (k <= t)? t : t+1;	//mは分割の中間点、挿入の位置に応じて変える	
	newndptr = nodenew();	//新しいノードの作成
	//新しいノードへのキーと枝の移動
	for (i = m+1; i <= 2*t; i++) {
		newndptr->key[i-m-1] = ndptr->key[i-1];
		newndptr->branch[i-m] = ndptr->branch[i];
	}
	newndptr -> dtn = 2*t-m;	//移動したデータ数
	ndptr->dtn = m;	//残ったデータ数
	//挿入位置に応じたノードに挿入
	if (k <= t) {
		insertitem(ndptr, k);
	}else {
		insertitem(newndptr, k-m);
	}
	//親キーを現ノードの最大要素に書き換える
	Key = ndptr->key[ndptr->dtn-1];
	newndptr->branch[0] = ndptr->branch[ndptr->dtn];
	ndptr->dtn--;
	newn = newndptr;
}

/////木を再帰的にたどって挿入する
void insertsub(node_t *ndptr, int t) {
	int i;
	//ノードが存在しなければ操作なし
	if (ndptr == NULL) {
		done = FALSE;
		newn = NULL;
		return;
	}
	i = 0;
	//挿入キーがノードキーよりも大きくなる直前のノードキーまで移動
while (i < ndptr->dtn && ndptr->key[i] < Key) {
	i++;
}
	//既に登録済み
if (i < ndptr->dtn && ndptr->key[i] == Key) {
	message = "もう登録されています";
	done = TRUE;
	return;
}
	//再帰的に葉ノードまで移動
	insertsub(ndptr->branch[i], t);
	if (done) {		//子ノードで挿入済みなら終了
		return;
	}
	if (ndptr->dtn < 2*t) {	//分割なしの挿入
		insertitem(ndptr, i);
		done = TRUE;
	}else {					//分割ありの挿入
		split(ndptr, i, t);
		done = FALSE;		//親キーに別の挿入を行いたいのでFALSE
		return;
		
	}
}

/////キーの挿入本体
void insert(int t){
	node_t *ndptr;
	message = "登録しました";
	insertsub(root, t);
	if (done) {
		return;
	}
	//FALSEの場合、新たにrootを作り、更新する
	ndptr = nodenew();
	ndptr->dtn = 1;
	ndptr->key[0] = Key;
	ndptr->branch[0] = root;
	ndptr->branch[1] = newn;
	root = ndptr;
}

////////////////////////////////////////////////////////////////////////

////////////////////キーの削除////////////////////////////////////////////

/////ノードとキーを指定して削除する
void removeitem(node_t *ndptr, int k, int t){
	//k番目以降の要素を左にひとつずつずらす
	while (++k < ndptr->dtn) {
		ndptr->key[k-1] = ndptr->key[k];
		ndptr->branch[k] = ndptr->branch[k+1];
	}
	undersize = --(ndptr->dtn) < t;	//データ数を減らし、最小のデータ数を下回っていないか
}										//チェックしている

/////左部分木の最も右の要素を右部分木の最も左に移動する
void moveright(node_t *ndptr, int k){
	int i;
	node_t *left, *right;
	left = ndptr->branch[k-1];		//左部分木
	right = ndptr->branch[k];		//右部分木
	for (i = right->dtn; i > 0; i--) {		//挿入の為に要素を１つずつ右に移動
		right->key[i] = right->key[i-1];
		right->branch[i+1] = right->branch[i];
	}
	right->branch[1] = right->branch[0];
	right->dtn++;
	right->key[0] = ndptr->key[k-1];		//親キーを右部分木へ
	ndptr->key[k-1] = left->key[left->dtn-1];	//左部分木の要素を親キーへ
	right->branch[0] = left->branch[left->dtn];
	left->dtn--;
}

/////右部分木の最も左の要素を左部分木の最も右に移動する
void moveleft(node_t *ndptr, int k){
	int i;
	node_t *left, *right;
	left = ndptr->branch[k-1];
	right = ndptr->branch[k];
	left->dtn++;
	left->key[left->dtn-1] = ndptr->key[k-1];	//親キーを左部分木へ
	left->branch[left->dtn] = right->branch[0];
	ndptr->key[k-1] = right->key[0];			//右部分木の要素を親キーへ
	right->branch[0] = right->branch[1];
	right->dtn--;
	for (i = 1 ; i <= right->dtn; i++) {		//削除の為に要素を１つずつ左へ移動
		right->key[i-1] = right->key[i];
		right->branch[i] = right->branch[i+1];
	}
}

/////隣り合う子ノードのマージ
void combine(node_t *ndptr, int k, int t){
	int i;
	node_t *left, *right;
	right = ndptr->branch[k];
	left = ndptr->branch[k-1];
	//親キーと枝[0]を左部分木に移動
	left->dtn++;
	left->branch[left->dtn] = right->branch[0];
	left->key[left->dtn-1] = ndptr->key[k-1];
	//右部分木の残りの枝とキーを全て左部分木に移動
	for (i = 1; i <= right->dtn; i++) {
		left->dtn++;
		left->key[left->dtn-1] = right->key[i-1];
		left->branch[left->dtn] = right->branch[i];
	}
	removeitem(ndptr, k-1, t);		//ここで親キーの移動が完了
	free(right);	//右部分木消滅
}

/////小さくなりすぎたノードを修復する
void restore(node_t *ndptr, int k, int t){
	undersize = FALSE;
	//最も左の部分木でない場合
	if (k > 0) {
		if (ndptr->branch[k-1]->dtn > t) {
			moveright(ndptr, k);	//左から要素をもらう
		//ノードが小さくなりすぎるならマージを行う。
		}else {		
			combine(ndptr, k, t);
		}
	//最も左の部分木である場合
	}else {
		if (ndptr->branch[1]->dtn > t) {
			moveleft(ndptr, 1);		//右から要素をもらう
		//ノードが小さくなりすぎるならマージを行う
		}else {
			combine(ndptr, 1, t);
		}
	}
}

/////再帰的に木をたどって削除する
void deletesub(node_t *ndptr, int t){
	int i;
	node_t *newndptr;
	//キー未発見なら終了
	if (ndptr == NULL) {
		return;
	}
	i = 0;
	//キーを捜索
	while (i < ndptr->dtn && ndptr->key[i] < Key) {
		i++;
	}
	//現在のノードでキーを発見
	if (i < ndptr->dtn && ndptr->key[i] == Key) {
		deleted = TRUE;
		//ポインタを葉ノードまで移動
		if ((newndptr = ndptr->branch[i+1]) != NULL) {
			while (newndptr->branch[0] != NULL) {
				newndptr = newndptr->branch[0];
			}
			//削除したい親キーの場所に右部分木の葉ノードの最左要素を移動する
			ndptr->key[i] = Key = newndptr->key[0];
			deletesub(ndptr->branch[i+1], t);	//移動した要素を削除する
			if (undersize) {
				restore(ndptr, i+1, t);	//サイズが小さくなりすぎるならマージ
			}
			//葉ノードに達したら削除が行われる
		}else {
			removeitem(ndptr, i, t);
		}
		//現在のノードで見つからない場合
	}else {
		deletesub(ndptr->branch[i], t);
				  if(undersize){
					  restore(ndptr, i, t);
				  }
	}
}

/////キーの削除本体
void delete(int t){
	node_t *ndptr;
	deleted = undersize = FALSE;
	deletesub(root, t);
	//削除成功
	if (deleted) {
		if (root->dtn == 0) {		//ルートがなくなる場合、ルートを更新する
			ndptr = root;
			root = root->branch[0];
			free(ndptr);
		}
		message = "削除しました";
	//削除失敗
	}else {
		message = "見つかりません";
	}
}

////////////////////////////////////////////////////////////////////////

///////////////デモ用のB木表示/////////////////////////////////////////////
void printtree(node_t *ndptr){
	static int depth = 0;
	int i;
	if (ndptr == NULL) {
		printf(".");
		return;
	}
	printf("\t(");
	depth++;
	for (i = 0; i < ndptr->dtn; i++) {
		printtree(ndptr->branch[i]);
		printf("%d", ndptr->key[i]);
	}
	printtree(ndptr->branch[ndptr->dtn]);
	printf(")\t");
	depth--;
}

////////////////////////////////////////////////////////////////////////

/////////////////////main関数////////////////////////////////////////////
#include <ctype.h>
int main(){
	int t = 0;
	printf("最小次数t (t:自然数<=50) ?\n");
	scanf("%d", &t);
	char s[2];
	for (; ;) {
		while (1) {
		printf("挿入In, 検索Sn, 削除Dn, 終了E (n:整数) ?\n");
		if (scanf("%1s%d", s, &Key) == 2 ) {
			break;
		}
			printf("エラー：入力は１つのアルファベットと１つの数字です\n");
		}
		switch (s[0]) {
			case 'I':
			case 'i':
				insert(t);
				break;
			case 'S':
			case 's':
				search();
				break;
			case 'D':
			case 'd':
				delete(t);
				break;
			case 'e':
			case 'E':
				message = "終了します";
				return EXIT_SUCCESS;
			default:
				message = "???";
				break;
		}
		printf("%s\n\n", message);
		printtree(root);
		printf("\n\n");
	}
	return EXIT_SUCCESS;
}



