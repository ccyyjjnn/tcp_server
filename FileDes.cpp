#include "FileDes.h"


FileDes::FileDes (Epoll *_ep, int _fd):ep(_ep), fd(_fd), listen_events(0), now_events(0), inEpoll(false)
{
}

FileDes::~FileDes ()
{}

int
FileDes::get_fd ()
{
    return fd;
}

void 
FileDes::set_listen_events ()
{
    listen_events = EPOLLIN | EPOLLET;
    ep->update_FileDes (this);
}

int
FileDes::get_listen_events ()
{    
    return listen_events;
}

void
FileDes::set_now_events (uint32_t _event)
{
    now_events = _event;
}

int
FileDes::get_now_events ()
{
    return now_events;
}

bool 
FileDes::get_inEpoll ()
{
    return inEpoll;
}

void
FileDes::set_inEpoll ()
{
    inEpoll = true;
}