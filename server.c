#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include "strcpy.h"
#include "db.h"
#include "duplicate.h"
#include "setFinalTime.h"

#define MAXBUF 2048
#define MAX 5
#define ALL 1
#define USER 20
#define CLIENT [5]; //접속 가능한 인원 수


char greet[]="접속되었습니다";
char no_greet[]="접속 되지 않았습니다.";

int C_Num=0;//접속자 수
struct message{
	char user[USER];
	char sbuf[MAXBUF];
};


struct add_num{
	int anum;
	char name[MAXBUF];
};

int num1=0;//동적할당 한 번만 하기 위한 변수

//int* timeTable_Free=NULL;

int timeTable_Num=0;//시간표 들어올 떄 인덱스 숫자

char **allTimeTable = NULL;

int client_basefd[5];
int dex=0;

struct overlap{
	int overlapTF;
	int overlapT[35];
};


void writeMessage(void*client_message,void*num,int basefd, int maxfd)
{
	while(num1==0){	
	//	char **allTimeTable=NULL;
		allTimeTable= (char**)malloc(sizeof(char*)*5);
		for(int i=0;i<5;i++){
		allTimeTable[i]=(char*)malloc(sizeof(char)*35);
		}
		
		num1++;
	}
	int index;
	struct message*cl_message;
	struct message*sv_message;
	struct add_num *index_num;
//	char all[]="ALL";

	cl_message=(struct message*)client_message;
	
	index_num=(struct add_num*)num;
	
	
	if(strcmp(cl_message->sbuf,"123")==0)
	{
		printf("등록 하겠습니다[접속자 수%d]\n",++C_Num);
		for(index=0;index<USER;index++)
		{
			if(((index_num+index)->anum)==basefd)
			{
				strcpy((index_num+index)->name,(cl_message->user));
			}
		}
		client_basefd[dex++]=basefd;
		memset(cl_message->sbuf,0,MAXBUF);

		write(basefd,greet,sizeof(greet));
	}

	else
	{
//		printf("시간표");
		char *a=malloc(sizeof(char)*36);
		strcpy(a,cl_message->sbuf);
	//	printf("%s",a);

		for(int i=0;i<35;i++){
			allTimeTable[timeTable_Num][i]=a[i];
		//	printf("%c",allTimeTable[timeTable_Num][i]);
		}
	//	printf("%d\n",timeTable_Num);
		timeTable_Num++;
		printf("\n");
		free(a);					
	}

	struct overlap *duplicate_TT; 
	if(C_Num==timeTable_Num){
		int* timeTable_Free=DBManage(allTimeTable,C_Num);
		char ss[35];
		for(int i=0;i<35;i++){
//			printf("%d",timeTable_Free[i]);
			char s[1];
			sprintf(&ss[i],"%d",timeTable_Free[i]);
		}
//		printf("%s",ss);
//		printf("여긴가\n");
		for(int i=0;i<C_Num;i++){
	
		write(client_basefd[i],ss,sizeof(ss));
		}
	
//		printf("여기니\n");
		duplicate_TT=ch_duplicate(timeTable_Free,C_Num);
//		printf("출력되나여");
	//	printf("\n duplicate_TT %d",duplicate_TT->overlapTF);
		printf("\n");
		int numR;
		int mm[35]={0, };
	//	printf("%d\n",duplicate_TT->overlapT[0]);
	//	for(int i=0;i<35;i++){
//			for(int j=0; j<35; j++){
//				if(duplicate_TT->overlapT[i]==j){
//					mm[j-1]=1;
	//				printf("%d", mm[j]);
//				}
//			}
//			if(duplicate_TT->overlapT[i]==0){
//				numR=i;
//				break;
//			}
	//		printf("%d\n",duplicate_TT->overlapT[i]);
			
	//	}

		if(duplicate_TT->overlapT[0]==0) mm[0]=1;
		for(int i=0;i<35;i++){
			if(duplicate_TT->overlapT[i]!=0){
	//			printf("%d..",duplicate_TT->overlapT[i]);
				mm[duplicate_TT->overlapT[i]]=1;
			}
		}
		
	//	for(int i=0;i<35;i++){
	//		printf("%dㅋㅋㅋ..",mm[i]);
	//	for(int i=0; i<35; i++){
	//		printf("%d",mm[i]);
	//	}
	//	}
		//printf(";ajdfs;;;;;;;;;;;sdkjf;askjdf;kjsdaf");

		char tt[36]={0, };
		
		for(int i=0;i<35;i++){
	//		if(duplicate_TT->overlapT[i])
			sprintf(&tt[i],"%d",mm[i]);
	//		printf("%c",tt[i]);
	//		i++;
//			tt[i]=" ";
		}
	
		char ee[36]={0, };
	
	//	printf("1이냐 0이냐:%d",duplicate_TT->overlapTF);
		if(duplicate_TT->overlapTF==1){
			sprintf(&ee[0],"%d",duplicate_TT->overlapT[0]);//
			for(int i=0; i<C_Num; i++){
				write(client_basefd[i],ee,sizeof(ee));
			//	printf("C넘이랑 i임:%d %d", C_Num, i);
			}
		}		
		else if(duplicate_TT->overlapTF==0){
			for(int j=0;j<C_Num;j++){
				write(client_basefd[j],tt,sizeof(tt));
			}
		
		memset(cl_message->sbuf,0,MAXBUF);
		int re;
		char cc[10]={0, };
	
		int checkcheck[10]={0, };
		for(int i=0; i<C_Num; i++){
			re=read(client_basefd[i],cl_message->sbuf,MAXBUF);
			strcpy(cc, cl_message->sbuf);
		//	printf("happy%s\n", cc);
			re=atoi(cc);
			checkcheck[i]=re;
		}
	//	for(int i=0; i<C_Num; i++)
	//		printf("good%d",checkcheck[i]);

		int voteR=voteResult(checkcheck,C_Num);
		sprintf(&ee[0],"%d",voteR);
		printf("\n");
	//	}

		for(int i=0;i<C_Num;i++){
			write(client_basefd[i],ee,sizeof(ee));
		}
		}
		
		
	}
}


