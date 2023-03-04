
#include "stdafx.h"
//游戏框架
#include "gamebox.h"
//位图
#include "mybitmap.h"
//基本库
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"
//时钟
#include "myclock.h"
//库
#include "mykey.h"

//当前窗口
extern HWND theWnd;

//DC:窗口，画布，临时内存
extern CDC *pDCwindow;
extern HDC hdccanvas,hdcmem;

//位图
extern MYBITMAP bmStart,bmBack,bmSquare,bmBomb;
//时钟
extern MYCLOCK myclock;
//按钮
extern MYBUTTON mybutton;

//不同种类方块的编号
enum square_id{
	ID_SQAURE,	//方形
};

//每四个点，表示一种方块
//(一维，二维都可以做)
POINT gl_square[28]={
	//方形
	{0,0},{1,0},{0,1},{1,1},
	//长条
	{0,-1},{0,0},{0,1},{0,2},
	//Z
	{-1,-1},{0,-1},{0,0},{1,0},
	//Z
	{-1,1},{0,1},{0,0},{1,0},
	//L
	{-1,-1},{-1,0},{0,0},{1,0},
	//L
	{-1,0},{0,0},{1,0},{1,-1},
	//
	{-1,0},{0,0},{1,0},{0,-1},
};

GAMEBOX::GAMEBOX()
{
	InitFont();

	//设置画笔，画刷
	hPen=(HPEN)GetStockObject(NULL_PEN);
	hPenWhite=(HPEN)GetStockObject(WHITE_PEN);
	hBrush=(HBRUSH)GetStockObject(BLACK_BRUSH);

	//初始状态
	iState=GAME_INFO;
	/////////////////////
	iAni=0;

	iScore=0;
	iSpeed=1;
	iSpeedSet=1;

	ClearMap();

	//默认使用烟花效果
	iUseMagic=1;
}

GAMEBOX::~GAMEBOX()
{
}

void GAMEBOX::Show()
{
	int i;

	switch(iState)
	{
	case GAME_INFO:
		//黑色背景
		SelectObject(hdccanvas,hBrush);
		SelectObject(hdccanvas,hPen);
		Rectangle(hdccanvas,0,0,GAMEWIDTH,GAMEHEIGHT);
		bmStart.Stretch(PIC0,30,100,GAMEWIDTH-60,GAMEHEIGHT-200);
		//第一秒 从左至右显示图片
		if(iAni<=25)
		{
			i=25-iAni;
			//按平方公式控制速度 GAMEWIDTH-i*i
			Rectangle(hdccanvas,GAMEWIDTH-i*i,0,GAMEWIDTH,GAMEHEIGHT);
		}
		break;

	case GAME_MENU:
		bmBack.Stretch(PIC0,0,0,GAMEWIDTH,GAMEHEIGHT);
		//显示按钮
		mybutton.HideAll();
		mybutton.Show2(BT_START);
		mybutton.Show2(BT_HELP);
		mybutton.Show2(BT_SET);
		break;

	case GAME_LOAD:
		break;

	case GAME_IN:
		//黑色背景
		SelectObject(hdccanvas,hBrush);
		SelectObject(hdccanvas,hPenWhite);
		Rectangle(hdccanvas,0,0,GAMEWIDTH,GAMEHEIGHT);
		//
		Rectangle(hdccanvas,20,18,244,462);
		Rectangle(hdccanvas,LEFT_RECT_X,LEFT_RECT_Y,242,460);
		//右上角
		Rectangle(hdccanvas,RIGHT_RECT_X,RIGHT_RECT_Y,
			RIGHT_RECT_X+132, RIGHT_RECT_Y+132);

		ShowInfoNow();//分数，速度文字
		ShowSquare();//方块
		ShowBomb();//特效
		break;

	case GAME_WIN:
		break;

	case GAME_FAIL:
		ShowFail();
		break;

	case GAME_PASS:
		break;

	case GAME_ITEM:
		break;

	default:
		break;
	}

}

//初始化字体
void GAMEBOX::InitFont()
{
	char temp[10]={0};
	int i;

	for(i=0;i<=sizeof(hf)/sizeof(HFONT);i++)
	{
		sprintf(temp,"black%d",i);
		hf[i]=CreateFont(10*(i+2),0,0,0,FW_HEAVY,0,0,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,temp);
	}
}


