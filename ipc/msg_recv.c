#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<sys/errno.h>
#include<errno.h>

#include"msg_helper.h"

int main(int argc,char **argv)
{
	int msgqid, rc;
	struct msg_buf msg;

	msgqid = msgget(5566, MSGPERM|IPC_CREAT|IPC_EXCL);
	if (msgqid < 0) {
		perror(strerror(errno));
		printf("failed to create message queue with msgqid = %d\n", msgqid);
		return 1;
	}

	rc = msgrcv(msgqid, &msg, sizeof(msg.mtext), 0, 0); 
	if (rc < 0) {
		perror( strerror(errno) );
		printf("msgrcv failed, rc=%d\n", rc);
		return 1;
	} 
	printf("Recv: %s\n",msg.mtext);

	rc = msgctl(msgqid, IPC_RMID, NULL);
	if (rc < 0) {
		perror( strerror(errno) );
		printf("msgctl (return queue) failed, rc=%d\n", rc);
		return 1;
	}

	return 0;
}
