/*
Library Version: 2010 0904
Designer: yzfy
E-Mail  : fygirl@vip.qq.com
Language: C++
Compiler: VC6/7/8/9   minGW with g++3.4.5
Comment : If you need to update this library, you can contact yzfy with Email
*/

/*
Compile: g++ need -luuid -loleaut32 -mwindows
*/

#ifndef __YZFY_GRAPHICS_H__
#define __YZFY_GRAPHICS_H__

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

#ifndef cprintf
#define cprintf printf
#endif

#ifndef cputs
#define cputs puts
#endif


#define _GRAPHICS_OPTIMIZE_   1
#define _GRAPHICS_FORCE_EXIT_ 1


#if defined(_GRAPHICS_LIB_LINK_)
    #ifdef _MSC_VER
        #if _GRAPHICS_LIB_LINK_ > 1
            #pragma comment(lib, "yzfy_graphics.lib")
        #elif _MSC_VER <= 1200
            #pragma comment(lib, "yzfy_graphics6.lib")
        #elif _MSC_VER <= 1400
            #pragma comment(lib, "yzfy_graphics05.lib")
        #elif _MSC_VER <= 1600
            #pragma comment(lib, "yzfy_graphics08.lib")
        #endif
        #if _MSC_VER >= 1200
            #ifdef _DEBUG
                #pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
                #pragma comment(linker, "/NODEFAULTLIB:MSVCRT.lib")
                #pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
            #else
                #pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
            #endif
        #else
            #ifdef _DEBUG
                #pragma comment(linker, "/NODEFAULTLIB:libc.lib")
            #endif
        #endif
    #endif
    #if _GRAPHICS_LIB_LINK_ > 1
        #undef DLL_EXPORT
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #ifdef _MSC_VER
        #if _MSC_VER > 1200
            #ifdef _DEBUG
                #pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
                #pragma comment(linker, "/NODEFAULTLIB:MSVCRT.lib")
                #pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
            #else
                /*#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")*/
            #endif
        #else
            #ifdef _DEBUG
                #pragma comment(linker, "/NODEFAULTLIB:libc.lib")
            #endif
        #endif
    #endif
#endif

#ifndef _Cdecl
#if __STDC__
#define _Cdecl  __stdcall //cdecl
#else
#define _Cdecl  __stdcall //cdecl
#endif
#endif

#ifndef ege_get_version
#ifdef UNICODE
#define ege_get_version ege_get_versionW
#else
#define ege_get_version ege_get_versionA
#endif
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1200
#define wchar_t unsigned short
#endif

/* 用户可用宏定义 */
#ifndef EGE_USER_MACRO
#define EGE_USER_MACRO

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))

#define SIZE2DWORD(w, h) ((w) | ((h)<<16))
#define LWORD(d) ((short)((d) & 0xFFFF))
#define HWORD(d) ((short)(((d) >> 16) & 0xFFFF))
#define ULWORD(d) ((unsigned short)((d) & 0xFFFF))
#define UHWORD(d) ((unsigned short)(((d) >> 16) & 0xFFFF))

#define COLOR_R(c) ((c) & 0xFF)
#define COLOR_G(c) (((c) >> 8) & 0xFF)
#define COLOR_B(c) (((c) >> 16) & 0xFF)
#define rgb(r, g, b) (((b) << 16) | ((g) << 8) | (r)) /* 为了不冲突，不得不改用小写 */
#define rgba(r, g, b, a) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r))

#endif

/* 常数声明 */
#if     !defined(__GRAPHX_DEF_)
#define __GRAPHX_DEF_

enum graphics_errors {      /* graphresult error return codes */
    grOk                =   0,
    grNoInitGraph       =  -1,
    grNotDetected       =  -2,
    grFileNotFound      =  -3,
    grInvalidDriver     =  -4,
    grNoLoadMem         =  -5,
    grNoScanMem         =  -6,
    grNoFloodMem        =  -7,
    grFontNotFound      =  -8,
    grNoFontMem         =  -9,
    grInvalidMode       = -10,
    grError             = -11,   /* generic error */
    grIOerror           = -12,
    grInvalidFont       = -13,
    grInvalidFontNum    = -14,
    grInvalidVersion    = -18,
    grException         = 0x10,  /* ege error */
    grParamError        = 0x11,
    grInvalidRegion     = 0x12,
    grOutOfMemory       = 0x13,
    grNullPointer       = 0x14,
    grAllocError        = 0x15,
    grInvalidMemory     = 0xCDCDCDCD,
};

enum graphics_drivers {     /* define graphics drivers */
    DETECT,         /* requests autodetection */
    CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,    /* 1 - 6 */
    HERCMONO, ATT400, VGA, PC3270,          /* 7 - 10 */
    TRUECOLOR, TRUECOLORSIZE,
    CURRENT_DRIVER = -1
};

enum graphics_modes {       /* graphics modes for each driver */
    CGAC0       = 0,  /* 320x200 palette 0; 1 page  */
    CGAC1       = 1,  /* 320x200 palette 1; 1 page  */
    CGAC2       = 2,  /* 320x200 palette 2: 1 page  */
    CGAC3       = 3,  /* 320x200 palette 3; 1 page  */
    CGAHI       = 4,  /* 640x200 1 page             */
    MCGAC0      = 0,  /* 320x200 palette 0; 1 page  */
    MCGAC1      = 1,  /* 320x200 palette 1; 1 page  */
    MCGAC2      = 2,  /* 320x200 palette 2; 1 page  */
    MCGAC3      = 3,  /* 320x200 palette 3; 1 page  */
    MCGAMED     = 4,  /* 640x200 1 page             */
    MCGAHI      = 5,  /* 640x480 1 page             */
    EGALO       = 0,  /* 640x200 16 color 4 pages   */
    EGAHI       = 1,  /* 640x350 16 color 2 pages   */
    EGA64LO     = 0,  /* 640x200 16 color 1 page    */
    EGA64HI     = 1,  /* 640x350 4 color  1 page    */
    EGAMONOHI   = 0,  /* 640x350 64K on card, 1 page - 256K on card, 4 pages */
    HERCMONOHI  = 0,  /* 720x348 2 pages            */
    ATT400C0    = 0,  /* 320x200 palette 0; 1 page  */
    ATT400C1    = 1,  /* 320x200 palette 1; 1 page  */
    ATT400C2    = 2,  /* 320x200 palette 2; 1 page  */
    ATT400C3    = 3,  /* 320x200 palette 3; 1 page  */
    ATT400MED   = 4,  /* 640x200 1 page             */
    ATT400HI    = 5,  /* 640x400 1 page             */
    VGALO       = 0,  /* 640x200 16 color 4 pages   */
    VGAMED      = 1,  /* 640x350 16 color 2 pages   */
    VGAHI       = 2,  /* 640x480 16 color 1 page    */
    PC3270HI    = 0,  /* 720x350 1 page             */
    IBM8514LO   = 0,  /* 640x480 256 colors         */
    IBM8514HI   = 1   /*1024x768 256 colors         */
};

