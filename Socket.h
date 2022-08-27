#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <stdio.h>
#include "InterAddress.h"

class Socket
{
private:
    int fd;
public:
    Socket();
    ~Socket();

    void bind (InetAddress *);
    void listen ();
    int accept (InetAddress *);
};