#include "headerFiles.h"

#define MAXLINE 1024
#define PORTNUM 50000
#define SOCK_SETSIZE 1021

#define MAX_CLIENT 100

//접속종료시 사용자 배열에서 삭제
void Delete(int *ar, int idx)
{
    memmove(ar + idx, ar + idx + 1, strlen(ar) - idx);
}

int main(int argc, char **argv)
{
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
    int list[MAX_CLIENT];
    //int list2[MAX_CLIENT];
    int clnt_num1=0;
    int clnt_num2=0;

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

    FD_ZERO(&readfds);
    FD_SET(listen_fd, &readfds);

    maxfd = listen_fd;
    while(1)
    {
        allfds = readfds;
        printf("Select Wait %d\n", maxfd);
        fd_num = select(maxfd + 1 , &allfds, (fd_set *)0,
                (fd_set *)0, NULL);

        if (FD_ISSET(listen_fd, &allfds))
        {
            addrlen = sizeof(client_addr);
            client_fd = accept(listen_fd,
                    (struct sockaddr *)&client_addr, &addrlen);

            //상규 추가
            list[clnt_num1] = client_fd;
            clnt_num1++;

            FD_SET(client_fd,&readfds);

            if (client_fd > maxfd)
                maxfd = client_fd;
            printf("Accept OK\n");

            //채팅방 선택
            {
                write(client_fd, "choice_chatting_room_number", 1024);
                read(client_fd, buf, MAXLINE-1);
                printf("%c\n", buf);


            }

            continue;
        }

        for (i = 0; i <= maxfd; i++)
        {
            sockfd = i;
            if (FD_ISSET(sockfd, &allfds))
            {
                if( (readn = read(sockfd, buf, MAXLINE-1)) == 0)
                {
                    printf("close\n");
                    close(sockfd);
                    FD_CLR(sockfd, &readfds);
                    for(int j=0; i<clnt_num1; ++j){
                        if(list[j]==i){
                            Delete(list, j);
                        }
                    }
                    clnt_num1--;
                }
                else
                {
                    buf[readn] = '\0';
                    if(clnt_num1 != 1){
                        for(int j=0; j<clnt_num1; j++){
                            if(i!=list[j]){
                                write(list[j], buf, strlen(buf));
                            }
                        }
                    }
                    else {
                        write(list[0], buf, strlen(buf));
                    }


                }
                if (--fd_num <= 0)
                    break;
            }
        }
    }
}
