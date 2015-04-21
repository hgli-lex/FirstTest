#include "shapes.h"

static bool flag_nex_box = false;

static void DRAW_BOX_LINES(int x, int y)  
{
    line(x,y,x+BOX_SIZE,y); 
    line(x,y,x,y+BOX_SIZE); 
    line(x,y+BOX_SIZE,x+BOX_SIZE,y+BOX_SIZE); 
    line(x+BOX_SIZE,y,x+BOX_SIZE,y+BOX_SIZE); 
}

/*
 *  ��ʼ������������������Ϸ���� ��Ϸ�ȼ��Լ���ʼ����Ϸ����
 */
void InitGameInterface(int coordinateX, int coordinateY, int verBoxNum, int horBoxNum)
{
    int origRow = coordinateX;

    for (int i = 0; i < horBoxNum; ++i)
    {
        for (int j = 0; j < verBoxNum; ++j)
        {
            stBoard[i][j].var = 0;
            stBoard[i][j].color = BgColor;
            DRAW_BOX_LINES(coordinateX, coordinateY);
            coordinateX += BOX_SIZE;
        }
        coordinateY += BOX_SIZE;
        coordinateX = origRow;
    }
}
/*
 *��ʾָ���ķ���
 */
void show_box(int x,int y,int box_numb,int color)
{
    int i,ii,ls_x=x;
    if(box_numb<0 || box_numb>=iMaxShapes)/*ָ���ķ��鲻����*/
        box_numb=iMaxShapes/2;
    setfillstyle(SOLID_FILL,color);
/********************************* 
 *   ��λ���жϵ���һλ��1
 *   ������ÿ1���ð���ֽ�����ʾ
 *   128d=1000 0000b
 *********************************/
    for(ii=0;ii<2;ii++) 
    {
        int mask=128;
        for(i=0;i<8;i++)
        {
            if(i%4==0 && i!=0)              /*��ʾת���������һ����*/
            {
                y+=BOX_SIZE;
                x=ls_x;
            }
                       if((shapes[box_numb].box[ii])&mask)
            {
                bar(x,y,x+BOX_SIZE,y+BOX_SIZE);
                DRAW_BOX_LINES(x, y);
            }
            x+=BOX_SIZE;
            mask/=2;
        }
        y+=BOX_SIZE;
        x=ls_x;
    }
}

void initialize(int x,int y,int m,int n)
{

    int i,j,oldx;
    oldx=x;
    for(j=0;j<n;j++)
    {
        for(i=0;i<m;i++)
        {

            stBoard[j][i].var=0;
            stBoard[j][i].color=BgColor;
            line(x,y,x+BOX_SIZE,y);
            line(x,y,x,y+BOX_SIZE);
            line(x,y+BOX_SIZE,x+BOX_SIZE,y+BOX_SIZE);
            line(x+BOX_SIZE,y,x+BOX_SIZE,y+BOX_SIZE);
            x+=BOX_SIZE;
        }
        y+=BOX_SIZE;
        x=oldx;
    }
}

int main()
{
	int driver = DETECT, mode = 0;
	initgraph(&driver, &mode, "��һ��ege����");

    //initgraph(640, 480);
    setbkcolor(BgColor);    // ���ñ���ɫ
    setcolor(FgColor);      // ����ǰ��ɫ
    randomize();
    //bar(100, 100, 500, 500);   // ���Կ��Ի����ײ�

    InitGameInterface(Sys_x, Sys_y, Horizontal_boxs, 10);
    show_box(Curbox_x,Curbox_y,2,shapes[2].color);
    //show_box(LeftWin_x,Curbox_y+200,nextbox,shapes[nextbox].color);
    //initialize(Sys_x,Sys_y,Horizontal_boxs,Vertical_boxs);/*��ʼ��*/
    //show_box(Curbox_x,Curbox_y,1,shapes[1].color);
    //show_box(LeftWin_x,Curbox_y+200,2,shapes[2].color);

	getch();
	closegraph();
	return 0;
}