// TCP echo client
#include "headerFiles.h"

#define SIZE 1024

void *t_function(void *data){
    int n;
    int s = *((int *)data);
    char buffer_rcv[SIZE];
    char* ptr_rcv = buffer_rcv;

    while(1){
         n = recv(s, ptr_rcv, SIZE, 0);
         buffer_rcv[n] = '\0';
         buffer_rcv[n+1] = '\n';
         printf("\nEchoed string received: %s \n 보낼 문자열을 입력하세요 :", ptr_rcv);
    }

}

char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = (char*)malloc(len1 + len2 + 1);//+1 for the zero-terminator
                                           //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);//+1 to copy the null-terminator
    return result;
}

int main (int argc, char* argv[])
{
    //
    int s;
    int n;
    char* servName;
    int servPort;
    char* string;
    int len;
    int maxLen;
    int test;
    char buffer[SIZE];
    char* ptr = buffer;
    char buffer_rcv[SIZE];
    char* ptr_rcv = buffer_rcv;
    char* msg;

    struct sockaddr_in servAddr;

    //상규 추가
    pthread_t pthread;
    int thr_id;
    int status;


    if(argc !=4)
    {
        printf("ERROR : three arguments are needed");
        exit(1);
    }
    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];

    string = concat(string, " : ");

    //
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, servName, &servAddr.sin_addr);
    servAddr.sin_port = htons(servPort);
    s = socket(PF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        perror("ERROR : socket creation failed");
        exit(1);
    }
    //
    if(connect(s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("ERROR : connection failed");
        exit(1);
    }
    //상규 추가
    thr_id = pthread_create(&pthread, NULL, t_function, (void *)&s);
    if(thr_id < 0){
        perror("스레드 안생김ㅋ");
        exit(0);
    }
    pthread_detach(pthread);
    printf("보낼 문자열을 입력하세요 : ");

    while(1){
//        printf("보낼 문자열을 입력하세요 : ");
        gets(buffer);
        if(strcmp(ptr, "quit")==0)
            break;

        msg = concat(string, ptr);

        test = send(s, msg, SIZE, 0);
//        n = recv(s, ptr_rcv, SIZE, 0);
//        printf("\nEchoed string received: ");
//        fputs(buffer_rcv, stdout);
//        printf("\n");
//        ptr_rcv = buffer_rcv[0];
    }

//
    //printf("\n");
    close(s);
    //
    exit(0);
}
