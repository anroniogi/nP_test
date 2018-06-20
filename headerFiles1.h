//"headerFiles.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>

#define LENGTH 50
//using namespace std;

struct UserData
{
    char name[LENGTH];
    char id[LENGTH];
    char pwd[LENGTH];
};

/*
class UserQueue
{
    private:
        UserData *uQueue;
        int uQsize;
        int ufront;
        int urear;

    public:
        void Init_uQueue(int size)  //큐크기 결졍
        {
            uQsize = size;  //size = 사람 수
            uQueue = (UserData *)malloc(uQsize*sizeof(UserData));   //큐를 사용하기 위한 메모리 할당
            ufront = 0;
            urear = 0;
        }
        void free_uQueue()  //큐 삭제
        {
            free(uQueue);
        }
        bool uInsert(UserData userdata, int socketdescriptor)   //큐내의 데이터 저장
        {
            if((urear + 1)% uQsize == ufront)
            {
                return false;
            }
            uQueue[urear] = userdata;
            urear = (urear + 1) % uQsize;
            return true;
        }
        UserData uDelete() //큐내의 데이터 삭제  todo : return value 체크
        {
            UserData a;
            if (ufront == urear)
            {
                return ;
            }
            a = uQueue[ufront];
            ufront = (ufront +1) %uQsize;
            return a;
        }
};
*/
/*
class MessageQueue
{
    private:
        int *mQueue;
        int mQsize;
        int mfront;
        int mrear;

    public:
        void Init_mQueue(int size)  //큐크기 결졍
        {
            mQsize = size;  //size =
            mQueue = (UserData *)malloc(uQsize*sizeof(UserData));   //큐를 사용하기 위한 메모리 할당
            mfront = 0;
            mrear = 0;
        }
        void free_mQueue()  //큐 삭제
        {
            free(mQueue);
        }
        bool mInsert(UserData userdata, int socketdescriptor)   //큐내의 데이터 저장
        {
            if((mrear + 1)% mQsize == mfront)
            {
                return false;
            }
            mQueue[mrear] = userdata;
            mrear = (mrear + 1) % mQsize;
            return true;
        }
        UserData mDelete() //큐내의 데이터 삭제  todo : return value 체크
        {
            UserData a;
            if (mfront == mrear)
            {
                return ;
            }
            a = mQueue[mfront];
            mfront = (mfront +1) %mQsize;
            return a;
        }
};
*/
/*
class UserMessageQueue
{
    private:
        string *umQueue;
        int umQsize;
        int umfront;
        int umrear;

    public:
        void Init_umQueue(int size)  //큐크기 결졍
        {
            umQsize = size;  //size = 사람 수
            umQueue = (UserData *)malloc(uQsize*sizeof(UserData));   //큐를 사용하기 위한 메모리 할당
            umfront = 0;
            umrear = 0;
        }
        void free_umQueue()  //큐 삭제
        {
            free(umQueue);
        }
        bool umInsert(UserData userdata, int socketdescriptor)   //큐내의 데이터 저장
        {
            if((umrear + 1)% umQsize == umfront)
            {
                return false;
            }
            umQueue[umrear] = userdata;
            umrear = (umrear + 1) % umQsize;
            return true;
        }
        string umDelete() //큐내의 데이터 삭제  todo : return value 체크
        {
            string a;
            if (umfront == umrear)
            {
                return ;
            }
            a = umQueue[umfront];
            umfront = (umfront +1) % umQsize;
            return a;
        }
};*/
