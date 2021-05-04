#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#define  LENGTH_BUFFER 1024
#define  PERMISSIONS 0666
using namespace std;

class MkFifo {

  private:
  // file descriptor
  int fd;

  char const *FIFO_PATH = "/tmp/";

  char buffer[LENGTH_BUFFER];

  public:
  // constructor

  MkFifo(char* fifoName) {
    char *pathName;
    pathName = (char*)malloc(strlen(FIFO_PATH) + strlen(fifoName));
    strcpy(pathName, FIFO_PATH);
    strcat(pathName, fifoName);
    // creating the fifo
      createFifo(pathName);
    }

  int createFifo(char* pathName) {
    if(mkfifo(pathName, PERMISSIONS) < 0){
        perror("Error: ");
        if(EEXIST) {
          printf("this file exist! \n");
        }
      } else {
        printf("creating fifo %s", pathName);
      }
  }

  int openFifo(char* fifoName, int mode){
    char *pathName;
    pathName = (char*)malloc(strlen(FIFO_PATH) + strlen(fifoName));
    strcpy(pathName, FIFO_PATH);
    strcat(pathName, fifoName);
    fd = open(pathName, mode);
    if( fd == -1){
      perror("Error: ");
      printf("pathName: %s\n", pathName);
      exit(1);
    }
  }

  void writef(char data[LENGTH_BUFFER])  {
      write(fd, data, strlen(data)+1);
    }

  void readf(){
      read(fd, buffer, sizeof(buffer));
    }

    char* getBuffer(){
      return buffer;
    }

  void closef() {
    close(fd);
  }

char* toCharArray(string src){
  char cstr[src.size() + 1];
  return strcpy(cstr, src.c_str());
}

};
