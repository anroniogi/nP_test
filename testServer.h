#include"headerFiles.h"

#define MAXLINE 1024
#define PORTNUM 50000
#define SOCK_SETSIZE 1021

#define MAX_CLIENT 100

pthread_t accept_f;
int accept_id;

pthread_t client_echo[MAX_CLIENT];

pthread_t room1_thread[20];
pthread_t room2_thread[20];
pthread_t room3_thread[20];

typedef struct Arg{
    int room_num;
    int clnt_num;
    int sock_num;
}Args;


UserData user[10];
int UserCount = 0;

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
int room[4][20];
int room1[MAX_CLIENT/5];
int room2[MAX_CLIENT/5];
int room3[MAX_CLIENT/5];


int clnt_num1=0;
int clnt_num2=0;
int clnt_num3=0;


int status = 1;



void to_Listen(){

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNUM);

    if((listen_s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(0);
    }

    if(bind(listen_s, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind error");
        exit(0);
    }
    if(listen(listen_s, 5) == -1)
    {
        perror("listen error");
        exit(0);
    }
}

void echo(int num){
    bool one=true;
    int n;
    int join = 0;
    char name[20];
    char msg[MAXLINE];

    send(client_s[num], "이름을 입력하세요", MAXLINE-1, 0);
    n=recv(client_s[num], name, MAXLINE-1, 0);
    name[n] = '\0';



    while(status){
        if((n=recv(client_s[num], buf, MAXLINE-1, 0))==0){
            printf("client[%d] 접속 종료", num);//채팅방 목록에서도 삭제해야됨
            status=0;
        }else if(join == 0){
            strcat(msg, name);
            strcat(msg, "님이 입장하셨습니다.");

            for(int i=0; i<100; ++i)
                send(client_s[i], msg, MAXLINE-1, 0);

            msg[0]='\0';
            join = 1;
        }
        else{
            buf[n]='\0';
            strcat(msg, name);
            strcat(msg, " : ");
            strcat(msg, buf);
            if(one){
                for(int i=0; i<100; ++i){
                    send(client_s[i], msg, MAXLINE-1, 0);
                }
            }
            one = !one;
            msg[0]='\0';
        }
    }
}

void echo1(int num){
    bool one=true;
    int n;
    int join = 0;
    char name[20];
    char msg[MAXLINE];

    send(room1[num], "이름을 입력하세요", MAXLINE-1, 0);
    n=recv(room1[num], name, MAXLINE-1, 0);
    name[n] = '\0';



    while(status){
        if((n=recv(room1[num], buf, MAXLINE-1, 0))==0){
            printf("client[%d]접속 종료", num);//채팅방 목록에서도 삭제해야됨
            status=0;
        }else if(join == 0){
            strcat(msg, name);
            strcat(msg, "님이 입장하셨습니다.");

            for(int i=0; i<20; ++i)
                send(room1[num], msg, MAXLINE-1, 0);

            msg[0]='\0';
            join = 1;
        }
        else{
            buf[n]='\0';
            strcat(msg, name);
            strcat(msg, " : ");
            strcat(msg, buf);
            if(one){
                for(int i=0; i<20; ++i){
                    send(room1[i], msg, MAXLINE-1, 0);
                }
            }
            one = !one;
            msg[0]='\0';
        }
    }
}

void echo2(int num){
    bool one=true;
    int n;
    int join = 0;
    char name[20];
    char msg[MAXLINE];

    send(room2[num], "이름을 입력하세요", MAXLINE-1, 0);
    n=recv(room2[num], name, MAXLINE-1, 0);
    name[n] = '\0';



    while(status){
        if((n=recv(room2[num], buf, MAXLINE-1, 0))==0){
            printf("client[%d]접속 종료", num);//채팅방 목록에서도 삭제해야됨
            status=0;
        }else if(join == 0){
            strcat(msg, name);
            strcat(msg, "님이 입장하셨습니다.");

            for(int i=0; i<20; ++i)
                send(room2[i], msg, MAXLINE-1, 0);

            msg[0]='\0';
            join = 1;
        }
        else{
            buf[n]='\0';
            strcat(msg, name);
            strcat(msg, " : ");
            strcat(msg, buf);
            if(one){
                for(int i=0; i<20; ++i){
                    send(room2[i], msg, MAXLINE-1, 0);
                }
            }
            one = !one;
            msg[0]='\0';
        }
    }
}
void echo3(int num){
    bool one=true;
    int n;
    int join = 0;
    char name[20];
    char msg[MAXLINE];

    send(room3[num], "이름을 입력하세요", MAXLINE-1, 0);
    n=recv(room3[num], name, MAXLINE-1, 0);
    name[n] = '\0';



    while(status){
        if((n=recv(room3[num], buf, MAXLINE-1, 0))==0){
            printf("client[%d]접속 종료", num);//채팅방 목록에서도 삭제해야됨
            status=0;
        }else if(join == 0){
            strcat(msg, name);
            strcat(msg, "님이 입장하셨습니다.");

            for(int i=0; i<20; ++i)
                send(room3[i], msg, MAXLINE-1, 0);

            msg[0]='\0';
            join = 1;
        }
        else{
            buf[n]='\0';
            strcat(msg, name);
            strcat(msg, " : ");
            strcat(msg, buf);
            if(one){
                for(int i=0; i<20; ++i){
                    send(room3[i], msg, MAXLINE-1, 0);
                }
            }
            one = !one;
            msg[0]='\0';
        }
    }
}




int select_room(int s){
    Args argu;
    int accept_id1;
    int accept_id2;
    int accept_id3;
    int num;
    int check;
    char buf[100];
    int status=1;
    usleep(300);
    while(s != 0){
        check = send(s, "*********************************************", MAXLINE-1, 0);
        sprintf(buf, "채팅방 1 : %d/20 명", clnt_num1);
        usleep(300);
        send(s, buf, MAXLINE-1, 0);
        sprintf(buf, "채팅방 2 : %d/20 명", clnt_num2);
        usleep(300);
        send(s, buf, MAXLINE-1, 0);
        sprintf(buf, "채팅방 3 : %d/20 명", clnt_num3);
        usleep(300);
        send(s, buf, MAXLINE-1, 0);
        usleep(300);
        send(s, "*********************************************", MAXLINE-1, 0);
        usleep(300);
        send(s, "원하는 채팅방 번호를 입력하세요", MAXLINE-1, 0);

        recv(s, buf, MAXLINE-1, 0);
        num = *buf - '0';

        switch (num) {
            case 1:
                /*
                argu.room_num = num;
                argu.clnt_num = clnt_num1;
                argu.sock_num = s;
                */
                //if문으로 20명 넘으면 못들어오게해야됨
                room1[clnt_num1] = s;
                accept_id1 = pthread_create(&room1_thread[clnt_num1], NULL, echo1, clnt_num3);
                pthread_detach(echo1);
                clnt_num1++;
                s=0;
                break;
            case 2:
                /*
                argu.room_num = num;
                argu.clnt_num = clnt_num2;
                argu.sock_num = s;
                */
                room2[clnt_num2] = s;
                accept_id2 = pthread_create(&room2_thread[clnt_num2], NULL, echo2, clnt_num3);
                pthread_detach(echo2);
                clnt_num2++;
                s=0;
                break;
            case 3:
                /*
                argu.room_num = num;
                argu.clnt_num = clnt_num3;
                argu.sock_num = s;
                */
                room3[clnt_num3] = s;
                accept_id3 = pthread_create(&room3_thread[clnt_num3], NULL, echo3, clnt_num3);
                pthread_detach(echo3);
                clnt_num3++;
                s=0;
                break;
            default :
                send(s, "1-3 사이의 숫자만 입력하세요", MAXLINE-1, 0);
                break;
        }
    }
}

void Accept(int num){
    int s;
    int select;
    int Astatus = 1;
    while(Astatus){
        socklen_t addrlen = sizeof(client_addr);

        s = accept(listen_s, (struct sockaddr *)&client_addr, &addrlen);
        /*
        client_s[num] = s;
        printf("accept !");
        send(s, "방을 선택하세요", MAXLINE-1, 0);
        recv(s, buf, MAXLINE-1, 0);
*/
//        login(s);
        //채팅방 선택
        //select = select_room(s);
        select_room(s);

        //아마 이거 안쓸듯?
        //accept_id = pthread_create(&client_echo[num], NULL, echo, num);
        //pthread_detach(client_echo[num]);

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
