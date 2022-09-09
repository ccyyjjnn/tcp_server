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
    memset (events, 0, sizeof (events)*MAX_EVENTS);
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


std::vector <FileDes*> Epoll::wait_epoll (int timeout)
{
    std::vector <FileDes*> active_event;
    int wait_e = epoll_wait (epfd, events, MAX_EVENTS, timeout);
    if_error (wait_e == -1, "epoll wait error");
    for (int i = 0; i < wait_e; ++i)
    {
        FileDes *des = (FileDes *)events[i].data.ptr;
        des->set_now_events (events[i].events);
        active_event.push_back (des);
    }
    
    return active_event;
}

void Epoll::update_FileDes (FileDes *filedes)
{
    int fd = filedes->get_fd ();
    struct epoll_event ev;
    memset (&ev, 0, sizeof (ev));
    ev.data.ptr = filedes;
    ev.events = filedes->get_listen_events ();

    if (!filedes->get_inEpoll ())
    {
        int res = epoll_ctl (epfd, EPOLL_CTL_ADD, fd, &ev);
        if_error (res == -1, "epoll ADD error");
        filedes->set_inEpoll ();
    }
    else
    {
        int res = epoll_ctl (epfd, EPOLL_CTL_MOD, fd, &ev);
        if_error (res == -1, "epoll MOD error");
    }
}