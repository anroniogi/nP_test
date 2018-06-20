#include"headerFiles.h"

#define MAXLINE 1024
#define PORTNUM 50000
#define SOCK_SETSIZE 1021

#define MAX_CLIENT 100

pthread_t accept_f;
int accept_id;
pthread_t client_echo[MAX_CLIENT];

int listen_s, client_s[100];
socklen_t addrlen;
int fd_num;
int maxfd = 0;
int sockfd;
int readn;
int i= 0;
char buf[MAXLINE];
int num=0;
fd_set readfds, allfds;

struct sockaddr_in server_addr, client_addr;

//연결된 소켓 배열 - 채팅방
//int list[MAX_CLIENT];
int room1[MAX_CLIENT/5];
int room2[MAX_CLIENT/5];
int room3[MAX_CLIENT/5];
int room4[MAX_CLIENT/5];
int room5[MAX_CLIENT/5];

int clnt_num1=0;
int clnt_num2=0;
int clnt_num3=0;
int clnt_num4=0;
int clnt_num5=0;

int status = 1;


void to_Listen(){

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNUM);

    if((listen_s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        return 1;
    }

    if(bind(listen_s, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind error");
        return 1;
    }
    if(listen(listen_s, 5) == -1)
    {
        perror("listen error");
        return 1;
    }
}



void echo(int num){
    while(status){
        int n;
        if((n=recv(client_s[num], buf, MAXLINE-1, 0))==0){
            printf("client[%d] 접속 종료", num);//채팅방 목록에서도 삭제해야됨
        }
        else{
            buf[n]='\0';
            for(int i=0; i<100; ++i){
                send(client_s[i], buf, MAXLINE-1, 0);
        }
        }
    }
}

void Accept(int num){
    int c_n;
    while(status){
        socklen_t addrlen = sizeof(client_addr);

        c_n = accept(listen_s, (struct sockaddr *)&client_addr, &addrlen);
        client_s[num] = c_n;

        accept_id = pthread_create(&client_echo[num], NULL, echo, num);
        pthread_detach(client_echo[num]);

        num++;
    }
}

void to_Create(int listen_s){
        accept_id = pthread_create(&accept_f, NULL, Accept, num);
        pthread_detach(accept_f);

}


//접속종료시 사용자 배열에서 삭제
void Delete(int *ar, int idx)
{
    memmove(ar + idx, ar + idx + 1, strlen(ar) - idx);
}
