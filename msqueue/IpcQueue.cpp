
class IpcQueue {

  private:
  MsgQueue *msgQueue;
  const long int MSGID = 1010;
  public:
  IpcQueue(){}
  IpcQueue(char* services){
    msgQueue = new MsgQueue();
    init(services);
  }

  void init(char *services) {
    setInfo(services);
  }

  void setInfo(char* info=NULL, long msgid=1010) {
    msgQueue->push(msgid, info);
  }

  char * getInfo(long msgid=1010) {
    return msgQueue->pop(msgid);
  }

  void processServer() {

  }

};