/* Colors for setpalette and setallpalette */

#if !defined(__COLORS)
#define __COLORS

enum COLORS {
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,       /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

enum CGA_COLORS {
    CGA_LIGHTGREEN      = 1,        /* Palette C0 Color Names   */
    CGA_LIGHTRED        = 2,
    CGA_YELLOW          = 3,

    CGA_LIGHTCYAN       = 1,        /* Palette C1 Color Names   */
    CGA_LIGHTMAGENTA    = 2,
    CGA_WHITE           = 3,

    CGA_GREEN           = 1,        /* Palette C2 Color Names   */
    CGA_RED             = 2,
    CGA_BROWN           = 3,

    CGA_CYAN            = 1,        /* Palette C3 Color Names   */
    CGA_MAGENTA         = 2,
    CGA_LIGHTGRAY       = 3
};


enum EGA_COLORS {
    EGA_BLACK           =  0,   /* dark colors */
    EGA_BLUE            =  1,
    EGA_GREEN           =  2,
    EGA_CYAN            =  3,
    EGA_RED             =  4,
    EGA_MAGENTA         =  5,
    EGA_BROWN           =  20,
    EGA_LIGHTGRAY       =  7,
    EGA_DARKGRAY        =  56,  /* light colors */
    EGA_LIGHTBLUE       =  57,
    EGA_LIGHTGREEN      =  58,
    EGA_LIGHTCYAN       =  59,
    EGA_LIGHTRED        =  60,
    EGA_LIGHTMAGENTA    =  61,
    EGA_YELLOW          =  62,
    EGA_WHITE           =  63
};
#endif


enum line_styles {      /* Line styles for get/setlinestyle */
    SOLID_LINE   = 0,
    DOTTED_LINE  = 1,
    CENTER_LINE  = 2,
    DASHED_LINE  = 3,
    USERBIT_LINE = 4,   /* User defined line style */
};

enum line_widths {      /* Line widths for get/setlinestyle */
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3,
};

enum text_just {        /* Horizontal and vertical justification
                           for settextjustify */
    LEFT_TEXT   = 0,
    CENTER_TEXT = 1,
    RIGHT_TEXT  = 2,

    BOTTOM_TEXT = 0,
    /* CENTER_TEXT = 1,  already defined above */
    TOP_TEXT    = 2
};

enum font_names {
    DEFAULT_FONT    = 0,    /* 8x8 bit mapped font */
    TRIPLEX_FONT    = 1,    /* "Stroked" fonts */
    SMALL_FONT  = 2,
    SANS_SERIF_FONT = 3,
    GOTHIC_FONT = 4,
    USER_FONT = 5
};

#define HORIZ_DIR   0   /* left to right */
#define VERT_DIR    1   /* bottom to top */

#endif

enum fill_patterns {/* Fill patterns for get/setfillstyle */
    EMPTY_FILL,     /* fills area in background color */
    SOLID_FILL,     /* fills area in solid fill color */
    LINE_FILL,      /* --- fill */
    LTSLASH_FILL,   /* /// fill */
    SLASH_FILL,     /* /// fill with thick lines */
    BKSLASH_FILL,   /* \\\ fill with thick lines */
    LTBKSLASH_FILL, /* \\\ fill */
    HATCH_FILL,     /* light hatch fill */
    XHATCH_FILL,    /* heavy cross hatch fill */
    INTERLEAVE_FILL,/* interleaving line fill */
    WIDE_DOT_FILL,  /* Widely spaced dot fill */
    CLOSE_DOT_FILL, /* Closely spaced dot fill */
    USER_FILL       /* user defined fill */
};

enum putimage_ops { /* BitBlt operators for putimage */
    COPY_PUT,       /* MOV */
    XOR_PUT,        /* XOR */
    OR_PUT,         /* OR  */
    AND_PUT,        /* AND */
    NOT_PUT         /* NOT */
};

enum page_set {
    PAGE_USING              = 0x80000000 /* using this bit to choose page 0-3, from 0x80000000 to 0x80000003 */
};

enum graphics_settings {
    GRAPHICS_FORCEEXIT          = 0x01,
    GRAPHICS_TOPMOST            = 0x02,
    GRAPHICS_PRIORITY           = 0x03,
    GRAPHICS_OBJECT             = 0x04,
    GRAPHICS_SHOWMOUSE          = 0x05,
    GRAPHICS_PRESETSTYLE        = 0x06,
    GRAPHICS_PRESETEXSTYLE      = 0x07,
    GRAPHICS_SETTITLE           = 0x08,
    GRAPHICS_SETSTYLE           = 0x09,
    GRAPHICS_SETEXSTYLE         = 0x0A,
    GRAPHICS_SETWINDOWTITLE     = 0x0B,
    GRAPHICS_ALWAYS_RENDER      = 0x10,
    GRAPHICS_DELAY_LEASTMODE    = 0x11,
    GRAPHICS_NULL               = 0x00
};

enum message_event {
    MSG_EVENT_UP            = 0x00,
    MSG_EVENT_DOWN          = 0x01,
    MSG_EVENT_CLICK         = 0x01,
    MSG_EVENT_DBCLICK       = 0x02,
    MSG_EVENT_MOVE          = 0x04,
    MSG_EVENT_WHEEL         = 0x10,
};

enum message_mouse {
    MSG_MOUSE_LEFT      = 0x01,
    MSG_MOUSE_RIGHT     = 0x02,
    MSG_MOUSE_MID       = 0x04,
};

/* 结构声明 */

struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
};

struct linesettingstype
{
    int linestyle;
    unsigned upattern;
    int thickness;
};

struct arccoordstype {
    int x, y;
    int xstart, ystart, xend, yend;
};

struct viewporttype
{
    int left;
    int top;
    int right;
    int bottom;
    int clipflag;
};

typedef struct COLORHSL
{
    float h;
    float s;
    float l;
}COLORHSL;

typedef struct COLORHSV
{
    float h;
    float s;
    float v;
}COLORHSV;

