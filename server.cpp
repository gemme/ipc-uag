#include <iostream>
#include <string>
#include <stdlib.h>
#include "./mkfifo/IpcFifo.cpp"
#include "./service/ServiceFactory.cpp"
#include "./msqueue/MsgQueue.cpp"
#include "./msqueue/IpcQueue.cpp"
#include <unistd.h>
#define true 1
#define false 0
#define SSOCIAL 10
#define SPROFESSIONAL 20
using namespace std;

int main() {

  /* PIPE BEGGINING */
  int pipe_parent[2];
  int pipe_child[2];
  char *pipe_message;
  if(pipe(pipe_parent) < 0){
    perror("Error pipe_parent: ");
  }
  if(pipe(pipe_child) < 0){
    perror("Error pipe_child: ");
  }
  int pid = fork();
  if(pid < 0){
    perror("Error on fork process: ");
  }
  /*PIPE END */

  if(pid){

    char name[LENGTH_BUFFER];

    printf("Who are you: " );

    fflush(stdout);

    fgets(name, LENGTH_BUFFER, stdin);

    char *fifoName = strtok(name, "\n");

    IpcFifo fifoserver(fifoName);

    char input[LENGTH_BUFFER];
    char menu[LENGTH_BUFFER];
    int opc = -1;

    strcpy(menu, "\nMENU: \n");
    strcat(menu, "1.- Social service: \n");
    strcat(menu, "2.- Professional practices: \n");
    strcat(menu, "Opcion: \n");

    while(true){

      char *message = fifoserver.receivingMessage(fifoName);

      printf("Message from client: %s \n", message);

      char *token = strtok(message, ":");
      char *whom;
      char *msg;
      whom = token;
      token = strtok(NULL,":");
      msg = token;

      opc = atoi(msg);

      /* printf("whom \n: %s", whom);
      printf("\nmsg \n: %s", msg);
      printf("\nopc \n: %i", opc); */
        switch(opc){
          case 1: {
            printf("Opcion 1 \n");
            write(pipe_child[1], "GET \n", LENGTH_BUFFER);
            char parent_message[LENGTH_BUFFER];
            int nbytes;
            while ((nbytes = read(pipe_parent[0], parent_message, LENGTH_BUFFER)) > 0){
              printf("%s\n", parent_message);
              fifoserver.sendingMessage(whom, parent_message);
              break;
            }
          }
          break;
          case 2: {
            printf("Opcion 2 \n");
            ServiceFactory *factory = new ServiceFactory(SPROFESSIONAL);
            Service *service = factory->getServiceInstance();
            char * professionalServices = service->getServices();
            const long int MSGID_SERVER = 1010;
            const long int MSGID_CLIENT = 0101;
            IpcQueue *ipcQueueServer = new IpcQueue();
            IpcQueue *ipcQueueClient = new IpcQueue();
            ipcQueueClient->setInfo(professionalServices, MSGID_CLIENT);
            char* info = ipcQueueServer->getInfo(MSGID_SERVER);
            printf("info: %s \n", info);
            fifoserver.sendingMessage(whom, info);
          }
          break;
          default:
            fifoserver.sendingMessage(whom, menu);
          break;
        }
    }
  }else {
    printf("child process \n");
    printf("I am a child \n");
    char child_message[LENGTH_BUFFER];
    int nbytes;
    ServiceFactory *factory = new ServiceFactory(SSOCIAL);
    Service *service = factory->getServiceInstance();
    //SocialService social_service;
    while ((nbytes = read(pipe_child[0], child_message, LENGTH_BUFFER)) > 0){
          printf("%s\n", child_message);
          if(child_message) {
            printf(" writing... to parent process through pipes %s \n", service->getServices());
            // printf("%s \n", );
            write(pipe_parent[1], service->getServices(), LENGTH_BUFFER);
          }
      // if (nbytes != 0)
    }
  }

 return -1;
}