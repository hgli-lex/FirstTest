/*
Library Version: 2010 0904
Designer: yzfy
E-Mail  : fygirl@vip.qq.com
Language: C++
Compiler: VC6/7/8/9   minGW with g++3.4.5
Comment : If you need to update this library, you can contact yzfy with Email
*/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#if defined(_MSC_VER) && _MSC_VER > 1000
#pragma once
#endif

#if !defined(_GRAPHICS_LIB_LINK_) && !defined(_SINGLE_FILE_)
#define _GRAPHICS_LIB_LINK_ 1
#endif

#include "yzfy_graphics.h"
#include "yzfy_dos.h"

#if defined(_MSC_VER) && defined(_CONSOLE)
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#endif
