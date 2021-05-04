#include <iostream>
#include <string>
#include "IpcFifo.cpp"
#define true 1
#define false 0
using namespace std;

int main() {

  char name[LENGTH_BUFFER];

  printf("Who are you: ");

  fflush(stdout);

  fgets(name, LENGTH_BUFFER, stdin);

  //char *fifoNameServer = (char*)"server";;
  char *fifoName = strtok(name, "\n");

  IpcFifo fifoclient(fifoName);

  char input[LENGTH_BUFFER];

  while(true){

    printf("Message: ");

    fflush(stdout);

    fgets(input, LENGTH_BUFFER, stdin);

    char msg [LENGTH_BUFFER];
    strcpy(msg, fifoName);
    strcat(msg, ":");
    strcat(msg, input);
    printf("message: %s", msg);
    fifoclient.sendingMessage((char*)"server", msg);

    char* message = fifoclient.receivingMessage(fifoName);

    printf("Message from server: %s", message);

  }

 return -1;
}