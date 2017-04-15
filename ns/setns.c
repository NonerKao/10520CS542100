#define _GNU_SOURCE
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<unistd.h>
#include<fcntl.h>

#define N_NS 3

char *ns_substr[N_NS] = {"net", "mnt", "ipc"};
int ns[N_NS] = {CLONE_NEWNET, CLONE_NEWNS, CLONE_NEWIPC};

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("usage: %s <desired namespace>\n", argv[0]);
		printf("\t For example, is the IPC namespace of process 5566 is wanted,\n");
		printf("\t %s /proc/5566/ns/ipc\n", argv[0]);
		return 1;
	}

	int i;
	for(i = 0; i< N_NS; i++){
		if(!strstr(argv[1], ns_substr[i]))
			continue;
		
		if(setns(open(argv[1], O_RDONLY), ns[i])){
			printf("setns fails\n");
			return 1;
		}
		
		printf("enter %s...\n", argv[1]);
		char *arg[] = {"bin/sh", NULL};
		char *env[] = {"PS1=\033[1;33mcontainer $ \033[m", NULL};
		execve("/bin/sh", arg, env);
	}

	printf("None of NET, MNT, or IPC is specified.\n");
	return 0;
}
