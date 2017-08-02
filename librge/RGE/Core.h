#ifndef CORE_H
#define CORE_H

#pragma once

#include <stdio.h>
#include <iostream>
#ifdef RGE_WIN
#include <tchar.h>
#include <windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#elif defined(RGE_UNIX)
#include <termios.h>
#include <term.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <ncurses.h>
#include <signal.h>
#include <libgen.h>
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
#include <fstream>
#include "Geometry.h"

typedef unsigned short WORD;
typedef unsigned long DWORD;

using namespace std;

#endif // !CORE_H