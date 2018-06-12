#include "headerFiles.h"

#define MAXLINE 1024 
#define PORTNUM 50000
#define SOCK_SETSIZE 1021

#define MAX_CLIENT 100

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

    //연결된 소켓 배열
    int list[MAX_CLIENT];
    int clnt_num=0;

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
            list[clnt_num] = client_fd;
            clnt_num++;

            FD_SET(client_fd,&readfds);

            if (client_fd > maxfd)
                maxfd = client_fd;
            printf("Accept OK\n");
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
                }
                else
                {
                    buf[readn] = '\0';
                    if(clnt_num != 1){
                        for(int j=0; j<clnt_num; j++){
                            write(list[j], buf, strlen(buf));
                        }
                    }
                    else write(list[0], buf, strlen(buf));
                    
                    
                }
                if (--fd_num <= 0)
                    break;
            }
        }
    }
}
