#ifndef _DLLMAIN_H_
#define _DLLMAIN_H_

#include <Windows.h>
#include <stdio.h>
#include <shlobj.h>
#include <ctime>
#include <string>

struct ServerInfo
{
    char name[64];
    char ip[64];
    int port;
};

static ServerInfo GetServerInfo();

#endif