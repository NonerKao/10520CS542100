### Assignment 2: Container Practice

This package provides you example programs that helps you accomplish this assignment.

* ipc, net, mnt: The three directories contain one-shot server-client communication examples.
* runc: The files to run a runc container, config.json and rootfs, are provided.
* ns: A demonstration of how a proccess can set its namespace.

Note that the last two requires the **root privilege**.

---

### The objective of this assignment: An echo service

1. Start container A, which runs the server program.  The server should block for an incoming message.
2. Start container B, which runs the client program.  The client should block for user inputs.
3. Choose any two of the NET, MNT, IPC namespaces, says X and Y.
4. Run the bridge program on the host.  The bridge should set its X namespace the same as container A's X namespace, and Y the same as B's.
5. Type any messages at the client side.  This should casuse the message to be sent through the common namespace, which is Y, between container B and the bridge program.
6. The bridge program then redirect the message through X namespace between container A and itself.
7. The server program in container A gets the message, and directly send identical message back.
8. The brdige then redirect the message from the server to the client.
9. The client should display the result.

As an example, the terminal running a client with a working echo service should look like this:
```
$ ./client
This is the first sentence
This is the first sentence
second
second
OK?
OK?
...
```

You should implement the transformation from a input message to the standard output.

---

### Questions?

Please report any problems you encounter on ILMS.  We will do our best to help you accomplish this assignment.