//( 返回值预留，暂时不用)
int GAMEBOX::Check()
{
	switch(iState)
	{
	case GAME_INFO:
		iAni++;
		if(myclock.clipcount())//动画播放后，显示菜单界面
		{
			iState=GAME_MENU;
			return 1;
		}
		break;

	case GAME_LOAD:
		break;

	case GAME_IN:
		CheckGame();
		break;

	case GAME_WIN:
		break;

	case GAME_ITEM:
		break;

	case GAME_FAIL:
		if(myclock.clipcount()) //失败定时结束，显示菜单界面
		{
			iState=GAME_MENU;
		}
		break;

	case GAME_PASS:
		break;

	default:
		break;
	}

	return 0;
}

void GAMEBOX::MouseMove(int x,int y)
{
	switch(iState)
	{
	case GAME_MENU:
		//检测鼠标是否移动到按钮上
		mybutton.MouseOver(x,y);
		break;

		break;

	case GAME_LOAD:
		break;

	case GAME_IN:
		break;

	case GAME_ITEM:
		break;

	default:
		break;
	}

}

//返回选择的菜单ID
int GAMEBOX::LButtonUp(int x,int y)
{
	int iButton;

	switch(iState)
	{
	case GAME_INFO:
		break;

	case GAME_MENU:
		iButton=mybutton.MouseOver(x,y);
		switch(iButton)
		{
		case BT_START:
			//清除游戏数据
			ClearMap();
			CreateNext();//创建第一个方块

			iSpeed=iSpeedSet;
			//清除玩家数据
			iScore=0;

			/////////////////
			iState=GAME_IN;
			//设置时间
			myclock.ReStart(TIME_MATCH);
			break;

		case BT_HELP:
			//操作说明
			return BT_HELP;


		case BT_SET:
			//设置选项
			return BT_SET;
		}
		break;

	case GAME_IN:
		break;

	case GAME_ITEM:
		break;

	default:
		break;
	}

	return INVALID;//-1,无效
}

void GAMEBOX::KeyProc(int iKey)
{
	//只有游戏进行中，才响应按键
	if(iState!=GAME_IN)
		return;

	switch(iKey)
	{
	case VK_UP:
		Rotate();
		break;

	case VK_LEFT:
		MoveLeft();
		break;

	case VK_RIGHT:
		MoveRight();
		break;

	case VK_DOWN:
		MoveDown();
		break;

	case KEY_F2:
		BeginBomb(2);
		break;

	case KEY_F3:
		BeginBomb(3);
		break;

	case KEY_F4:
		BeginBomb(4);
		break;

	case KEY_F12:
		if(iSpeed<9)
		{
			iSpeed++;
		}
		break;

	case VK_ESCAPE:
		//返回菜单
		iState=GAME_MENU;
		break;

	default:
		break;
	}
}

//显示当前速度，分数
void GAMEBOX::ShowInfoNow()
{
	char *strinfo[]={"SCORE:","SPEED:"};
	char temp[50]={0};


	SelectObject(hdccanvas,hf[0]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(0,200,0));
	//分数
	TextOut(hdccanvas,270,200,strinfo[0],strlen(strinfo[0]));

	sprintf(temp,"%d",iScore);
	TextOut(hdccanvas,270,230,temp,strlen(temp));

	//速度
	SetTextColor(hdccanvas,RGB(50,60,240));
	TextOut(hdccanvas,270,300,strinfo[1],strlen(strinfo[1]));

	sprintf(temp,"%d",iSpeed);
	TextOut(hdccanvas,270,330,temp,strlen(temp));
}

//清除数据
void GAMEBOX::ClearMap()
{
	memset(gamemap,0,sizeof(gamemap));
	squareNow.id=INVALID;
	squareNext.id=INVALID;

	iTime=0;

	iStartBomb=0;//停止特效
	iScale=6;
}

//创建新的方块
void GAMEBOX::CreateNext()
{
	squareNext.id=rand()%7;
	squareNext.icolor=rand()%4+1;//颜色
	squareNext.pos.x=0;
	squareNext.pos.y=0;
	memcpy(squareNext.chip, &gl_square[squareNext.id*4],4*sizeof(POINT));

}

