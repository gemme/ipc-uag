#include <iostream>
#include <string>
#include "IpcFifo.cpp"
#define true 1
#define false 0
using namespace std;

int main() {

 char name[LENGTH_BUFFER];

  printf("Who are you: " );

  fflush(stdout);

  fgets(name, LENGTH_BUFFER, stdin);

  char *fifoName = strtok(name, "\n");

  IpcFifo fifoserver(fifoName);

  char input[LENGTH_BUFFER];

  while(true){

    char *message = fifoserver.receivingMessage(fifoName);

    printf("Message from client: %s \n", message);

    printf("Message: ");

    fflush(stdout);

    fgets(input, LENGTH_BUFFER, stdin);

    char *fromFifo = strtok(message, ":");

    fifoserver.sendingMessage(fromFifo, input);

   }

 return -1;
}