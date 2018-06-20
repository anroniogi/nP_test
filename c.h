#define SIZE 1024

int s;
int n;
char* servName = "127.0.0.1";
int servPort = 50000;
char* string;
int len;
int maxLen;
int test;
char buffer[SIZE];
char* ptr = buffer;
char buffer_rcv[SIZE];
char* ptr_rcv = buffer_rcv;
char* msg;
int status=1;

struct sockaddr_in servAddr;

//상규 추가
pthread_t pthread;
int thr_id;
int status;


char* concat(const char *s1, const char *s2){
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = (char*)malloc(len1 + len2 + 1);//+1 for the zero-terminator
                                           //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);//+1 to copy the null-terminator
    return result;
}

void connect_to_server(){
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
}



void *t_function(void *data){
    int n;
    int s = *((int *)data);
    char buffer_rcv[SIZE];
    char* ptr_rcv = buffer_rcv;

    while(status){
         n = recv(s, ptr_rcv, SIZE, 0);
         buffer_rcv[n] = '\0';
         buffer_rcv[n+1] = '\n';
         printf("\n%s \n", ptr_rcv);
    }
}

void choice_room(int s){
    int n;
    char buffer_rcv[SIZE];
    char* ptr_rcv = buffer_rcv;

    printf("입장할 채팅방을 선택하세요\n");

    n = recv(s, ptr_rcv, SIZE, 0);
    buffer_rcv[n] = '\0';

    printf("%s\n", buffer_rcv);


}

void make_recv_thread(s){
    thr_id = pthread_create(&pthread, NULL, t_function, (void *)&s);
    if(thr_id < 0){
        perror("스레드 안생김ㅋ");
        exit(0);
    }
}

void send_func(int s){
        printf("보낼 문자열을 입력하세요 : ");
        gets(buffer);
        if(strcmp(ptr, "quit")==0)
            status=0;

        //사용자 이름 받아와야함
        //msg = concat(string, ptr);

        //test = send(s, msg, SIZE, 0);
        test = send(s, ptr, SIZE, 0);
}
