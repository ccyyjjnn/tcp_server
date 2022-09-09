#pragma once
#include <sys/epoll.h>
#include "Epoll.h"

class Epoll;
class FileDes
{
private:
    Epoll *ep;
    int fd;
    uint32_t listen_events;
    uint32_t now_events;
    bool    inEpoll;
public:
    FileDes(Epoll *_ep, int _fd);
    ~FileDes();

    int  get_fd ();
    void set_inEpoll ();
    bool get_inEpoll ();
    void set_listen_events ();
    int  get_listen_events ();
    int  get_now_events ();
    void set_now_events (uint32_t);
};

