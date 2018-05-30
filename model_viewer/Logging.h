#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdarg>
#include <cstdio>

#ifdef _DEBUG
	void MVDebugLog(const char* format, ...);
#define MVLOG(...) MVDebugLog(__VA_ARGS__)
#else
#define MVLOG(...)
#endif
