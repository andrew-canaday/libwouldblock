libwouldblock
==========

A simple little hack to allow you to debug EAGAIN/EWOULDBLOCK behavior and
partial sends/receives.

License
-------
This project is licensed under the Apache License. See LICENSE for details.

Usage:
------

Use `WB_<syscall>_PROB=[0-100]` to set the probability of a given syscall
actually being invoked. The remainder of the time, the call returns
`EAGAIN/EWOULDBLOCK`.

Additionally, partial send/recv can be emulated by setting one or both of
`WB_RECV_SIZE` / `WB_SEND_SIZE` to non-zero values.


```Shell
# accept 80% of the time, recv 90% of the time and send 100% of the time
# also, only recv in 20 bytes chunks, and send in 15 byte chunks:
WB_PROB_ACCEPT=80 \
WB_PROB_RECV=90 \
WB_PROB_SEND=100 \
WB_RECV_SIZE=20 \
WB_SEND_SIZE=15 \
    wouldblock.sh my_exec --opt=val arg1 arg2
```

Installation:
=============

To install, you should be able to simply:

    ./autogen.sh
    mkdir ./build
    cd ./build
    ../configure && make check && make install

