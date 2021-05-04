// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct msg_buffer {
    long msg_type;
    char *msg_text;
} message;

class MsgQueue {
    private:
    key_t key;
    int msgid;
    public:
    void push(long msgid, char * msg) {
        message.msg_type = msgid;
        message.msg_text = (char*)malloc(strlen(msg));
        strcpy(message.msg_text, msg);
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    char* pop(long msgid) {
        message.msg_type = msgid;
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        return message.msg_text;
    }

    MsgQueue() {
        // ftok to generate unique key
        key = ftok("uag", 65);
        // msgget creates a message queue
        // and returns identifier
        msgid = msgget(key, 0666 | IPC_CREAT);
    }
};