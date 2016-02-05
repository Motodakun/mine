#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	float user;
	float o100;
	float o50;
	float o10;
} odata_t;

float buy110(float c[], int j[], float n, int ac[], int aj[]) {
	if (rand()%100 < 40) {
		printf("buy juice with 110 yen\n");
		c[0] = c[0] + 1;
		c[2] = c[2] + 1;
		j[0] = j[0] - 1 + aj[0];
		n++;
	}
	else if(rand()%100 < 65) {
		printf("buy juice with 150 yen\n");
		if (c[0] < 4) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 4 + (ac[0]*4);
			c[1] = c[1] + 1;
			c[2] = c[2] + 1;
			j[0] = j[0] - 1 + aj[0];
			n++;
		}
	}
	else if(rand()%100 < 95) {
		printf("buy juice with 200 yen\n");
		if (c[0] < 4 || c[1] < 1) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 4 + (ac[0]*4);
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] + 2;
			j[0] = j[0] - 1 + aj[0];
			n++;
		}
	}
	else {
		printf("buy juice with 500 yen\n");
		if (c[0] < 4 || c[1] < 1 || c[2] < 3) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 4 + (ac[0]*4);
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] - 3 + ac[2];
			j[0] = j[0] - 1 + aj[0];
			n++;
		}
	}
	return n;
}

float buy120(float c[], int j[], float n, int ac[], int aj[]) {
	if (rand()%100 < 35) {
		printf("buy juice with 120 yen\n");
		c[0] = c[0] + 2;
		c[2] = c[2] + 1;
		j[1] = j[1] - 1 + aj[1];
		n++;
	}
	else if(rand()%100 < 65) {
		printf("buy juice with 150 yen\n");
		if (c[0] < 3) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 3 + (ac[0]*3);
			c[1] = c[1] + 1;
			c[2] = c[2] + 1;
			j[1] = j[1] - 1 + aj[1];
			n++;
		}
	}
	else if(rand()%100 < 95) {
		printf("buy juice with 200 yen\n");
		if (c[0] < 3 || c[1] < 1) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 3 + (ac[0]*3);
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] + 2;
			j[1] = j[1] - 1 + aj[1];
			n++;
		}
	}
	else {
		printf("buy juice with 500 yen\n");
		if (c[0] < 3 || c[1] < 1 || c[2] < 3) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[0] = c[0] - 3 + (ac[0]*3);
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] - 3 + ac[2];
			j[1] = j[1] - 1 + aj[1];
			n++;
		}
	}
	return n;		
}

float buy150(float c[], int j[], float n, int ac[], int aj[]) {
	if (rand()%100 < 55) {
		printf("buy juice with 150 yen\n");
		c[1] = c[1] + 1;
		c[2] = c[2] + 1;
		j[2] = j[2] - 1 + aj[2];
		n++;
	}
	else if(rand()%100 < 90) {
		printf("buy juice with 200 yen\n");
		if (c[1] < 1) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] + 2;
			j[2] = j[2] - 1 + aj[2];
			n++;
		}
	}
	else {
		printf("buy juice with 500 yen\n");
		if (c[1] < 1 || c[2] < 3) {
			printf("no change\n");
			c[3] = 1;
		}
		else {
			c[1] = c[1] - 1 + ac[1];
			c[2] = c[2] - 3 + ac[2];
			j[2] = j[2] - 1 + aj[2];
			n++;
		}
	}
	return n;			
}