typedef struct COLORRGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}COLORRGB;

/* 3d 结构 */
struct point2d {
    float x;
    float y;
};

struct point3d {
    float x;
    float y;
    float z;
};

struct vector2d {
    struct point2d p[2];
};

struct vector3d {
    struct point3d p[2];
};

typedef struct trangle2d {
    struct point2d p[3];
    int color;
}trangle2d;

struct trangle3d {
    struct point3d p[3];
    int color;
};

extern int directvideo;

/* 函数声明 */

typedef int (__stdcall MSG_FUNC_PROC )(void*, unsigned, unsigned, unsigned);
typedef int (__stdcall MSG_KEY_PROC  )(void*, unsigned, int);
typedef int (__stdcall MSG_MOUSE_PROC)(void*, unsigned, int, int, int);

typedef int (__stdcall EGE_GAME_PROC )(void*, float);

typedef MSG_FUNC_PROC       * LPMSG_FUNC_PROC;
typedef MSG_KEY_PROC        * LPMSG_KEY_PROC;
typedef MSG_MOUSE_PROC      * LPMSG_MOUSE_PROC;

typedef EGE_GAME_PROC       * LPEGE_GAME_PROC;


#ifndef _GRAPHICS_INTERRUPT_
#define _GRAPHICS_INTERRUPT_
typedef void (__cdecl _interrupt)();
#define interrupt
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*
_Cdecl 标识的为TC图形或系统函数，可在搜索引擎里找到相关解释
有$$$标记的为功能未完成函数
*/

/* 库属性函数 */
DLL_EXPORT int _Cdecl graphics_setting(int nCommand, void * pParam);
DLL_EXPORT const char*      far _Cdecl ege_get_versionA();
DLL_EXPORT const wchar_t*   far _Cdecl ege_get_versionW();

#ifdef wchar_t
#undef wchar_t
#endif

/* 窗口函数 */
DLL_EXPORT int graphupdate(); /* 强制更新指定句柄窗口图形区 */

/* 资源函数 */
DLL_EXPORT int far _Cdecl ege_getressize(int id, const char* type);
DLL_EXPORT int far _Cdecl ege_loadres(int id, const char* type, void* buffer);

/* 颜色函数 */
DLL_EXPORT COLORHSL far _Cdecl RGBtoHSL(int col);
DLL_EXPORT int far _Cdecl HSLtoRGB(float h, float s, float l);
DLL_EXPORT COLORHSV far _Cdecl RGBtoHSV(int col);
DLL_EXPORT int far _Cdecl HSVtoRGB(float h, float s, float v);
DLL_EXPORT int far _Cdecl RGBtoBGR(int color);
DLL_EXPORT int far _Cdecl RGBtoGRAY(int color);

/* 压缩函数 */
    /* 压缩时dest缓冲区要保证最小大小为sourceLen * 1.001 + 16 */
    /* 调用compress/compress2前，*destLen必须有值，表示dest缓冲区的最大大小，返回时这个值表示实际大小 */
    /* compress2 的level 从0-9，0不压缩，9最大压缩，compress函数使用默认值6 */
DLL_EXPORT int _Cdecl ege_compress(void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen);
DLL_EXPORT int _Cdecl ege_compress2(void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen, int level);
DLL_EXPORT int _Cdecl ege_uncompress(void *dest, unsigned long *destLen, const void *source, unsigned long sourceLen);
DLL_EXPORT unsigned long _Cdecl ege_uncompress_size(const void *source, unsigned long sourceLen); /* 返回0表示错误，其它表示大小 */

/*图形库部分*/

DLL_EXPORT void*far _Cdecl initgraph(int far *gdriver, int far *gmode, const char *path); /* 返回的指针在使用多窗口时有用 */
DLL_EXPORT void far _Cdecl detectgraph(int *gdriver, int *gmode);
DLL_EXPORT void far _Cdecl closegraph(void);
DLL_EXPORT int  far _Cdecl registerbgidriver(void (*driver)(void));
DLL_EXPORT void far _Cdecl EGAVGA_driver(void);
DLL_EXPORT int  far _Cdecl graphresult(void);
DLL_EXPORT char*far _Cdecl grapherrormsg(int errorcode);

DLL_EXPORT void far _Cdecl cleardevice(void);
DLL_EXPORT void far _Cdecl clrscr(void);

DLL_EXPORT int  far _Cdecl getpixel(int x, int y);
DLL_EXPORT void far _Cdecl putpixel(int x, int y, int color);

DLL_EXPORT int  far _Cdecl getcolor(void);
DLL_EXPORT int  far _Cdecl getbkcolor(void);
DLL_EXPORT int  far _Cdecl getmaxcolor(void);
DLL_EXPORT int  far _Cdecl getmaxx(void);
DLL_EXPORT int  far _Cdecl getmaxy(void);
DLL_EXPORT int  far _Cdecl getx(void);
DLL_EXPORT int  far _Cdecl gety(void);

DLL_EXPORT void far _Cdecl setcolor(int color);
DLL_EXPORT void far _Cdecl setbkcolor(int color);

DLL_EXPORT void far _Cdecl moveto(int x, int y);
DLL_EXPORT void far _Cdecl moverel(int dx, int dy);

DLL_EXPORT void far _Cdecl setlinestyle(int linestyle, unsigned upattern, int thickness);
DLL_EXPORT void far _Cdecl getlinesettings(struct linesettingstype far *lineinfo);
DLL_EXPORT void far _Cdecl setwritemode(int mode);

DLL_EXPORT void far _Cdecl line(int x0, int y0, int x1, int y1);
DLL_EXPORT void far _Cdecl lineto(int x, int y);
DLL_EXPORT void far _Cdecl linerel(int dx, int dy);

DLL_EXPORT void far _Cdecl bar(int x1, int y1, int x2, int y2);
DLL_EXPORT void far _Cdecl bar3d(int x1, int y1, int x2, int y2, int depth, int topflag);

DLL_EXPORT void far _Cdecl circle(int x, int y, int radius);
DLL_EXPORT void far _Cdecl arc(int x, int y, int stangle, int endangle, int radius);
DLL_EXPORT void far _Cdecl getarccoords(struct arccoordstype far *arccoords);
DLL_EXPORT void far _Cdecl ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);
DLL_EXPORT void far _Cdecl fillellipse(int x, int y, int xradius, int yradius);
DLL_EXPORT void far _Cdecl rectangle(int x1, int y1, int x2, int y2);
DLL_EXPORT void far _Cdecl drawpoly(int numpoints, int far *polypoints);
DLL_EXPORT void far _Cdecl floodfill(int x, int y, int border);
DLL_EXPORT void far _Cdecl setfillstyle(int pattern, int color);
DLL_EXPORT void far _Cdecl fillpoly(int numpoints, int far *polypoints);
DLL_EXPORT void far _Cdecl pieslice(int x, int y, int stangle, int endangle, int radius);
DLL_EXPORT void far _Cdecl sector(int X, int Y, int StAngle, int EndAngle, int XRadius, int YRadius);

