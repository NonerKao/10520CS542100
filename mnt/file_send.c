#include <sys/inotify.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc, char *argv[])
{
	int inotifyFd, wd, j;
	char buf[BUF_LEN] __attribute__ ((aligned(8)));
	ssize_t numRead;
	char *p;
	struct inotify_event *event;

	inotifyFd = inotify_init();                 
	if (inotifyFd == -1) {
		perror(strerror(errno));
		printf("inotifyFd\n");
		return 1;
	}

	wd = inotify_add_watch(inotifyFd, getcwd(NULL, 0), IN_DELETE);
	if (wd == -1) {
		perror(strerror(errno));
		printf("inotify_add_watch\n");
		return 1;
	}

	FILE *fp = fopen("message", "w");
	char input[4096], ch;
	while((ch = getchar()) != '\n'){
		fputc(ch, fp);
	}
	fputc('\n', fp);
	fclose(fp);

	while(1) {                                 
		numRead = read(inotifyFd, buf, BUF_LEN);
		if (numRead <= 0) {
			perror(strerror(errno));
			printf("read() from inotify fd returned %d!", numRead);
			return 1;
		}

		for (p = buf; p < buf + numRead; ) {
			event = (struct inotify_event *) p;

			if((event->mask & IN_DELETE) && !strcmp(event->name, "message"))
				goto end;

			p += sizeof(struct inotify_event) + event->len;
		}
	}

end:
	close(inotifyFd);
	close(wd);
	exit(EXIT_SUCCESS);
}
