// TCP echo client
#include "headerFiles.h"
#include "c.h"


int main (int argc, char* argv[]){


    /********************************
    string = concat(string, " : ");
    보낼 메세지에 사용자 이름 추가해서 보내야됨
    ********************************/

    // login 추가해야함
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //서버로 connect 요구 전송
    connect_to_server();

    //채팅방 선택
  //  choice_room(s);


    //상규 송신대기 스레드 생성
    make_recv_thread(s);
    pthread_detach(pthread);

    while(status){
        send_func(s);
    }

    close(s);
    exit(0);
}
