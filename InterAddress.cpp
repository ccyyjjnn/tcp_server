#include "InterAddress.h"
#include <cstring>
InetAddress::InetAddress (): addr_len (sizeof (addr))
{
    memset (&addr, 0, sizeof (addr));
    addr_len = sizeof (addr);
}

InetAddress::InetAddress (const char* ip, uint16_t port):addr_len (sizeof (addr))
{
    memset (&addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr (ip); //把网络地址转换成二进制数字，返回的地址已经是网络字节格式
    addr.sin_port = htons (port);
    addr_len = sizeof (addr);
}