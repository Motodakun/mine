#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 50
#define SUCCESS 1
#define FAILURE 0

typedef int data_t;

//gueue definition
typedef struct {
	int head;
	int num;
	data_t data[QUEUE_SIZE];
} queue_t;


//enqueue implementation
int enqueue(queue_t *que, data_t enq_data) {
	if (que->num < QUEUE_SIZE) {
		que->data[(que->head + que->num) % QUEUE_SIZE] = enq_data;
		que->num ++;
		printf("キューに追加(que_num : %d)\n", que->num);
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

//dequeue implementation
int dequeue(queue_t *que, data_t *deq_data) {
	//	data_t d;
	if (que->num > 0) {
		*deq_data = que->data[que->head];
		que->head = (que->head + 1) % QUEUE_SIZE;
		que->num --;
		printf("キューから削除(que_num : %d)\n", que->num);
		return SUCCESS;
	}else {
		return FAILURE;
	}
}

int main () {
	//initialization
	int i = 0;
	int *flug;
	int a, r, j, n, k;
	int rp;	//random coming of 1 patient (/min)
	int rt[8];	//random select for Peak Time 
	
	//for Queue
	data_t d;	
	queue_t que;
	que.num = que.head = 0;
	
	//	int np = 8;	//Normal Patients
	//	int pp = 13;	//Patients in the Peak
	//	int ttm = 6;	//Treatment Time (min)
	//	float tth = 0.1;	//Treatment Time (hour)
	//	int bh = 480;	//Business Hour (min)
	int sh = 0;	//Sum Hour (min)
	int *ct;	//Count for Treatment
	
	int nd;	//Number of Doctor
	int pth;	//Peak Time (hour)
	
	int s = 0;	//sum
	double at1 = 0;	//Averege of Treatment Time before enqueue
	double at2 = 0;	//Average of Treatment Time for only enqueue values
	double *at;	//Average of All at1
	double at_sum = 0;
	int max = 0;
	//	double t8 = 21;	//Value for calculating 8 patients at2
	//	double t13 = 36;	//Value for calculating 13 patients at2
	
	srand(time(NULL));
	
	//input
	printf("Insert number of Simulation\n");
	scanf("%d", &n);
	printf("Insert number of Doctor\n");
	scanf("%d", &nd);
	printf("Insert length of Peak Time\n");
	scanf("%d", &pth);
	
	//Setting for at
	at = (double *)malloc(sizeof(double) * n);
	if (at == NULL) {
		printf("No Memory!!\n");
		exit(0);
	}
	
	for (j=0; j < n; j++) {
		at[j] = 0;
	}
	
	//Setting for Treatment Counter as a doctor
	ct = (int *)malloc(sizeof(int) * nd);
	if (ct == NULL) {
		printf("No Memory!!\n");
		exit(0);
	}
	
	
	//Setting for Flug as a Counter
	flug = (int *)malloc(sizeof(int) * nd);
	if (flug == NULL) {
		printf("No Memory!!\n");
		exit(0);
	}
	
	/*	if (pth == 1) {
	 rt = rand() % 7;
	 }*/
	
	//Start Simulation
	for (k = 0; k < n; k++) {
		printf("Simulation NO.%d\n", k+1);
		//Initialization as a Simulation
		//rt[8] = {0};
		for (j=0; j < 8; j++) {
			rt[j] = 0;
		}
		for (j=0; j < nd; j++) {
			ct[j] = 0;
		}
		for (j=0; j < nd; j++) {
			flug[j] = 0;
		}
		que.num = que.head = 0;
		sh = 0;
		s = 0;
		at1 = 0;
		at2 = 0;
		while (i < pth) {
			r = rand() % 8;
			if (rt[r] == 0) {
				printf("%dth hour is Peak\n", r);
				rt[r] = 1;
				i++;
			} else {
				continue;
			}
		}
	
		while (sh < 480) {
			r = sh / 60;
			printf("%d時間経過\n", r);
			i = 0;
			//Peak Time
			if (rt[r] == 1) {
				while (i < 60) {
					//Add count for Treatment time
					for (j=0; j < nd; j++) {
						if (flug[j] == 1) {
							ct[j]++;
						}
						if (ct[j] == 7) {
							flug[j] = 0;
							ct[j] = 0;
						}
					}				
				//				printf("que.num = %d(Peak)\n", que.num);
				//				printf("ct = %d(Peak)\n", ct);
					rp = rand() % 60;
					//Coming 1 Patient (/min)
					if (rp < 13) {
						//at2 = (que.num) * 6 + (6 - ct);
						at2 = (que.num) * 6;
						for (j = 0; j < nd; j++) {
							at2 = at2 + 6 - ct[j];
						}
						at1 = (at1 * s + at2) / (s+1); // new at1
						s = s+1;	//new s
						enqueue(&que, 1);
						if (max < que.num) {
							max = que.num;
						}
					}
					//Coming no Patients (/min)
					else {
					}
					//judgement of Treatment
					for (j=0; j < nd; j++) {
						if (flug[j] == 0) {
							a = dequeue(&que, &d);
							if (a == 1) {
								flug[j] = 1;
							}
						}
					}
					sh++;
					i++;
				}
			}
			//Normal Time
			else {
				while (i < 60) {
					//Add count for Treatment time
					for (j=0; j < nd; j++) {
						if (flug[j] == 1) {
							ct[j]++;
						}
						if (ct[j] == 7) {
							flug[j] = 0;
							ct[j] = 0;
						}
					}
				//				printf("que.num = %d(Normal)\n", que.num);
				//				printf("ct = %d(Normal)\n", ct);
					rp = rand() % 60;
					//Coming 1 Patient (/min)
					if (rp < 8) {
						//at2 = (que.num) * 6 + (6 - ct);
						at2 = (que.num) * 6;
						for (j = 0; j < nd; j++) {
							at2 = at2 + 6 - ct[j];
						}
						at1 = (at1 * s + at2) / (s+1); // new at1
						s = s+1;	//new s
						enqueue(&que, 1);
						if (max < que.num) {
							max = que.num;
						}
					}
					//Coming no Patients (/min)
					else {
					}
					//judgement of Treatment
					for (j=0; j < nd; j++) {
						if (flug[j] == 0) {
							a = dequeue(&que, &d);
							if (a == 1) {
								flug[j] = 1;
							}
						}
					}
					sh++;
					i++;
				}
			}
		}
		at[k] = at1;
		at_sum = at_sum + at[k];
		printf("Average for Waiting Time (k = %d) : %.2f\n", k+1, at[k]);
		printf("Needed Minimum Chairs (k = %d) : %d\n\n", k+1, max);
	}	

	at1 = at_sum / n;
	
	//output
	printf("For %d Simulations\n", n);
	printf("Average for Waiting Time (min) : %.2f\n", at1);
	printf("Needed Minimum Chairs : %d\n", max);
	
	free(ct);
	free(flug);
	free(at);
	return 0;
}

