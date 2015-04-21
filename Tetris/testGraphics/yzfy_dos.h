/*
Library Version: 2010 0904
Designer: yzfy
E-Mail  : fygirl@vip.qq.com
Language: C++
Compiler: VC6/7/8/9   minGW with g++3.4.5
Comment : If you need to update this library, you can contact yzfy with Email
*/

/*
包含本文件时，必须同时包含graphics
*/

#ifndef __YZFY_DOS_H__
#define __YZFY_DOS_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef far
#define far
#endif

#ifndef DLL_EXPORT
    #ifdef _USRDLL
        #ifndef PYGRAPHICS
            #define DLL_EXPORT __declspec(dllexport)
        #else
            #define DLL_EXPORT
        #endif
    #else
        #define DLL_EXPORT
    #endif
#endif

#ifndef farmalloc
#define farmalloc   malloc
#endif

#ifndef farfree
#define farfree     free
#endif

#ifndef _Cdecl
#if __STDC__
#define _Cdecl
#else
#define _Cdecl  __stdcall //cdecl
#endif
#endif

struct time {
    unsigned char   ti_min;     /* Minutes */
    unsigned char   ti_hour;    /* Hours */
    unsigned char   ti_hund;    /* Hundredths of seconds */
    unsigned char   ti_sec;     /* Seconds */
};

struct date {
    int     da_year;    /* Year - 1980 */
    char    da_day;     /* Day of the month */
    char    da_mon;     /* Month (1 = Jan) */
};

struct WORDREGS {
    unsigned int  ax, bx, cx, dx, si, di, cflag, flags;
};

struct BYTEREGS {
    unsigned char al, ah, bl, bh, cl, ch, dl, dh;
};

union   REGS    {
    struct  WORDREGS x;
    struct  BYTEREGS h;
};

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _GRAPHICS_INTERRUPT_
#define _GRAPHICS_INTERRUPT_
typedef void (__cdecl _interrupt)(void);
#define interrupt 
#endif

_interrupt*( getvect(int intr_num));

/* 中断处理函数 */
DLL_EXPORT void setvect(int intr_num, void interrupt(*isr)());

DLL_EXPORT void _Cdecl disable(void);
DLL_EXPORT void _Cdecl enable(void);
DLL_EXPORT void _Cdecl outportb(int port, char byte); /* $$$$$$$$$$$$$ */



/* 旧式系统函数部分 */
DLL_EXPORT void far _Cdecl delay(int delay_time);/* 延迟 delay_time/100 毫秒的时间，精度为0.01毫秒 */
DLL_EXPORT int  far _Cdecl bioskey (int cmd);
DLL_EXPORT void far _Cdecl gotoxy(int x, int y);
DLL_EXPORT void far _Cdecl textcolor(int color);
DLL_EXPORT void far _Cdecl textattr(int attr);
DLL_EXPORT int  far _Cdecl int86(int intr_num, union REGS *inregs, union REGS *outregs);
DLL_EXPORT void far _Cdecl gettime(struct time *timep);
DLL_EXPORT void far _Cdecl getdate(struct date *datep);





/* 旧式系统函数部分 */
DLL_EXPORT void far _Cdecl e_delay(void * _this, int delay_time);/* 延迟 delay_time/100 毫秒的时间，精度为0.01毫秒 */
DLL_EXPORT int  far _Cdecl e_bioskey(void * _this, int cmd);
DLL_EXPORT int  far _Cdecl e_int86(void * _this, int intr_num, union REGS *inregs, union REGS *outregs);


#ifdef __cplusplus
}
#endif

#endif
