#include "Socket.h"
#include "util.h"

Socket::Socket():fd(-1)
{
    fd = socket (AF_INET, SOCK_STREAM, 0);
    if_error (fd ==-1, "Socket no_parameter creat error");
}

void Socket::bind (InetAddress *addr)
{
    int value = ::bind (fd, (sockaddr *)&addr->addr, addr->addr_len);
    if_error (value == -1, "bind error\n");
}

void 
Socket::listen ()
{
    int value = ::listen (fd, SOMAXCONN);
    if_error (value == -1, "listen error\n");
}

int 
Socket::accept (InetAddress *addr)
{
    int accept_fd = ::accept (fd, (sockaddr *)&addr->addr, &addr->addr_len);
    if_error (accept_fd == -1, "accept error\n");
    return accept_fd;
}