DLL_EXPORT void far _Cdecl settextstyle(int font, int direction, int charsize); //* direction not support now * /
DLL_EXPORT void far _Cdecl settextjustify(int horiz, int vert);
DLL_EXPORT void far _Cdecl outtext(char far *textstring);
DLL_EXPORT void far _Cdecl outtextxy(int x, int y, char far *textstring);
DLL_EXPORT void far _Cdecl gettextsettings(struct textsettingstype far *textinfo);
DLL_EXPORT int  far _Cdecl textheight(char far *textstring);
DLL_EXPORT int  far _Cdecl textwidth(char far *textstring);
DLL_EXPORT void far _Cdecl setusercharsize(int multx, int divx, int multy, int divy);


DLL_EXPORT void far _Cdecl getimage(int x1, int y1, int x2, int y2, void far *mapbuf);
DLL_EXPORT void far _Cdecl putimage(int x, int y, void * mapbuf, int op);
DLL_EXPORT void far _Cdecl putimageex(void * destbuf, int x, int y, void * mapbuf, int op); //扩展
DLL_EXPORT unsigned far _Cdecl imagesize(int x1,int y1, int x2,int y2);

DLL_EXPORT void far _Cdecl setviewport(int left, int top, int right, int bottom, int clip);
DLL_EXPORT void far _Cdecl clearviewport(void);
DLL_EXPORT void far _Cdecl getviewsettings(struct viewporttype far *viewport);
DLL_EXPORT void far _Cdecl getaspectratio(int far *xasp, int far *yasp);
DLL_EXPORT void far _Cdecl setaspectratio(int xasp, int yasp);

DLL_EXPORT void far _Cdecl graphdefaults(void);

DLL_EXPORT void far _Cdecl setactivepage(int page);
DLL_EXPORT void far _Cdecl setvisualpage(int page);

/* 图形部分过时无意义占位用于兼容的函数 */
DLL_EXPORT unsigned far _Cdecl setgraphbufsize(unsigned bufsize);


/* 仿系统函数部分 */
DLL_EXPORT int _Cdecl getch();
DLL_EXPORT int _Cdecl getkey();
DLL_EXPORT int _Cdecl getflush();
DLL_EXPORT int _Cdecl kbhit();
DLL_EXPORT int  far _Cdecl random(int n);
DLL_EXPORT void far _Cdecl randomize();

/* 非标扩展函数部分 */
DLL_EXPORT void _Cdecl console_cls(void); /* 扩展函数 */
DLL_EXPORT void _Cdecl delay_ms(int ms);  /* 延迟ms毫秒的时间 */
DLL_EXPORT void _Cdecl delay_fps(int fps);/* 延迟1000/fps 毫秒的时间 */
DLL_EXPORT double _Cdecl fclock(); /* 返回以秒为单位的，程序启动以来的时间 */
DLL_EXPORT int  _Cdecl keystate(int nVirtualKey);
DLL_EXPORT void _Cdecl settextcolor(int color); /* setcolor会调用这个函数，这个函数在仅仅改字体颜色时有加速作用 */
DLL_EXPORT void _Cdecl setfont(char* name, int basesize, int option); /* option低四位有效，改变settextstyle中font=5的字体，从最低到高表示：加粗，加斜，加下划线，加删除线 */

/* 图形辅助扩展 */

    /* 加速版画线类函数，对于此类函数，线宽和线类型设置对此无效 */
DLL_EXPORT void _Cdecl line_base(int bx, int by, int ex, int ey, int color);
DLL_EXPORT void _Cdecl line_f(int x0, int y0, int x1, int y1);
DLL_EXPORT void _Cdecl lineto_f(int x, int y);
DLL_EXPORT void _Cdecl linerel_f(int dx, int dy);
DLL_EXPORT void _Cdecl drawpoly_f(int numpoints, int far *polypoints);

    /* GDIPLUS版函数，用于平滑输出 */
DLL_EXPORT void _Cdecl line_g(float x0, float y0, float x1, float y1);
DLL_EXPORT void _Cdecl lineto_g(float x, float y);
DLL_EXPORT void _Cdecl linerel_g(float dx, float dy);
DLL_EXPORT void _Cdecl drawpoly_g(int numpoints, float far *polypoints);
DLL_EXPORT void _Cdecl ellipse_g(float x1, float y1, float x2, float y2);
DLL_EXPORT void _Cdecl circle_g(float x, float y, float r);
DLL_EXPORT void _Cdecl arc_g(float x, float y, float stangle, float endangle, float r);
DLL_EXPORT void _Cdecl garc_g(float x1, float y1, float x2, float y2, float stangle, float sweepAngle);
DLL_EXPORT void _Cdecl rectangle_g(float x1, float y1, float x2, float y2);

DLL_EXPORT void*_Cdecl initimage(int width, int height);
DLL_EXPORT void _Cdecl freeimage(void *mapbuf); /* getimage 后不需要的图片尽可能调用本函数释放，
    尽管你不释放，库也会自动帮你，但主动调用会更有效利用内存空间 */
DLL_EXPORT int  _Cdecl getimagewidth(void *mapbuf);
DLL_EXPORT int  _Cdecl getimageheight(void *mapbuf);
DLL_EXPORT int  _Cdecl getimagenew(int width, int height, void *mapbuf);
DLL_EXPORT int  _Cdecl getbitmapfromresource(int id, void far *mapbuf);/* 读取正确返回0，否则非0，仅支持BITMAP类资源 */
DLL_EXPORT int  _Cdecl getbitmapfromresource2(const char* name, void far *mapbuf);
DLL_EXPORT int  _Cdecl getimagefromresource(int id, const char* type, void far *mapbuf);/* 读取正确返回0，否则非0 */
DLL_EXPORT int  _Cdecl getimagefromresource2(const char* name, const char* type, void far *mapbuf);
DLL_EXPORT int  _Cdecl getimagefromfile(const char* filename, void far *mapbuf); /* 读取正确返回0，否则非0 */
DLL_EXPORT int  _Cdecl saveimage(const char* filename, void far *mapbuf);

    /* 页间混合处理 */
