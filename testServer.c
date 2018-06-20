#include "headerFiles.h"
#include "testServer.h"

int main(int argc, char **argv){

    to_Listen();

    to_Create(listen_s);

//    accept_id = pthread_create(&accept_f, NULL, Accept, (void *)&listen_s);

    while(1);







    return 0;
}
