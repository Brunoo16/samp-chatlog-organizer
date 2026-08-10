#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Windows.h>
#include <cstdio>

#endif

#ifdef _DEBUG

void CreateDebugConsole();

#define DEBUG_PRINT(...) printf(__VA_ARGS__)

#else

#define DEBUG_PRINT(...) ((void)0)

#endif