int main(){
	int optval=1;
	int ssock,csock;
	struct sockaddr_in server_addr,client_addr;
	int clen,data_len;
	fd_set read_fds,tmp_fds;
	int fd;
	struct add_num add_num[USER];
	int index,maxfd;
	struct message read_message;

	if((ssock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
	{
		perror("socket error:");
		exit(1);
	}

	setsockopt(ssock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

	memset(add_num,0,sizeof(add_num));
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(30010);

	int ch=bind(ssock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ch<0)
	{
		perror("bind error:");
		exit(1);
	}
	
	ch=listen(ssock,5);
	if(ch<0)
	{
		perror("listen error:");
		exit(1);
	}
	
	clen=sizeof(client_addr);
	
	FD_ZERO(&read_fds);
	FD_SET(ssock,&read_fds);

	maxfd=ssock;

	while(1)
	{
		tmp_fds=read_fds;
		if(select(maxfd+1,&tmp_fds,0,0,(struct timeval*)0)<1)
		{
			perror("select error:");
			exit(1);
		}
		
		for(fd=0;fd<maxfd+1;fd++)
		{
			if(FD_ISSET(fd,&tmp_fds))
			{
				if(fd==ssock)
				{
					if((csock=accept(ssock,(struct sockaddr*)&client_addr,&clen))<0)
					{
						perror("accept error:");
						exit(1);
					}
					FD_SET(csock,&read_fds);
					//printf("새로운 클라이언트 %d번 파일 디스크립터 접속\n",csock);

					for(index=0;index<MAX;index++)
					{
						if(add_num[index].anum==0)
						{
							add_num[index].anum=csock;
							maxfd++;
							break;
						}
					}

					if(csock>maxfd)
					{
						maxfd=csock;
					}
				}
				else
				{
					memset(&read_message,0,sizeof(read_message));
					data_len=read(fd,(struct message*)&read_message,sizeof(read_message));
					if(data_len>0)
					{
						writeMessage((void*)&read_message,(void*)add_num,fd,maxfd);
				//		printf("message from client:%s",(char*)(struct message*)&read_message);
					
					}
					else if(data_len==0)
					{
						for(index=0;index<USER;index++)
						{
							if(add_num[index].anum==fd)
							{
								add_num[index].anum=0;
								strcpy(add_num[index].name,"");
								break;
							}

						}
						close(fd);
						FD_CLR(fd,&read_fds);
						if(maxfd==fd) maxfd--;
						printf("클라이언트 해체\n");
					}
					else if(data_len<0)
					{
						perror("read error:");
						exit(1);
					}
				}
			}
		}
	}
	return 0;
}
