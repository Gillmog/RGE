#ifndef CORE_H
#define CORE_H

#pragma once

#include <stdio.h>
#include <iostream>
#ifdef RGE_WIN
#include <tchar.h>
#include <windows.h>
#elif defined(RGE_UNIX)
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <curses.h>
#define FOREGROUND_INTENSITY 1
#define FOREGROUND_BLUE 1
#endif
#include <vector>
#include <assert.h>
#include <ctime>
#include <memory>
#include <functional>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "Geometry.h"

typedef unsigned short      WORD;
typedef unsigned long       DWORD;

using namespace std;

#endif // !CORE_H