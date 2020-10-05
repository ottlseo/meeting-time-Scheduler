#include "db.h"

int* DBManage(char ** allTimeTable, int C_Num){
	static int array[35]={0, };
	int f=0;
	
	for(int j=0;j<35;j++){
		int num=0;
		for(int i=0;i<C_Num;i++){
			if(allTimeTable[i][j]=='x') num++;
		}
		array[f]=num;
		f++;
	}

	return array;
}
