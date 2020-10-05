#include <stdio.h>
#include "setFinalTime.h"

int voteResult(int Arr[], int C_Num){
//	C_Num = 5;

	int freq[35] = {0, };
	for (int i=0; i<C_Num; i++){
		int index = Arr[i];
		freq[index-1]++;
}
	printf("투표 결과\n");

	for (int j=1; j<=C_Num; j++){
		printf("%3d\t번 %3d\n", j,freq[j-1]);
}
	int max = freq[0];
	int max_index =1;

	for (int i=0; i<C_Num; i++){
		if(max < freq[i]){
			max = freq[i];
			max_index = i+1;
}
}
	printf("최종 약속 시간: %d\n", max_index);
	return max_index;
}