DLL_EXPORT int _Cdecl mergeimage_copy(int page); /* page页(page>0)帖图到0页 */
DLL_EXPORT int _Cdecl mergeimage_transparent(int page); /* page页(page>0)以0为keycolor透明帖图到0页，以下几个均以0页为目标结果页且以0为keycolor */
DLL_EXPORT int _Cdecl mergeimage_alphablend(int page, int alpha); /* 与目标页按alpha混合 */
DLL_EXPORT int _Cdecl mergeimage_alphacopy(int destpage, int srcpage, int alpha); /* 源页alpha运算后覆盖目标页 */
DLL_EXPORT int _Cdecl mergeimageto_alphablend(int alpha); /* 以page1为目标以page2为源按alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl mergeimage_superalphablend(); /* 以page0为目标以page1为源按page2蓝色分量为alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl mergeimageto_superalphablend(); /* 以page1为目标以page2为源按page3蓝色分量为alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl visualpageswap(int page1, int page2);


    /*
    以下图形函数中，OriginDest是必须的，
    后面的关于位置和长宽的参数，如果置0则使用默认值，位置用(0,0)，长宽用图片大小
    */
DLL_EXPORT int _Cdecl putimage_stretch(
    const void* imgdest,
    const void* imgsrc,     // handle to source
    int nXOriginDest,       // x-coord of destination upper-left corner
    int nYOriginDest,       // y-coord of destination upper-left corner
    int nWidthDest,         // width of destination rectangle
    int nHeightDest,        // height of destination rectangle
    int nXOriginSrc,        // x-coord of source upper-left corner
    int nYOriginSrc,        // y-coord of source upper-left corner
    int nWidthSrc,          // width of source rectangle
    int nHeightSrc          // height of source rectangle
);

DLL_EXPORT int _Cdecl putimage_transparent(
    const void* imgdest,
    const void* imgsrc,     // handle to source
    int nXOriginDest,       // x-coord of destination upper-left corner
    int nYOriginDest,       // y-coord of destination upper-left corner
    int crTransparent,      // color to make transparent
    int nXOriginSrc,        // x-coord of source upper-left corner
    int nYOriginSrc,        // y-coord of source upper-left corner
    int nWidthSrc,          // width of source rectangle
    int nHeightSrc          // height of source rectangle
);

DLL_EXPORT int _Cdecl putimage_alphablend(
    const void* imgdest,
    const void* imgsrc,         // handle to source
    int nXOriginDest,           // x-coord of destination upper-left corner
    int nYOriginDest,           // y-coord of destination upper-left corner
    unsigned char alpha,        // alpha
    int nXOriginSrc,            // x-coord of source upper-left corner
    int nYOriginSrc,            // y-coord of source upper-left corner
    int nWidthSrc,              // width of source rectangle
    int nHeightSrc              // height of source rectangle
);

DLL_EXPORT int _Cdecl putimage_alphatransparent(
    const void* imgdest,
    const void* imgsrc,         // handle to source
    int nXOriginDest,           // x-coord of destination upper-left corner
    int nYOriginDest,           // y-coord of destination upper-left corner
    int crTransparent,          // color to make transparent
    unsigned char alpha,        // alpha
    int nXOriginSrc,            // x-coord of source upper-left corner
    int nYOriginSrc,            // y-coord of source upper-left corner
    int nWidthSrc,              // width of source rectangle
    int nHeightSrc              // height of source rectangle
);

DLL_EXPORT int _Cdecl putimage_trangle(
    const void* imgdest,
    const void* imgtexture,
    const struct trangle2d * dt,// dest trangle, original
    const struct trangle2d * tt,// textture trangle uv 0.0 - 1.0
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha= -1 means no alpha
    int smooth
);

DLL_EXPORT int _Cdecl putimage_rotate(
    const void* imgdest,
    const void* imgtexture,
    int nXOriginDest,
    int nYOriginDest,
    float centerx,
    float centery,
    float radian,
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha== -1 means no alpha
    int smooth
);

DLL_EXPORT int _Cdecl putimage_rotatezoom(
    const void* imgdest,
    const void* imgtexture,
    int nXOriginDest,
    int nYOriginDest,
    float centerx,
    float centery,
    float radian,
    float zoom,
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha== -1 means no alpha
    int smooth
);

    /* imagefilter */
DLL_EXPORT int _Cdecl imagefilter_blurring (
    void* imgdest,
    int nXOriginDest,
    int nYOriginDest,
    int nWidthDest,
    int nHeightDest,
    int intensity,              // in range[0, 0x80] 4 direction, in range[0x81, 0x100], 8 direction
    int alpha                   // in range[0, 256], alpha== -1 means no alpha
);


/* 窗口操作 */
DLL_EXPORT void _Cdecl window_getviewport(struct viewporttype * viewport);
DLL_EXPORT void _Cdecl window_setviewport(int x, int y, int w, int h);

/* 消息处理与主循环 */
/*
callback function define as:
int __stdcall on_msg_key(void* param, unsigned msg, int key);
msg: see 'enum message_event'
key: keycode
return zero means process this message, otherwise means pass it and then process with 'getch' function
*/
DLL_EXPORT int _Cdecl message_addkeyhandler(void* param, LPMSG_KEY_PROC func);
/*
callback function define as:
int __stdcall on_msg_mouse(void* param, unsigned msg, int key, int x, int y);
msg: see 'enum message_event'
key: see 'enum message_mouse', if msg==MSG_EVENT_WHELL, key is a int number that indicates the distance the wheel is rotated, expressed in multiples or divisions of WHEEL_DELTA, which is 120.
x,y: current mouse (x, y)
return zero means process this message, otherwise means pass it and then process with 'getch' function
*/
DLL_EXPORT int _Cdecl message_addmousehandler(void* param, LPMSG_MOUSE_PROC func);
//DLL_EXPORT int message_addmsghandler(void* param, msg_func_call func);

/*
callback function define as:
int __stdcall on_update(void* param, float ms);
int __stdcall on_render(void* param, float ms);

float ms: from the time last call to now
*/
DLL_EXPORT int _Cdecl ege_gameloop(
    LPEGE_GAME_PROC pUpdate,
    void* updateparam,
    unsigned updatefps,         //using zero set it unlimit
    LPEGE_GAME_PROC pRender,
    void* renderparam,
    unsigned renderfps          //using zero set it unlimit
    );


