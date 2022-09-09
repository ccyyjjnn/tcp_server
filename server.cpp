#include "server.h"
#include "Socket.h"
#include "util.h"
#include "Epoll.h"
#include "InterAddress.h"
#include "FileDes.h"
#include <cstring>
#include <errno.h>


#define READ_BUFF 1024

void 
read_event (int sockfd)
{
    char buf[READ_BUFF];
    while (1)
    {
        sizeof (buf, 0, sizeof (buf));
        ssize_t read_byte = read (sockfd, buf, sizeof (buf));
        if (read_byte>0)
        {
            printf ("客户端 FD: %d__：__%s", sockfd, buf);
        }
        else if (read_byte < -1 && errno == EINTR)
        {
            printf ("客户端断开 FD：%d",sockfd);
            continue;
        }
        else if (read_byte ==-1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
        {
            break;
        }
        else if (read_byte == 0)
        {
            printf ("客户端关闭");
            close (sockfd);
            break;
        }
        else 
        {
            break;
        }
    }
    
}

int 
main ()
{
    Socket *ser_socket = new Socket ();
    InetAddress *ser_addr = new InetAddress ("127.0.0.1", 5555);
    int on = 1;
    int res = setsockopt(ser_socket->get_fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ser_socket->bind (ser_addr);
    ser_socket->listen ();
    Epoll *ep = new Epoll ();
    ser_socket->setnonblocking ();
    FileDes *ser_filedes = new FileDes (ep, ser_socket->get_fd());
    ser_filedes->set_listen_events ();
    while (true)
    {
        std::vector <FileDes*> ev = ep->wait_epoll();
        int ev_size = ev.size ();        
        for (int i = 0; i <ev_size; ++i)
        {
            int active = ev[i]->get_fd ();
            if (active == ser_socket->get_fd ())
            {
                InetAddress *cli_add = new InetAddress ();
                Socket *cli_sock = new Socket (ser_socket->accept (cli_add));
                printf ("\n新连接，fd:%d, IP:%s, Port:%d",
                        cli_sock->get_fd(), inet_ntoa (cli_add->addr.sin_addr), ntohs (cli_add->addr.sin_port));
                cli_sock->setnonblocking();
                FileDes *filedes = new FileDes(ep, cli_sock->get_fd ());
                filedes->set_listen_events ();
            }
            else if (ev[i]->get_now_events()  & EPOLLIN)
            {
                read_event (ev[i]->get_fd());
            }
        }
        
    }
    delete ser_socket;
    delete ser_addr;
    return 0;
}