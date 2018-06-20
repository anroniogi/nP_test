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
#include<stdbool.h>

#define LENGTH 15
#define uQ_SIZE 10

/*
  func : UserData 구조체 선언
  todo : 구조체 선언 test
*/
typedef struct {
    char name[LENGTH];
    char id[LENGTH];
    char pwd[LENGTH];
} UserData;

/*
    func : UserQueue 선언
    todo : socketdescriptor 확인 및 test
*/
/*
typedef struct {
	UserData uqueue[uQ_SIZE];
	int ufront, urear;
}uQueueType;

uQueueType *createuQueue() {
	uQueueType *uQ;
	uQ = (uQueueType *)malloc(sizeof(uQueueType));
	uQ->ufront = 0;
	uQ->urear = 0;
	return uQ;
}

int is_uQEmpty(uQueueType *uQ) {
	if (uQ->ufront == uQ->urear) {
		printf("\n UserQueue is empty! \n");
		return 1;
	}
	else return 0;
}

int is_uQFull(uQueueType *uQ) {
	if (((uQ->urear + 1) % uQ_SIZE) == uQ->ufront) {
		printf("\n UserQueue is full! \n");
		return 1;
	}
	else return 0;
}

void en_uQueue(uQueueType *uQ, UserData item, int socketdescriptor) {
	if (is_uQFull(uQ))	exit(1);
	else {
		uQ->urear = (uQ->urear + 1) % uQ_SIZE;
		uQ->uqueue[uQ->urear] = item;
	}
}

UserData de_uQueue(uQueueType *uQ) {
	if (is_uQEmpty(uQ))	exit(1);
	else {
		uQ->ufront = (uQ->ufront + 1) % uQ_SIZE;
		return uQ->uqueue[uQ->ufront];
	}
}

void del(uQueueType *uQ) {
	if (is_uQEmpty(uQ))	exit(1);
	else uQ->ufront = (uQ->ufront + 1) % uQ_SIZE;
}

UserData peek(uQueueType *uQ) {
	if (is_uQEmpty(uQ)) exit(1);
	else return uQ->uqueue[(uQ->ufront + 1) % uQ_SIZE];
}

/*
  func : MessageQueue
*/

/*
  func : client가 입력한 id 와 파일내 id Check
  todo : test
*/
/*
bool CheckUserId (char buffer[LENGTH]) {
  int i = 0;
  FILE *fp;
  UserData u[10];
  fp = fopen("user.txt", "r");
  //UserData u[i];
if(fp == NULL)
  return false;

  for(; i<10; i++){
    fread(&u[i], sizeof(UserData), 1, fp);
    if(!strcmp(buffer, u[i].id)){
      return true;
    }
    else return false;
  }
  fclose(fp);
}

/*
  func : client가 입력한 pwd 와 파일내 pwd Check
  todo : test
*//*
bool CheckUserPwd (char buffer[LENGTH]) {
  int i = 0;
  FILE *fp;
  fp = fopen("user.txt", "r");
  //UserData u[i];
  UserData u[10];

  for(; i<10; i++){
    fread(&u[i], sizeof(UserData), 1, fp);
    if(!strcmp(buffer, u[i].pwd)){
      return true;
    }
    else return false;
  }
  fclose(fp);
}

/*

*//*
void SaveUserID (char buffer[LENGTH], UserData* u, int i){
  FILE *fp;
  fp = fopen("user.txt","w");
  fwrite(&u[i].id, sizeof(u[i].id), 1, fp);
  fclose(fp);
}

void SaveUserPwd (char buffer[LENGTH], UserData* u, int i){
  FILE *fp;
  fp = fopen("user.txt","w");
  fwrite(&u[i].pwd, sizeof(u[i].pwd), 1, fp);
  fclose(fp);
}

void SaveUserName (char buffer[LENGTH], UserData* u, int i){
  FILE *fp;
  fp = fopen("user.txt","w");
  fwrite(&u[i].name, sizeof(u[i].name), 1, fp);
  fclose(fp);
}
*/
