#pragma once
#include <vector>
#include <sys/epoll.h>
#include <stdio.h>

class Epoll
{
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();
    std::vector <epoll_event> wait_epoll(int timeout =-1);
    void add_fd (int fd, uint32_t op);

};
