### Running a container

You may use
```
$ runc start <any_name>
```
to launch a container with settings in `config.json` and the root directory in rootfs.

---

### Setup network for runc container

If networking is needed in container, you may execute the `script.sh` to setup a network namespace `net415`.  However, it may not work bydefault.  You **have to** some custom setup in the script.sh:
```
...
WAN=enp3s0
...
```
This setting should be replaced by your main network interface in your environment.  If you use the VM in assignment 1, this should be eth0.  Once the setting is done and the script is executed without any errors, then,
```
# ./script.sh
# runc start net_test
/ # ping 8.8.8.8
PING 8.8.8.8 (8.8.8.8): 56 data bytes
64 bytes from 8.8.8.8: seq=0 ttl=42 time=5.533 ms
64 bytes from 8.8.8.8: seq=1 ttl=42 time=5.381 ms
...
(it should work)
```
