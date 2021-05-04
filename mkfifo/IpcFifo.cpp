#include <stdio.h>
#include <string.h>
#include <iostream>
#include "MkFifo.cpp"
using namespace std;

class IpcFifo {

  private:

  MkFifo _mkfifo;

  public:
  // constructor
  IpcFifo(char* fifoName): _mkfifo(fifoName) {
    printf("initializing Ipc Fifo... %s\n", fifoName);
  }

  int sendingMessage(char * fifoName, char *input) {
    _mkfifo.openFifo(fifoName, O_WRONLY);
    _mkfifo.writef(input);
    _mkfifo.closef();
  }

  char* receivingMessage(char * fifoName) {
    _mkfifo.openFifo(fifoName, O_RDONLY);
    _mkfifo.readf();
    _mkfifo.closef();
    return _mkfifo.getBuffer();
  }

};