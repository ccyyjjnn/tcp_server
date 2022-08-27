#include "server.h"
#include "Socket.h"
#include "util.h"
#include "InterAddress.h"
#include <cstring>

int 
main ()
{
    Socket *ser_socket = new Socket ();
    InetAddress *ser_addr = new InetAddress ("127.0.0.1", 5188);
    ser_socket->bind (ser_addr);
    ser_socket->listen ();

    InetAddress *clin_addr = new InetAddress ();
    int conn = ser_socket->accept (clin_addr);
    char recvbuf[1024];
    while (1)
    {
        memset (recvbuf, 0, sizeof (recvbuf));
        int ret =read (conn, recvbuf, sizeof (recvbuf));
        write (conn, recvbuf, ret);
        printf ("客户端:%s",recvbuf);
    }
    return 0;
}