#include "clientCheck.h"

void selectDay(int *A){
	int i=0;
	int num;
	int classlist[7] = {7,1,2,3,4,5,6};
	int n=0;
	int j=0;
	for(int i=0;i<35;i++){
		if(A[i]==1){
	
			int d_class = classlist[(i+1)%7];
			if(i<7)
				n=1;
			else if(i<14)
				n=2;
			else if(i<21)
				n=3;
			else if(i<28)
				n=4;
			else
				n=0;
			switch(n){
				case 0: printf("후보 %d : 금요일 %d교시\n", j+1, d_class);
					break;	
				case 1: printf("후보 %d : 월요일 %d교시\n", j+1, d_class);
					break;
				case 2: printf("후보 %d : 화요일 %d교시\n", j+1, d_class);
					break;
				case 3: printf("후보 %d : 수요일 %d교시\n", j+1, d_class);
					break;
				case 4: printf("후보 %d : 목요일 %d교시\n", j+1, d_class);
					break;
			}
		j++;
		}
		
	}

}