void GAMEBOX::ShowSquare()
{
	int i;
	int x0,y0;//坐标原点
	int m,n;

	//右上角显示下一个
	x0=RIGHT_RECT_X+2*ITEM_EDGE;
	y0=RIGHT_RECT_Y+2*ITEM_EDGE;

	for(i=0;i<4;i++)
	{
		bmSquare.Show(squareNext.icolor,
			x0+squareNext.chip[i].x*ITEM_EDGE,
			y0+squareNext.chip[i].y*ITEM_EDGE);
	}

	//当前移动的方块
	x0=LEFT_RECT_X+squareNow.pos.x*ITEM_EDGE;
	y0=LEFT_RECT_Y+squareNow.pos.y*ITEM_EDGE;

	if(squareNow.id!=INVALID)
	{
		for(i=0;i<4;i++)
		{
			//方块在界面内，则显示
			if(squareNow.pos.y+squareNow.chip[i].y>=0)
			{
				bmSquare.Show(squareNow.icolor,
					x0+squareNow.chip[i].x*ITEM_EDGE,
					y0+squareNow.chip[i].y*ITEM_EDGE);
			}
		}
	}

	//已经放置的方块
	for(m=0;m<20;m++)
	{
		for(n=0;n<10;n++)
		{
			if(VALID==gamemap[m][n])
			{
				bmSquare.Show(PIC0,
					LEFT_RECT_X+n*ITEM_EDGE,
					LEFT_RECT_Y+m*ITEM_EDGE);
			}
		}
	}
}

//游戏主要逻辑检测
void GAMEBOX::CheckGame()
{
	//如果正在播放烟花效果，停止检测
	if(iStartBomb)
		return;

	if(INVALID==squareNow.id)
	{
		//如果没有当前移动的方块
		//生成当前方块
		memcpy(&squareNow,&squareNext,sizeof(squareNext));
		squareNow.pos.x=4;
		squareNow.pos.y=0;
		iTime=0;

		if(!CanMove())
		{
			//如果新生成的方块无法移动，失败
			iState=GAME_FAIL;
			myclock.ReStart(TIME_FAIL);
		}

		//生成下一个
		CreateNext();
	}
	else
	{
		//移动当前方块
		iTime++;
		if(iTime>=12-iSpeed)
		{
			iTime=0;
			if(!CanMove())
			{
				//清除当前方块
				squareNow.id=INVALID;
				//写入数组
				PutSpare();
			}
			else
			{
				squareNow.pos.y++;
			}
		}
	}

	ClearRow();

	//速度
	if(iScore>=iSpeed*LEVEL_SCORE)
	{
		if(iSpeed<9)
			iSpeed++;
	}
}

int GAMEBOX::CanMove()
{
	int i;
	int m,n;//行列

	for(i=0;i<4;i++)
	{
		//下落
		m=squareNow.pos.y+squareNow.chip[i].y+1;
		n=squareNow.pos.x+squareNow.chip[i].x;
		if(m>19 || VALID==gamemap[m][n])
		{
			return 0;
		}
	}

	return 1;
}

void GAMEBOX::PutSpare()
{
	int i;
	int m,n;//行列

	for(i=0;i<4;i++)
	{
		m=squareNow.pos.y+squareNow.chip[i].y;
		n=squareNow.pos.x+squareNow.chip[i].x;
		gamemap[m][n]=VALID;//设置有方块
	}

}

void GAMEBOX::MoveLeft()
{
	int i;
	int m,n;//行列
	int iCan=1;

	for(i=0;i<4;i++)
	{
		m=squareNow.pos.y+squareNow.chip[i].y;
		n=squareNow.pos.x+squareNow.chip[i].x-1;//左移
		if(n<0 || VALID==gamemap[m][n])
		{
			iCan=0;
			break;
		}
	}

	if(iCan)
		squareNow.pos.x--;
}

void GAMEBOX::MoveRight()
{
	int i;
	int m,n;//行列
	int iCan=1;

	for(i=0;i<4;i++)
	{
		//右移
		m=squareNow.pos.y+squareNow.chip[i].y;
		n=squareNow.pos.x+squareNow.chip[i].x+1;
		if(n>9 || VALID==gamemap[m][n])
		{
			iCan=0;
			break;
		}
	}

	if(iCan)
		squareNow.pos.x++;
}

void GAMEBOX::ClearRow()
{
	int i;
	int m,n;//行列
	int iNum;
	int iScoreRow[]={0,10,30,60,100};//分值，1行10分，2行30，3行60，4行100
	int iRow;//消去多少行

	iRow=0;
	//第19行，是最底一行
	for(m=19;m>0;m--)
	{
		iNum=0;
		for(n=0;n<10;n++)
		{
			iNum+=gamemap[m][n];
		}
		//消去一行
		if(iNum==10)
		{
			iRow++;//统计消去多少行

			for(i=m;i>0;i--)
			{
				//移动
				memcpy(gamemap[i],gamemap[i-1],10*sizeof(int));
			}
			memset(gamemap[0],0,10*sizeof(int));
			m++;//重要，再次检测这一行
		}
		if(iNum==0)
		{
			//空行，不再判断
			break;
		}
	}

	iScore+=iScoreRow[iRow];//增加分数
	if(iRow>=2)
	{
		//消除两行以上
		BeginBomb(iRow);
	}
}

