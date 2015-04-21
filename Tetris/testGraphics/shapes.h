#ifndef _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_
#define _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_

#include "Include/easyx.h"
#include "Include/graphics.h"

// ��ɫ
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


const int iHorBox = 10;       // �װ���򷽿���Ŀ
const int iVerBox = 10;       // �װ����򷽿���Ŀ
const int iMaxShapes = 100;   // �������״�������Ŀ
const int BOX_SIZE = 20;                // ÿ������20����


#define FgColor 3       /*ǰ����ɫ,������.2-green*/
#define BgColor 0 
#define Sys_x 160           /*��ʾ�����������Ͻ�x����*/
#define Sys_y 25            /*��ʾ�����������Ͻ�y����*/

#define Horizontal_boxs 10  /*ˮƽ�ķ����Է���Ϊ��λ�ĳ���*/
#define Vertical_boxs 15    /*��ֱ�ķ����Է���Ϊ��λ�ĳ���,Ҳ��˵����15������*/

#define LeftWin_x Sys_x+Horizontal_boxs*BOX_SIZE+46        /*�ұ�״̬����x����*/

#define Begin_boxs_x Horizontal_boxs/2  /*������һ������ʱ���ֵ���ʼλ��*/
int Curbox_x=Sys_x+Begin_boxs_x*BOX_SIZE,Curbox_y=Sys_y;/*x,y�Ǳ��淽��ĵ�ǰ�����*/


//#define DRAW_BOX_LINES(x,y)  \
//    line(x,y,x+BOX_SIZE,y); \
//    line(x,y,x,y+BOX_SIZE); \
//    line(x,y+BOX_SIZE,x+BOX_SIZE,y+BOX_SIZE); \
//    line(x+BOX_SIZE,y,x+BOX_SIZE,y+BOX_SIZE); 

typedef struct tagSTBoard // ��Ϸ�װ�ṹ������ÿ�����������е�����
{
	int var;     // val = 0 ��ʾ�ø���δ��ռ�� val = 1��ʾ���ӱ�ռ��
	int color;   // color������ӵ���ɫ������������
}STBoard;

STBoard stBoard[iHorBox][iVerBox];

typedef struct tagSTShape
{
	/*
	 *	һ���ֽ�8bit ��ÿ4λ������Ϸ�����е�һ�У�����box[0]="0x88" box[1]="0xC0"��ʾ����
	 *  1 0 0 0
	 *  1 0 0 0
	 *  1 1 0 0
	 *  0 0 0 0
     *  ÿ����״��4X4�ķ����ʾ
	 */

	char box[2];
	int color;    // ÿ���������ɫ
    int next;     // �¸�����ı��
}STShape;

STShape shapes[iMaxShapes] = 
{

    /*
     *	 ��      �ڿڿ�    �ڿ�        ��
     *   ��      ��          ��    �ڿڿ�
     *   �ڿ�                ��
     */
    {0x88, 0xC0, CYAN, 1},
    {0xE8, 0x00, CYAN, 2},
    {0xC4, 0x40, CYAN, 3},
    {0x2E, 0x00, CYAN, 0},
};


#endif // _31D4DD08_E30A_42E5_97CC_12F07133F76E_H_