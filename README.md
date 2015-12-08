libwouldblock
==========

A simple little hack to allow you to debug EAGAIN/EWOULDBLOCK behavior.

License
-------
This project is licensed under the Apache License. See LICENSE for details.

Usage:
------

Use `LWB_<syscall>_PROB=[0-100]` to set the probability of a given syscall
actually being invoked. The remainder of the time, the call returns
`EAGAIN/EWOULDBLOCK`.


```Shell
# accept 80% of the time, recv 90% of the time and send 100% of the time:
LWB_ACCEPT_PROB=80 \
LWB_RECV_PROB=90 \
LWB_SEND_PROB=100 \
    wouldblock.sh
```

Installation:
=============

To install, you should be able to simply:

    ./autogen.sh
    mkdir ./build
    cd ./build
    ../configure && make check && make install

