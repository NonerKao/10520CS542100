### Exercise: share only MNT namespace with a container

First, copy necessary codes into `rootfs`:
```
# cp mnt/file_recv.c runc/rootfs
# cp mnt/file_send.c runc/rootfs
```

Start a container and compile the code:
```
# cd runc
# runc start with_mnt_test
/ # gcc file_recv.c -o server
/ # gcc file_send.c -o client
/ # ./server
```

Onpe another terminal.  Enter the `ns` directory (assume that the container has PID 1234) :
```
# cd ns
# gcc setns.c -o setns
# ./setns /proc/1234/ns/mnt
container $ ./client
```

Notice that in such case, the container cannot communicate with the `setns`ed process using `net` or `ipc` servers and clients.