/* 3d部分 */
DLL_EXPORT void _Cdecl zoom_point3d(struct point3d * pt, float zoom);
DLL_EXPORT void _Cdecl zoom_trangle(struct trangle3d * t , float zoom);
DLL_EXPORT void _Cdecl rotate_point3d_x(struct point3d * pt, float r);
DLL_EXPORT void _Cdecl rotate_point3d_y(struct point3d * pt, float r);
DLL_EXPORT void _Cdecl rotate_point3d_z(struct point3d * pt, float r);
DLL_EXPORT void _Cdecl rotate_trangle_x(struct trangle3d * t , float r);
DLL_EXPORT void _Cdecl rotate_trangle_y(struct trangle3d * t , float r);
DLL_EXPORT void _Cdecl rotate_trangle_z(struct trangle3d * t , float r);
DLL_EXPORT void _Cdecl move_point3d(struct point3d * pt, const struct point3d * dpt);
DLL_EXPORT void _Cdecl move_trangle(struct trangle3d * t , const struct point3d * dpt);
DLL_EXPORT void _Cdecl set_viewpoint(const struct point3d * pt);
DLL_EXPORT void _Cdecl draw_trangle (const struct trangle3d * t);
DLL_EXPORT int  _Cdecl clear_zbuffer(void);













/* 库属性函数 */
DLL_EXPORT int _Cdecl e_graphics_setting(void * _this, int nCommand, void * pParam);

/* 窗口函数 */
DLL_EXPORT int e_graphupdate(void* _this); /* 强制更新指定句柄窗口图形区 */


/*图形库部分*/
DLL_EXPORT void*far _Cdecl e_initgraph(void * _this, int far *gdriver, int far *gmode, const char *path);
DLL_EXPORT void far _Cdecl e_closegraph(void * _this);

DLL_EXPORT void far _Cdecl e_cleardevice(void * _this);

DLL_EXPORT int  far _Cdecl e_getpixel(void * _this, int x, int y);
DLL_EXPORT void far _Cdecl e_putpixel(void * _this, int x, int y, int color);

DLL_EXPORT int  far _Cdecl e_getcolor(void * _this);
DLL_EXPORT int  far _Cdecl e_getbkcolor(void * _this);
DLL_EXPORT int  far _Cdecl e_getmaxcolor(void * _this);
DLL_EXPORT int  far _Cdecl e_getmaxx(void * _this);
DLL_EXPORT int  far _Cdecl e_getmaxy(void * _this);
DLL_EXPORT int  far _Cdecl e_getx(void * _this);
DLL_EXPORT int  far _Cdecl e_gety(void * _this);

DLL_EXPORT void far _Cdecl e_setcolor(void * _this, int color);
DLL_EXPORT void far _Cdecl e_setbkcolor(void * _this, int color);

DLL_EXPORT void far _Cdecl e_moveto(void * _this, int x, int y);
DLL_EXPORT void far _Cdecl e_moverel(void * _this, int dx, int dy);

DLL_EXPORT void far _Cdecl e_setlinestyle(void * _this, int linestyle, unsigned upattern, int thickness);
DLL_EXPORT void far _Cdecl e_getlinesettings(void * _this, struct linesettingstype far *lineinfo);
DLL_EXPORT void far _Cdecl e_setwritemode(void * _this, int mode);

DLL_EXPORT void far _Cdecl e_line(void * _this, int x0, int y0, int x1, int y1);
DLL_EXPORT void far _Cdecl e_lineto(void * _this, int x, int y);
DLL_EXPORT void far _Cdecl e_linerel(void * _this, int dx, int dy);

DLL_EXPORT void far _Cdecl e_bar(void * _this, int x1, int y1, int x2, int y2);
DLL_EXPORT void far _Cdecl e_bar3d(void * _this, int x1, int y1, int x2, int y2, int depth, int topflag);

DLL_EXPORT void far _Cdecl e_circle(void * _this, int x, int y, int radius);
DLL_EXPORT void far _Cdecl e_arc(void * _this, int x, int y, int stangle, int endangle, int radius);
DLL_EXPORT void far _Cdecl e_getarccoords(void * _this, struct arccoordstype far *arccoords);
DLL_EXPORT void far _Cdecl e_ellipse(void * _this, int x, int y, int stangle, int endangle, int xradius, int yradius);
DLL_EXPORT void far _Cdecl e_fillellipse(void * _this, int x, int y, int xradius, int yradius);
DLL_EXPORT void far _Cdecl e_rectangle(void * _this, int x1, int y1, int x2, int y2);
DLL_EXPORT void far _Cdecl e_drawpoly(void * _this, int numpoints, int far *polypoints);
DLL_EXPORT void far _Cdecl e_floodfill(void * _this, int x, int y, int border);
DLL_EXPORT void far _Cdecl e_setfillstyle(void * _this, int pattern, int color);
DLL_EXPORT void far _Cdecl e_fillpoly(void * _this, int numpoints, int far *polypoints);
DLL_EXPORT void far _Cdecl e_pieslice(void * _this, int x, int y, int stangle, int endangle, int radius);
DLL_EXPORT void far _Cdecl e_sector(void * _this, int X, int Y, int StAngle, int EndAngle, int XRadius, int YRadius);

DLL_EXPORT void far _Cdecl e_settextstyle(void * _this, int font, int direction, int charsize); /* direction not support now */
DLL_EXPORT void far _Cdecl e_settextjustify(void * _this, int horiz, int vert);
DLL_EXPORT void far _Cdecl e_outtext(void * _this, char far *textstring);
DLL_EXPORT void far _Cdecl e_outtextxy(void * _this, int x, int y, char far *textstring);
DLL_EXPORT void far _Cdecl e_gettextsettings(void * _this, struct textsettingstype far *textinfo);
DLL_EXPORT int  far _Cdecl e_textheight(void * _this, char far *textstring);
DLL_EXPORT int  far _Cdecl e_textwidth(void * _this, char far *textstring);
DLL_EXPORT void far _Cdecl e_setusercharsize(void * _this, int multx, int divx, int multy, int divy);


DLL_EXPORT void far _Cdecl e_getimage(void * _this, int x1, int y1, int x2, int y2, void far *mapbuf);
DLL_EXPORT void far _Cdecl e_putimage(void * _this, int x, int y, void * mapbuf, int op);
DLL_EXPORT void far _Cdecl e_putimageex(void * _this, void * destbuf, int x, int y, void * mapbuf, int op); //扩展
DLL_EXPORT unsigned far _Cdecl e_imagesize(void * _this, int x1,int y1, int x2,int y2);

