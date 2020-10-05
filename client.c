#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "strcpy.h"
#include <stdint.h>
#include "clientCheck.h"

#define MAXBUF 2048
#define USER 20

struct message{
	char user[USER];
	char sbuf[MAXBUF];
};

int main(){
	
	char classes[7][8]={"class1","class2","class3","class4","class5","class6","class7"};
	
	char weekdays[5][4]={"Mon","Tue","Wed","Thu","Fri"};
	char schedule[7][5];
	int i_array[7][5];
	char check;

	char ch_array[35];	

	char gg[35];//겹공강 분석 시간표
	int ssock;
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF], pre[MAXBUF];
	fd_set read_fds, tmp_fds;
	int fd;
	char name[20];
	struct message write_message;
	int re;

	if((ssock = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("socket error: ");
		exit(1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("203.255.176.225");
	server_addr.sin_port = htons(30010);

	clen = sizeof(server_addr);

	printf("사용자를 입력하시오: ");
	fgets(name, MAXBUF, stdin);
	
	
//	*(name+(strlen(name)-1))='\0';
	
	if(connect(ssock,(struct sockaddr *)&server_addr, clen)<0){
		perror("connect error: ");
		return -1;
	}
	memset(&write_message, 0, sizeof(write_message));
	strcpy(write_message.user, name);
	strcpy(write_message.sbuf, "123");
	if(write(ssock, (struct message*)&write_message, sizeof(write_message))<0){
		perror("write error: ");
		exit(1);
	}
	
	FD_ZERO(&read_fds);
	FD_SET(ssock, &read_fds);
	FD_SET(0, &read_fds);

	fd = ssock;

	while(1){
		tmp_fds = read_fds;

		if(select(fd+1, &tmp_fds, 0,0,0)<0){
			perror("select error: ");
			exit(1);
		}
		if(FD_ISSET(ssock, &tmp_fds)){
			memset(buf, 0, MAXBUF);
			re = read(ssock, buf, MAXBUF);
			if(re<0){
				perror("read error: ");
				exit(1);
			}
			else if(re==0){
				printf("서버와의 접속이 끊겼습니다.");
				break;
			}
			printf("%s\n", buf);
			memset(buf,0,MAXBUF);
		}
		else if(FD_ISSET(0, &tmp_fds)){
			memset(&write_message, 0, sizeof(write_message));
			memset(buf, 0, MAXBUF);


		//	fgets(write_message.user, USER, stdin);
		//	*(write_message.user+(strlen(write_message.user)-1))='\0';
			printf("자신의 시간표를 입력해주세요: \n");
			printf("해당 시간에 수업이 있으면 o(소문자) 입력\n");
			printf("해당 시간에 수업이 없으면 x(소문자) 입력\n\n");
	//		printf("%s %s 수업 여부:",weekdays[0],classes[0]);

			for(int i=0;i<5;i++)
			{
				for(int j=0;j<7;j++)
				{
					while(1)
					{
						scanf("%c",&check);
						schedule[j][i]=check;
						if(check=='o') i_array[j][i]=0;
						if(check=='x') i_array[j][i]=1;

						if(check=='o'||check=='x') break;
						else printf("%s %s 수업 여부: ",weekdays[i],classes[j]);
					}
				}
				printf("\n");
			}

			printf("       ");

			for(int j=0;j<7;j++)
			{
				printf("%s",classes[j]);
				printf("  ");
			}
			printf("\n");



			for(int i=0;i<5;i++)
			{
				printf("%s\t",weekdays[i]);
				for(int j=0;j<7;j++)
				{
					printf("%c\t",schedule[j][i]);
				}
				printf("\n");
			}
			int k=0;
			for(int i=0;i<5;i++){
				for(int j=0;j<7;j++){
					ch_array[k]=schedule[j][i];
					k++;
				}
			}

			
		//	fgets(buf, MAXBUF, stdin);
		//	*(buf + (strlen(buf)-1))='\0';
		//	write(ssock,(struct message*)&write_message,sizeof(write_message));
		//	char (*timetable)[7][5]=schedule[7][5];
		//	memset(buf,0,MAXBUF);
			strcpy(write_message.sbuf,(ch_array+'\0'));
			if(write(ssock,(struct message*)&write_message,sizeof(write_message))<0){
				perror("write error");
				exit(1);
			}
		//	memset(&write_message,0,sizeof(write_message));
		//	strcpy(write_message.sbuf,"timetable input finish")
		//	if(write(ssock,(struct message*)&write_message,sizeof(write_message))<0){
		//		perror("write error");
		//		exit(1);
		//	}

//			write(ssock,(struct message*)&write_message.sbuf,sizeof(write_message.sbuf));
//
//			if(write(ssock, (struct message*)&write_message, sizeof(write_message))<0){
//				perror("write error: ");
//				exit(1);
//
//			}
			
			re=read(ssock,buf,MAXBUF);
			printf("\n아래는 분석한 겹공강 시간표입니다.\n");
				
			strcpy(gg,buf);
			printf("\t");
			for(int i=0;i<7;i++){
				printf("%s",classes[i]);
				printf("  ");
			}
			printf("\n");
			int mnm=0;
			for(int j=0;j<5;j++){
				printf("%s\t",weekdays[j]);
				for(int i=0;i<7;i++){
					printf("%c\t",gg[mnm++]);
				}
				printf("\n");
			}

		
			char dd[50];
			char aa[36]={0, };
	//		memset(buf,0,MAXBUF);
			int ccc[35]={0, };
		//	re=read(ssock,buf,MAXBUF);
			///	strcpy(dd,buf);
			memset(buf,0,MAXBUF);
		//	char num[10];
		//	printf("%s\n",dd);
		//	if(dd=="1"){
		//		re=read(ssock,buf,MAXBUF);
		//		strcpy(aa,buf);
	//			memset(buf,0,MAXBUF);
		//		ccc[0]=aa[0]-'0';
		//		selectDay(ccc);
				
		//	}
			
		//	else if(dd=="0"){
				re=read(ssock,buf,MAXBUF);
				strcpy(aa,buf);
		//		printf("%s",aa);
	//			memset(buf,0,MAXBUF);
			//	ccc=atoi(aa);
				for(int k=0;k<35;k++){
		//	printf("%c",aa[k]);
			//	char* AAA;
			//	AAA=aa;	
					ccc[k]=(int)(aa[k])-48;
			//	for(int k=0; k<35; k++)
		//			printf("%d",ccc[k]);
				}
			
				if(strlen(aa)==1){
					int classList[7]={7,1,2,3,4,5,6};
					int ii=ccc[0];
					int n = 0;
					if(ii<7) n=1;
					else if(ii<14) n=2;
					else if(ii<21) n=3;
					else if(ii<28) n=4;
					int ff = classList[(ii+1)%7];
					printf("\n");
					switch(n){
						case 0: printf("확정된 최종 약속 시간은 금요일 %d교시입니다.\n",ff);break;
						case 1: printf("확정된 최종 약속 시간은 월요일 %d교시입니다.\n",ff);break;
						case 2: printf("확정된 최종 약속 시간은 화요일 %d교시입니다.\n",ff);break;
						case 3: printf("확정된 최종 약속 시간은 수요일 %d교시입니다.\n",ff);break;
						case 4: printf("확정된 최종 약속 시간은 목요일 %d교시입니다.\n",ff);break;
					}
				}		
				else{
				printf("\n아래는 약속시간을 정하기 위한, 겹공강 후보 입니다.\n");
				selectDay(ccc);
				char num[10];
				printf("투표를 시작합니다.(후보 하나만 입력해주세요)\n");
		//		printf("111\n");
				scanf("%s",num);
		//		printf("22222\n");	
		//		printf("afjsdkfja;sdf");
				printf("선택하신 번호는 %s입니다.\n",num);
		//		printf("ddddddddddd");
				
	//	}
				memset(buf,0,MAXBUF);
				strcpy(buf,num);
				write(ssock, buf, sizeof(buf));
		//		printf("happy~~~~~");

				char ee[1];
				memset(buf,0,MAXBUF);
				re=read(ssock,buf,MAXBUF);
				strcpy(ee,buf);
				int q=atoi(ee);
				
		//		printf("%d",q);
				int chchch=0;
				int ii=0;
				for(int i=0;i<35;i++){
					if(ccc[i]==1) chchch++;
					if(chchch==q){
					 ii=i;
					 break;
					}
				}

				int classList[7] = {7,1,2,3,4,5,6};
				int n=0;
				if(ii<7) n=1;
				else if(ii<14) n=2;
				else if(ii<21) n=3;
				else if(ii<28) n=4;
				int ff = classList[(ii+1)%7];
				switch(n){
					case 0: printf("확정된 최종 약속 시간은 금요일 %d교시입니다.\n",ff);break;
					case 1: printf("확정된 최종 약속 시간은 월요일 %d교시입니다.\n",ff);break;
					case 2: printf("확정된 최종 약속 시간은 화요일 %d교시입니다.\n",ff);break;
					case 3: printf("확정된 최종 약속 시간은 수요일 %d교시입니다.\n",ff);break;
					case 4: printf("확정된 최종 약속 시간은 목요일 %d교시입니다.\n",ff);break;
				}
				}
			break;
		}
		
	//	printf("시간표 전송 끝남");
	}

	close(ssock);
	return 0;
}