void GAMEBOX::MoveDown()
{
	int i;

	for(i=0;i<19;i++)
	{
		if(!CanMove())
		{
			return;
		}
		else
		{
			squareNow.pos.y++;
		}
	}
}

void GAMEBOX::Rotate()
{
	int i;
	int m,n;//行列
	int iCan=1;
	int temp;

	//正方形不旋转
	if(ID_SQAURE==squareNow.id)
		return;

	for(i=0;i<4;i++)
	{
		//旋转后的小块坐标
		//旋转公式(x,y)旋转90度变为(-y,x)，再加上当前位置
		m=squareNow.pos.y+squareNow.chip[i].x;
		n=squareNow.pos.x-squareNow.chip[i].y;
		if( n<0 || n>9
			|| m<0 || m>19
			|| VALID==gamemap[m][n])
		{
			iCan=0;
			break;
		}
	}

	if(iCan)
	{
		for(i=0;i<4;i++)
		{
			temp=squareNow.chip[i].x;
			//旋转后的小块坐标
			squareNow.chip[i].x=-squareNow.chip[i].y;
			squareNow.chip[i].y=temp;
		}
	}
}


void GAMEBOX::ShowFail()
{
	char *str[]={"GAME OVER"};
	char temp[50]={0};

	//矩形
	SelectObject(hdccanvas,hBrush);
	SelectObject(hdccanvas,hPenWhite);
	Rectangle(hdccanvas,50,170,GAMEWIDTH-50,GAMEHEIGHT-170);

	//文本：失败
	SelectObject(hdccanvas,hf[3]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(140,200,200));
	TextOut(hdccanvas,110,200,str[0],strlen(str[0]));

}

void GAMEBOX::ShowHelp()
{
	char *str[]={
		"旋转： 上",
		"移动： 左 右 下",
		"退出： Esc"
		};
	char temp[50]={0};
	int i;

	SelectObject(hdccanvas,hf[1]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(190,170,110));

	for(i=0;i<3;i++)
	{
		TextOut(hdccanvas,110,200+i*40,str[i],strlen(str[i]));
	}
}

void GAMEBOX::ShowSet()
{
	char *str[]={
		"设置速度",
		};
	char temp[50]={0};

	SelectObject(hdccanvas,hf[1]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(190,170,110));
	TextOut(hdccanvas,140,200,str[0],strlen(str[0]));

	sprintf(temp,"%d",iSpeedSet);
	TextOut(hdccanvas,200,280,temp,strlen(temp));
}

void GAMEBOX::ShowBomb()
{
	int i;

	if(iStartBomb)
	{
		if(SCENE0==iScene)
		{
			//一个粒子上抛至顶点
			bmBomb.ShowNoBack(PIC0,magicobj[0].x,magicobj[0].y);
			//刷新坐标
			magicobj[0].y+=magicobj[0].yoff;
			magicobj[0].yoff++;

			if(magicobj[0].yoff>=0)
			{
				iScene=SCENE1;//动画2

				for(i=0;i<iScale;i++)
				{
					magicobj[i].x=magicobj[0].x;
					magicobj[i].y=magicobj[0].y;
					magicobj[i].yoff=-rand()%15;
					magicobj[i].xoff=rand()%9-4;
				}
			}
		}
		else if(SCENE1==iScene)
		{
			//粒子上抛，下落
			//iScale:粒子数量
			for(i=0;i<iScale;i++)
			{
				bmBomb.ShowNoBack(rand()%5,magicobj[i].x,magicobj[i].y);
				//刷新坐标
				magicobj[i].y+=magicobj[i].yoff;
				magicobj[i].x+=magicobj[i].xoff;
				magicobj[i].yoff++;
			}
			if(magicobj[0].yoff>15)
			{
				iStartBomb=0;//停止
			}
		}
	}
}

//启动烟花动画
void GAMEBOX::BeginBomb(int isize)
{
	int iSizeTable[]={3,4,5,10,20};

	//如果没有开启烟花效果，直接返回
	if(!iUseMagic)
		return;

	//isize范围:0至4，共5种烟花规模
	if(isize<0 || isize>4)
		return;

	iStartBomb=1;
	magicobj[0].x=120;
	magicobj[0].y=430;
	magicobj[0].xoff=0;
	magicobj[0].yoff=-16-isize*2;//设置初始上抛速度
	iScene=SCENE0;
	iScale=iSizeTable[isize];//设置粒子数量
}