int main () {
	//初期化
    int i;
	char c1[5];
	char c2[5];
	char c3[5];
	char c4[5];
	char c5[5];
	char c6[5];
	char *endp;
	int repnum;
	int n = 0;
	float number;
	float sumnumber = 0;
	float avgnumber = 0;
	float icoin[4];
	int addcoin[3] = {0};
	float sumcoin[3] = {0};
	float avgcoin[3] = {0};
	int ijuice[3];
	int addjuice[3] = {0};
	float ic[3];
	int ij[3];
	float mincoin[3];
	for (i = 0; i < (sizeof(mincoin)/sizeof(mincoin[0])); i++) {
		mincoin[i]=9999;
	}
	
	odata_t *odata;
	odata = (odata_t *)malloc(sizeof(odata_t)* 100);
	if (odata == NULL) {
		printf("no memory\n");
		exit(0);
	}
	
	srand((unsigned int)time(NULL));
	
	//入力
	printf("How many times do you want to simulate?\n");
	scanf("%d", &repnum);
	printf("\nPlease enter the numer of the change\n10 yen：");
	scanf("%s", c1);
	if (c1[0] == 'i') {
		ic[0] = 10;
		addcoin[0] = 1;
	}
	else {
		ic[0] = strtod(c1, &endp);
//		printf("ic[0] = %f\n", ic[0]);
	}
	
	printf("50 yen：");
	scanf("%s", c2);
	if (c2[0] == 'i') {
		ic[1] = 10;
		addcoin[1] = 1;
	}
	else {
		ic[1] = strtod(c2, &endp);
//		printf("ic[1] = %f\n", ic[1]);
	}
	
	printf("100 yen：");
	scanf("%s", c3);
	if (c3[0] == 'i') {
		ic[2] = 10;
		addcoin[2] = 3;
	}
	else {
		ic[2] = strtod(c3, &endp);
//		printf("ic[2] = %f\n", ic[2]);
	}
	
	
	printf("\nPlease enter the number of the juice \n110 yen juice：");
	scanf("%s", c4);
	if (c4[0] == 'i') {
		ij[0] = 10;
		addjuice[0] = 1;
	}
	else {
		ij[0] = strtod(c4, &endp);
		printf("ij[0] = %d\n", ij[0]);
	}
	
	printf("120 yen juice：");
	scanf("%s", c5);
	if (c5[0] == 'i') {
		ij[1] = 10;
		addjuice[1] = 1;
	}
	else {
		ij[1] = strtod(c5, &endp);
		printf("ij[1] = %d\n", ij[1]);
	}
	
	printf("150 yen juice：");
	scanf("%s", c6);
	if (c6[0] == 'i') {
		ij[2] = 10;
		addjuice[2] = 1;
	}
	else {
		ij[2] = strtod(c6, &endp);
		printf("ij[2] = %d\n", ij[2]);
	}
	
	
	//処理
	for (n = 0; n < repnum; n++) {
		//処理内初期化
		number = 0;
		for (i = 0; i < 3; i++) {
			icoin[i] = ic[i];
			ijuice[i] = ij[i];
		}
		icoin[3] = 0;
		
		//処理開始
		printf("process %d of 100\n", n+1);
		while (1) {
			if (rand()%100 < 40) {
				printf("\nbuy 110 yen juice\n");
				if (ijuice[0] == 0) {
					printf("110 yen juice was sold out!!\n");
					continue;
				}
				number = buy110(icoin, ijuice, number, addcoin, addjuice);
			}
			else if (rand()%100 < 80) {
				printf("\nbuy 120 yen juice\n");
				if (ijuice[1] == 0) {
					printf("120 yen juice was sold out!!\n");
					continue;
				}
				number = buy120(icoin, ijuice, number, addcoin, addjuice);
			}
			else {
				printf("\nbuy 150 yen juice\n");
				if (ijuice[2] == 0) {
					printf("150 yen juice was sold out!!\n");
					continue;
				}
				number = buy150(icoin, ijuice, number, addcoin, addjuice);
			}
			if (ijuice[0] == 0 && ijuice[1] == 0 && ijuice[2] == 0) {
				printf("\nHere, no juice!\n");
				break;
			}
			if (icoin[3] == 1) {
				break;
			}
		}
		sumnumber = sumnumber + number;
		for (i = 0; i < 3; i++) {
			sumcoin[i] = sumcoin[i] + icoin[i];
			if (mincoin[i] > icoin[i]) {
				mincoin[i] = icoin[i];
			}
		}
		odata[n].user = number;
		odata[n].o10 = icoin[0];
		odata[n].o50 = icoin[1];
		odata[n].o100 = icoin[2];
		
		printf("\nthe number of users: %.0f\n", odata[n].user);
		printf("the number of the left change\n10 yen: %.0f\n50 yen: %.0f\n100 yen: %.0f\n", odata[n].o10, odata[n].o50, odata[n].o100);		
	}
	
	//出力部
	if (repnum > 0) {
		avgnumber = sumnumber / repnum;
	}
	if (repnum > 0) {
		for (i = 0; i < (sizeof(avgcoin)/sizeof(avgcoin[0])); i++) {
			avgcoin[i] = sumcoin[i] / repnum;
		}
	}
	printf("With %d simulations,\n", repnum);
	if (addjuice[0]== 0 && addjuice[1] == 0 && addjuice[2] == 0) {
		printf("\nAgainst %d of juice, the average number of users: %.2f\n", ij[0]+ij[1]+ij[2], avgnumber);
	}
	else {
		printf("\nthe average number of users: %.2f\n", avgnumber);
	}
	
	if (addcoin[0] == 0) {
		printf("\nthe average number of the left change\n10 yen: %.2f\n", avgcoin[0]);
	}
	else{
		printf("\nthe average number of the left change\n10 yen: Infinity\n");
	}
	if (addcoin[1] == 0) {
		printf("50 yen: %.2f\n", avgcoin[1]);
	}
	else{
		printf("50 yen: Infinity\n");
	}
	if (addcoin[2] == 0) {
		printf("100 yen: %.2f\n", avgcoin[2]);
	}
	else{
		printf("100 yen: Infinity\n");
	}
	
	if (addcoin[0] == 0) {
		printf("\nthe minimum number of the left change\n10 yen: %.0f\n", mincoin[0]);
	}
	else{
		printf("\nthe minimum number of the left change\n10 yen: Infinity\n");
	}
	if (addcoin[1] == 0) {
		printf("50 yen: %.0f\n", mincoin[1]);
	}
	else{
		printf("50 yen: Infinity\n");
	}
	if (addcoin[2] == 0) {
		printf("100 yen: %.0f\n", mincoin[2]);
	}
	else{
		printf("100 yen: Infinity\n");
	}
}