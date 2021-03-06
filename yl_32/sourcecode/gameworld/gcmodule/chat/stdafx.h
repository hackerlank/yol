
#pragma once

#define NOMINMAX
#define SCRIPT_BINDK

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif

#include "Core.h"
#include "Core/QThread.h"
#include "Network/QSocket.h"

#include "Misc/utilities.h"

#pragma comment(lib, "lua5d.lib")
