#include "util.h"
#include "Epoll.h"
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 1024

Epoll::Epoll ():epfd (-1), events (nullptr)
{
    epfd = epoll_create1 (0);
    if_error (epfd == -1, "epoll creat error");
    events =new epoll_event [MAX_EVENTS];
    //printf ("---events:%d",events);
    memset (events, 0, sizeof (events));
}

Epoll::~Epoll ()
{
    if (epfd != -1)
    {
        close (epfd);
        epfd = -1;
    }
    delete [] events;
}

void
Epoll::add_fd (int fd, uint32_t op)
{
    struct epoll_event ev;
    memset (&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    ev.events = op;
    printf ("\n epoll_fd:%d",fd);
    if_error (epoll_ctl (epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "fd add event error");
}


std::vector <epoll_event> Epoll::wait_epoll (int timeout)
{
    //int timeout =-1;
    std::vector <epoll_event> active_event;
    int wait_e = epoll_wait (epfd, events, MAX_EVENTS, timeout);
    if_error (wait_e == -1, "epoll wait error");
    for (int i = 0; i < wait_e; ++i)
    {
        printf ("\n----i:%d---",i);
        active_event.push_back (events[i]);
    }
    
    return active_event;
}