DLL_EXPORT void far _Cdecl e_setviewport(void * _this, int left, int top, int right, int bottom, int clip);
DLL_EXPORT void far _Cdecl e_clearviewport(void * _this);
DLL_EXPORT void far _Cdecl e_getviewsettings(void * _this, struct viewporttype far *viewport);
DLL_EXPORT void far _Cdecl e_getaspectratio(void * _this, int far *xasp, int far *yasp);
DLL_EXPORT void far _Cdecl e_setaspectratio(void * _this, int xasp, int yasp);

DLL_EXPORT void far _Cdecl e_graphdefaults(void * _this);

DLL_EXPORT void far _Cdecl e_setactivepage(void * _this, int page);
DLL_EXPORT void far _Cdecl e_setvisualpage(void * _this, int page);

/* 仿系统函数部分 */
DLL_EXPORT int _Cdecl e_getch(void * _this);
DLL_EXPORT int _Cdecl e_getkey(void * _this);
DLL_EXPORT int _Cdecl e_getflush(void * _this);
DLL_EXPORT int _Cdecl e_kbhit(void * _this);

/* 非标扩展函数部分 */
DLL_EXPORT void _Cdecl e_delay_ms(void * _this, int ms);  /* 延迟ms毫秒的时间 */
DLL_EXPORT void _Cdecl e_delay_fps(void * _this, int fps);/* 延迟1000/fps 毫秒的时间 */
//DLL_EXPORT int  keystate(void * _this, int nVirtualKey);
DLL_EXPORT void _Cdecl e_settextcolor(void * _this, int color); /* setcolor会调用这个函数，这个函数在仅仅改字体颜色时有加速作用 */
DLL_EXPORT void _Cdecl e_setfont(void * _this, char* name, int basesize, int option); /* option低四位有效，改变settextstyle中font=5的字体，从最低到高表示：加粗，加斜，加下划线，加删除线 */

/* 图形辅助扩展 */

    /* 加速版画线类函数，对于此类函数，线宽和线类型设置对此无效 */
DLL_EXPORT void _Cdecl e_line_base(void * _this, int bx, int by, int ex, int ey, int color);
DLL_EXPORT void _Cdecl e_line_f(void * _this, int x0, int y0, int x1, int y1);
DLL_EXPORT void _Cdecl e_lineto_f(void * _this, int x, int y);
DLL_EXPORT void _Cdecl e_linerel_f(void * _this, int dx, int dy);
DLL_EXPORT void _Cdecl e_drawpoly_f(void * _this, int numpoints, int far *polypoints);

    /* GDIPLUS版函数，用于平滑输出 */
DLL_EXPORT void _Cdecl e_line_g(void * _this, float x0, float y0, float x1, float y1);
DLL_EXPORT void _Cdecl e_lineto_g(void * _this, float x, float y);
DLL_EXPORT void _Cdecl e_linerel_g(void * _this, float dx, float dy);
DLL_EXPORT void _Cdecl e_drawpoly_g(void * _this, int numpoints, float far *polypoints);
DLL_EXPORT void _Cdecl e_ellipse_g(void * _this, float x1, float y1, float x2, float y2);
DLL_EXPORT void _Cdecl e_circle_g(void * _this, float x, float y, float r);
DLL_EXPORT void _Cdecl e_arc_g(void * _this, float x, float y, float stangle, float endangle, float r);
DLL_EXPORT void _Cdecl e_garc_g(void * _this, float x1, float y1, float x2, float y2, float stangle, float sweepAngle);
DLL_EXPORT void _Cdecl e_rectangle_g(void * _this, float x1, float y1, float x2, float y2);

DLL_EXPORT void*_Cdecl e_initimage(void * _this, int width, int height);
DLL_EXPORT void _Cdecl e_freeimage(void * _this, void *mapbuf); /* getimage 后不需要的图片尽可能调用本函数释放，
    尽管你不释放，库也会自动帮你，但主动调用会更有效利用内存空间 */
DLL_EXPORT int  _Cdecl e_getimagewidth(void * _this, void *mapbuf);
DLL_EXPORT int  _Cdecl e_getimageheight(void * _this, void *mapbuf);
DLL_EXPORT int  _Cdecl e_getimagenew(void * _this, int width, int height, void *mapbuf);
DLL_EXPORT int  _Cdecl e_getbitmapfromresource(void * _this, int id, void far *mapbuf);/* 读取正确返回0，否则非0，仅支持BITMAP类资源 */
DLL_EXPORT int  _Cdecl e_getbitmapfromresource2(void * _this, const char* name, void far *mapbuf);
DLL_EXPORT int  _Cdecl e_getimagefromresource(void * _this, int id, const char* type, void far *mapbuf);/* 读取正确返回0，否则非0 */
DLL_EXPORT int  _Cdecl e_getimagefromresource2(void * _this, const char* name, const char* type, void far *mapbuf);
DLL_EXPORT int  _Cdecl e_getimagefromfile(void * _this, const char* filename, void far *mapbuf); /* 读取正确返回0，否则非0 */
DLL_EXPORT int  _Cdecl e_saveimage(void* _this, const char* filename, void far *mapbuf);

    /* 页间混合处理 */
DLL_EXPORT int _Cdecl e_mergeimage_copy(void * _this, int page); /* page页(page>0)帖图到0页 */
DLL_EXPORT int _Cdecl e_mergeimage_transparent(void * _this, int page); /* page页(page>0)以0为keycolor透明帖图到0页，以下几个均以0页为目标结果页且以0为keycolor */
DLL_EXPORT int _Cdecl e_mergeimage_alphablend(void * _this, int page, int alpha); /* 与目标页按alpha混合 */
DLL_EXPORT int _Cdecl e_mergeimage_alphacopy(void * _this, int destpage, int srcpage, int alpha); /* 源页alpha运算后覆盖目标页 */
DLL_EXPORT int _Cdecl e_mergeimageto_alphablend(void * _this, int alpha); /* 以page1为目标以page2为源按alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl e_mergeimage_superalphablend(void * _this); /* 以page0为目标以page1为源按page2蓝色分量为alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl e_mergeimageto_superalphablend(void * _this); /* 以page1为目标以page2为源按page3蓝色分量为alpha混合的结果存在page0 */
DLL_EXPORT int _Cdecl e_visualpageswap(void * _this, int page1, int page2);


    /*
    以下图形函数中，OriginDest是必须的，
    后面的关于位置和长宽的参数，如果置0则使用默认值，位置用(0,0)，长宽用图片大小
    */
