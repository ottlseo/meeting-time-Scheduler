#include "duplicate.h"

struct overlap *ch_duplicate(int* timeTable_Free, int C_Num) {
	int i;
	int* dis;
	static struct overlap{
		int overlapTF;
		int overlapT[35];
	};

	struct overlap *A=malloc(sizeof(struct overlap));	

	dis = (int*)malloc(sizeof(int)*(C_Num+1));

//	if(dis == NULL) {
//		printf("malloc error");
//	}

	for(i = 0; i < 35; i++) {
		dis[timeTable_Free[i]]++;
	}
	
	for(i = 0; i <=C_Num; i++) {
		printf("\n%d명이 되는 시간의 빈도는 %3d입니다.\n", i, dis[i]);
	}

	printf("\n");

	if(dis[0] == 35) {
		printf("가능한 약속 시간이 없습니다.");
	}

	for(int j = C_Num; j > 0; j--) {
		if(dis[j] > 0) {
			if(dis[j] == 1){
				printf("가능한 약속 시간이 하나입니다.");
				A->overlapTF=1;
			
				for(int i=0;i<35;i++){
					if(timeTable_Free[i]==j){
						A->overlapT[0]=i;
					}
				}
			}
			else{ 
				printf("가장 많은 참석 가능 인원 %d명이 모일 수 있는 약속 시간이 %d개 입니다.\n", j, dis[j]);
				A->overlapTF=0;//가능한 약속 시간이 여러 개
				int num=0;
				for(int i=0;i<35;i++){
					if(timeTable_Free[i]==j){
						A->overlapT[num]=i;
						num++;
					}
				}
			}
			break;	
		}	
	}

	free(dis);
	return A;
}
