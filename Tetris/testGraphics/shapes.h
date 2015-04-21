#ifndef _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_
#define _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_

#include "Include/easyx.h"
#include "Include/graphics.h"

// 颜色
//#define	BLACK			0
//#define	BLUE			0xAA0000
//#define	GREEN			0x00AA00
//#define	CYAN			0xAAAA00
//#define	RED				0x0000AA
//#define	MAGENTA			0xAA00AA
//#define	BROWN			0x0055AA
//#define	LIGHTGRAY		0xAAAAAA
//#define	DARKGRAY		0x555555
//#define	LIGHTBLUE		0xFF5555
//#define	LIGHTGREEN		0x55FF55
//#define	LIGHTCYAN		0xFFFF55
//#define	LIGHTRED		0x5555FF
//#define	LIGHTMAGENTA	0xFF55FF
//#define	YELLOW			0x55FFFF
//#define	WHITE			0xFFFFFF


const int iHorBox = 10;       // 底板横向方块数目
const int iVerBox = 10;       // 底板纵向方块数目
const int iMaxShapes = 100;   // 下落的形状的最大数目
const int BOX_SIZE = 20;                // 每个方块20像素


#define FgColor 3       /*前景颜色,如文字.2-green*/
#define BgColor 0 
#define Sys_x 160           /*显示方块界面的左上角x坐标*/
#define Sys_y 25            /*显示方块界面的左上角y坐标*/

#define Horizontal_boxs 10  /*水平的方向以方块为单位的长度*/
#define Vertical_boxs 15    /*垂直的方向以方块为单位的长度,也就说长是15个方块*/

#define LeftWin_x Sys_x+Horizontal_boxs*BOX_SIZE+46        /*右边状态栏的x坐标*/

#define Begin_boxs_x Horizontal_boxs/2  /*产生第一个方块时出现的起始位置*/
int Curbox_x=Sys_x+Begin_boxs_x*BOX_SIZE,Curbox_y=Sys_y;/*x,y是保存方块的当前坐标的*/


//#define DRAW_BOX_LINES(x,y)  \
//    line(x,y,x+BOX_SIZE,y); \
//    line(x,y,x,y+BOX_SIZE); \
//    line(x,y+BOX_SIZE,x+BOX_SIZE,y+BOX_SIZE); \
//    line(x+BOX_SIZE,y,x+BOX_SIZE,y+BOX_SIZE); 

typedef struct tagSTBoard // 游戏底板结构，代表每个格子所具有的属性
{
	int var;     // val = 0 表示该各自未被占用 val = 1表示格子被占用
	int color;   // color代表格子的颜色，增加美观性
}STBoard;

STBoard stBoard[iHorBox][iVerBox];

typedef struct tagSTShape
{
	/*
	 *	一个字节8bit 用每4位代表游戏方块中的一行，例如box[0]="0x88" box[1]="0xC0"表示的是
	 *  1 0 0 0
	 *  1 0 0 0
	 *  1 1 0 0
	 *  0 0 0 0
     *  每个形状用4X4的方块表示
	 */

	char box[2];
	int color;    // 每个方块的颜色
    int next;     // 下个方块的编号
}STShape;

STShape shapes[iMaxShapes] = 
{

    /*
     *	 口      口口口    口口        口
     *   口      口          口    口口口
     *   口口                口
     */
    {0x88, 0xC0, CYAN, 1},
    {0xE8, 0x00, CYAN, 2},
    {0xC4, 0x40, CYAN, 3},
    {0x2E, 0x00, CYAN, 0},
};


#endif // _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_