DLL_EXPORT int _Cdecl e_putimage_stretch(
    void * _this,
    const void* imgdest,
    const void* imgsrc,     // handle to source
    int nXOriginDest,       // x-coord of destination upper-left corner
    int nYOriginDest,       // y-coord of destination upper-left corner
    int nWidthDest,         // width of destination rectangle
    int nHeightDest,        // height of destination rectangle
    int nXOriginSrc,        // x-coord of source upper-left corner
    int nYOriginSrc,        // y-coord of source upper-left corner
    int nWidthSrc,          // width of source rectangle
    int nHeightSrc          // height of source rectangle
);

DLL_EXPORT int _Cdecl e_putimage_transparent(
    void * _this,
    const void* imgdest,
    const void* imgsrc,     // handle to source
    int nXOriginDest,       // x-coord of destination upper-left corner
    int nYOriginDest,       // y-coord of destination upper-left corner
    int crTransparent,      // color to make transparent
    int nXOriginSrc,        // x-coord of source upper-left corner
    int nYOriginSrc,        // y-coord of source upper-left corner
    int nWidthSrc,          // width of source rectangle
    int nHeightSrc          // height of source rectangle
);

DLL_EXPORT int _Cdecl e_putimage_alphablend(
    void * _this,
    const void* imgdest,
    const void* imgsrc,         // handle to source
    int nXOriginDest,           // x-coord of destination upper-left corner
    int nYOriginDest,           // y-coord of destination upper-left corner
    unsigned char alpha,        // alpha
    int nXOriginSrc,            // x-coord of source upper-left corner
    int nYOriginSrc,            // y-coord of source upper-left corner
    int nWidthSrc,              // width of source rectangle
    int nHeightSrc              // height of source rectangle
);

DLL_EXPORT int _Cdecl e_putimage_alphatransparent(
    void * _this,
    const void* imgdest,
    const void* imgsrc,         // handle to source
    int nXOriginDest,           // x-coord of destination upper-left corner
    int nYOriginDest,           // y-coord of destination upper-left corner
    int crTransparent,          // color to make transparent
    unsigned char alpha,        // alpha
    int nXOriginSrc,            // x-coord of source upper-left corner
    int nYOriginSrc,            // y-coord of source upper-left corner
    int nWidthSrc,              // width of source rectangle
    int nHeightSrc              // height of source rectangle
);

DLL_EXPORT int _Cdecl e_putimage_trangle(
    void * _this,
    const void* imgdest,
    const void* imgtexture,
    const struct trangle2d * dt,// dest trangle, original
    const struct trangle2d * tt,// textture trangle uv 0.0 - 1.0
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha= -1 means no alpha
    int smooth
);

DLL_EXPORT int _Cdecl e_putimage_rotate(
    void * _this,
    const void* imgdest,
    const void* imgtexture,
    int nXOriginDest,
    int nYOriginDest,
    float centerx,
    float centery,
    float radian,
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha== -1 means no alpha
    int smooth
);

DLL_EXPORT int _Cdecl e_putimage_rotatezoom(
    void * _this,
    const void* imgdest,
    const void* imgtexture,
    int nXOriginDest,
    int nYOriginDest,
    float centerx,
    float centery,
    float radian,
    float zoom,
    int btransparent,           // transparent (1) or not (0)
    int alpha,                  // in range[0, 256], alpha== -1 means no alpha
    int smooth
);

    /* imagefilter */
DLL_EXPORT int _Cdecl e_imagefilter_blurring (
    void * _this,
    void* imgdest,
    int nXOriginDest,
    int nYOriginDest,
    int nWidthDest,
    int nHeightDest,
    int intensity,              // in range[0, 0x80] 4 direction, in range[0x81, 0x100], 8 direction
    int alpha                   // in range[0, 256], alpha== -1 means no alpha
);


/* 窗口操作 */
DLL_EXPORT void _Cdecl e_window_getviewport(void * _this, struct viewporttype * viewport);
DLL_EXPORT void _Cdecl e_window_setviewport(void * _this, int x, int y, int w, int h);

/* 消息处理与主循环 */
/*
callback function define as:
int __stdcall on_msg_key(void* param, unsigned msg, int key);
msg: see 'enum message_event'
key: keycode
return zero means process this message, otherwise means pass it and then process with 'getch' function
*/
DLL_EXPORT int _Cdecl e_message_addkeyhandler(void * _this, void* param, LPMSG_KEY_PROC func);
/*
callback function define as:
int __stdcall on_msg_mouse(void* param, unsigned msg, int key, int x, int y);
msg: see 'enum message_event'
key: see 'enum message_mouse', if msg==MSG_EVENT_WHELL, key is a int number that indicates the distance the wheel is rotated, expressed in multiples or divisions of WHEEL_DELTA, which is 120.
x,y: current mouse (x, y)
return zero means process this message, otherwise means pass it and then process with 'getch' function
*/
DLL_EXPORT int _Cdecl e_message_addmousehandler(void * _this, void* param, LPMSG_MOUSE_PROC func);
//DLL_EXPORT int message_addmsghandler(void * _this, void* param, msg_func_call func);

/*
callback function define as:
int __stdcall on_update(void* param, float ms);
int __stdcall on_render(void* param, float ms);

float ms: from the time last call to now
*/
DLL_EXPORT int _Cdecl e_ege_gameloop(
    void* _this,
    LPEGE_GAME_PROC pUpdate,
    void* updateparam,
    unsigned updatefps,         //using zero set it unlimit
    LPEGE_GAME_PROC pRender,
    void* renderparam,
    unsigned renderfps          //using zero set it unlimit
    );

/* 3d部分 */
DLL_EXPORT void _Cdecl e_set_viewpoint(void * _this, const struct point3d * pt);
DLL_EXPORT void _Cdecl e_draw_trangle (void * _this, const struct trangle3d * t);
DLL_EXPORT int  _Cdecl e_clear_zbuffer(void * _this);

#ifdef __cplusplus
}
#endif

#ifdef EGE_DEBUG_MEMLEAK
#include "debug_new.h"
#endif

#ifdef _SINGLE_FILE_
#if (_SINGLE_FILE_ != 0)
#include "yzfy_zlib.cpp"
#include "yzfy_graphics_c.cpp"
#include "yzfy_graphics.cpp"
#endif
#endif

#endif /*__YZFY_GRAPHICS_H__*/
