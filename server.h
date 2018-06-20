#define MAXLINE 1024
#define PORTNUM 50000
#define SOCK_SETSIZE 1021

#define MAX_CLIENT 100

int listen_fd, client_fd;
socklen_t addrlen;
int fd_num;
int maxfd = 0;
int sockfd;
int readn;
int i= 0;
char buf[MAXLINE];
fd_set readfds, allfds;

struct sockaddr_in server_addr, client_addr;

//연결된 소켓 배열 - 채팅방
//int list[MAX_CLIENT];
int room1[MAX_CLIENT];
int room2[MAX_CLIENT];
int room3[MAX_CLIENT];
int room4[MAX_CLIENT];
int room5[MAX_CLIENT];

int clnt_num1=0;
int clnt_num2=0;
int clnt_num3=0;
int clnt_num4=0;
int clnt_num5=0;

void to_Listen(){
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        return 1;
    }
    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNUM);

    if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind error");
        return 1;
    }
    if(listen(listen_fd, 5) == -1)
    {
        perror("listen error");
        return 1;
    }
}




//접속종료시 사용자 배열에서 삭제
void Delete(int *ar, int idx)
{
    memmove(ar + idx, ar + idx + 1, strlen(ar) - idx);
}
