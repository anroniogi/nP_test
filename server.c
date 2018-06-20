#include "headerFiles.h"
#include "server.h"


int main(int argc, char **argv)
{

    to_Listen();

    FD_ZERO(&readfds);
    FD_SET(listen_fd, &readfds);

    maxfd = listen_fd;
    while(1)
    {
        allfds = readfds;
        printf("Select Wait %d\n", maxfd);
        fd_num = select(maxfd + 1 , &allfds, (fd_set *)0,
                (fd_set *)0, NULL);

        //연결
        if (FD_ISSET(listen_fd, &allfds))
        {
            addrlen = sizeof(client_addr);
            client_fd = accept(listen_fd,
                    (struct sockaddr *)&client_addr, &addrlen);



            FD_SET(client_fd,&readfds);

            if (client_fd > maxfd)
                maxfd = client_fd;
            printf("Accept OK\n");

            //채팅방 선택
            {
                write(client_fd, "choice_chatting_room_number", 1024);
                read(client_fd, buf, MAXLINE-1);
                printf("%c\n", buf);



                //상규 추가
                list[clnt_num1] = client_fd;
                clnt_num1++;
            }

            continue;
        }

        for (i = 0; i <= maxfd; i++)
        {
            sockfd = i;
            if (FD_ISSET(sockfd, &allfds))
            {
                if( (readn = read(sockfd, buf, MAXLINE-1)) == 0){
                    //채팅방 나가기
                    printf("close\n");
                    close(sockfd);
                    FD_CLR(sockfd, &readfds);
                    for(int j=0; i<clnt_num1; ++j){
                        if(list[j]==i){
                            //채팅방 리스트에서 삭제
                            Delete(list, j);
                        }
                    }
                    //채팅방 인원수에서 삭제
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
