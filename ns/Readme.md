### Checking namespaces

Assume that a container is executing, you may check its namespaces inside of it by the following command
(Note that the actual number you get may differ from this example):
```
/ # ls -al /proc/self/ns/
total 0
dr-x--x--x    2 root     root             0 Apr 15 02:28 .
dr-xr-xr-x    8 root     root             0 Apr 15 02:28 ..
lrwxrwxrwx    1 root     root             0 Apr 15 02:28 ipc -> ipc:[4026532283]
lrwxrwxrwx    1 root     root             0 Apr 15 02:28 mnt -> mnt:[4026532281]
lrwxrwxrwx    1 root     root             0 Apr 15 02:28 net -> net:[4026532461]
lrwxrwxrwx    1 root     root             0 Apr 15 02:28 pid -> pid:[4026532284]
lrwxrwxrwx    1 root     root             0 Apr 15 02:28 uts -> uts:[4026532282]
```
while the same command on the host may be:
```
# ls -al /proc/self/ns/
總計 0
dr-x--x--x 2 root root 0  4月 15 10:35 .
dr-xr-xr-x 8 root root 0  4月 15 10:35 ..
lrwxrwxrwx 1 root root 0  4月 15 10:35 ipc -> ipc:[4026531839]
lrwxrwxrwx 1 root root 0  4月 15 10:35 mnt -> mnt:[4026531840]
lrwxrwxrwx 1 root root 0  4月 15 10:35 net -> net:[4026531957]
lrwxrwxrwx 1 root root 0  4月 15 10:35 pid -> pid:[4026531836]
lrwxrwxrwx 1 root root 0  4月 15 10:35 uts -> uts:[4026531838]
```

The different numbers indicates different namespaces.

---

### Entering different namespaces using setns.c

First, you should start a container and get its process ID.  This can be achieved by
```
$ runc start --pid-file /tmp/runc.pid container1
$ cat /tmp/runc.pid
5678$
```
where you can specify a file to store the actual PID of the container.

With the information, now you can use `setns.c` program:
```
$ gcc setns.c -o setns
$ ./setns /proc/5678/ns/net
enter /proc/5678/ns/net...
container $ ip a
(different network interfaces here)
```
