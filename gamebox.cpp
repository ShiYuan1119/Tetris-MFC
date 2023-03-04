
#include "stdafx.h"
//��Ϸ���
#include "gamebox.h"
//λͼ
#include "mybitmap.h"
//������
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"
//ʱ��
#include "myclock.h"
//��
#include "mykey.h"

//��ǰ����
extern HWND theWnd;

//DC:���ڣ���������ʱ�ڴ�
extern CDC *pDCwindow;
extern HDC hdccanvas,hdcmem;

//λͼ
extern MYBITMAP bmStart,bmBack,bmSquare,bmBomb;
//ʱ��
extern MYCLOCK myclock;
//��ť
extern MYBUTTON mybutton;

//��ͬ���෽��ı��
enum square_id{
	ID_SQAURE,	//����
};

//ÿ�ĸ��㣬��ʾһ�ַ���
//(һά����ά��������)
POINT gl_square[28]={
	//����
	{0,0},{1,0},{0,1},{1,1},
	//����
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

	//���û��ʣ���ˢ
	hPen=(HPEN)GetStockObject(NULL_PEN);
	hPenWhite=(HPEN)GetStockObject(WHITE_PEN);
	hBrush=(HBRUSH)GetStockObject(BLACK_BRUSH);

	//��ʼ״̬
	iState=GAME_INFO;
	/////////////////////
	iAni=0;

	iScore=0;
	iSpeed=1;
	iSpeedSet=1;

	ClearMap();

	//Ĭ��ʹ���̻�Ч��
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
		//��ɫ����
		SelectObject(hdccanvas,hBrush);
		SelectObject(hdccanvas,hPen);
		Rectangle(hdccanvas,0,0,GAMEWIDTH,GAMEHEIGHT);
		bmStart.Stretch(PIC0,30,100,GAMEWIDTH-60,GAMEHEIGHT-200);
		//��һ�� ����������ʾͼƬ
		if(iAni<=25)
		{
			i=25-iAni;
			//��ƽ����ʽ�����ٶ� GAMEWIDTH-i*i
			Rectangle(hdccanvas,GAMEWIDTH-i*i,0,GAMEWIDTH,GAMEHEIGHT);
		}
		break;

	case GAME_MENU:
		bmBack.Stretch(PIC0,0,0,GAMEWIDTH,GAMEHEIGHT);
		//��ʾ��ť
		mybutton.HideAll();
		mybutton.Show2(BT_START);
		mybutton.Show2(BT_HELP);
		mybutton.Show2(BT_SET);
		break;

	case GAME_LOAD:
		break;

	case GAME_IN:
		//��ɫ����
		SelectObject(hdccanvas,hBrush);
		SelectObject(hdccanvas,hPenWhite);
		Rectangle(hdccanvas,0,0,GAMEWIDTH,GAMEHEIGHT);
		//
		Rectangle(hdccanvas,20,18,244,462);
		Rectangle(hdccanvas,LEFT_RECT_X,LEFT_RECT_Y,242,460);
		//���Ͻ�
		Rectangle(hdccanvas,RIGHT_RECT_X,RIGHT_RECT_Y,
			RIGHT_RECT_X+132, RIGHT_RECT_Y+132);

		ShowInfoNow();//�������ٶ�����
		ShowSquare();//����
		ShowBomb();//��Ч
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

//��ʼ������
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


//( ����ֵԤ������ʱ����)
int GAMEBOX::Check()
{
	switch(iState)
	{
	case GAME_INFO:
		iAni++;
		if(myclock.clipcount())//�������ź���ʾ�˵�����
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
		if(myclock.clipcount()) //ʧ�ܶ�ʱ��������ʾ�˵�����
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
		//�������Ƿ��ƶ�����ť��
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

//����ѡ��Ĳ˵�ID
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
			//�����Ϸ����
			ClearMap();
			CreateNext();//������һ������

			iSpeed=iSpeedSet;
			//����������
			iScore=0;

			/////////////////
			iState=GAME_IN;
			//����ʱ��
			myclock.ReStart(TIME_MATCH);
			break;

		case BT_HELP:
			//����˵��
			return BT_HELP;


		case BT_SET:
			//����ѡ��
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

	return INVALID;//-1,��Ч
}

void GAMEBOX::KeyProc(int iKey)
{
	//ֻ����Ϸ�����У�����Ӧ����
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
		//���ز˵�
		iState=GAME_MENU;
		break;

	default:
		break;
	}
}

//��ʾ��ǰ�ٶȣ�����
void GAMEBOX::ShowInfoNow()
{
	char *strinfo[]={"SCORE:","SPEED:"};
	char temp[50]={0};


	SelectObject(hdccanvas,hf[0]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(0,200,0));
	//����
	TextOut(hdccanvas,270,200,strinfo[0],strlen(strinfo[0]));

	sprintf(temp,"%d",iScore);
	TextOut(hdccanvas,270,230,temp,strlen(temp));

	//�ٶ�
	SetTextColor(hdccanvas,RGB(50,60,240));
	TextOut(hdccanvas,270,300,strinfo[1],strlen(strinfo[1]));

	sprintf(temp,"%d",iSpeed);
	TextOut(hdccanvas,270,330,temp,strlen(temp));
}

//�������
void GAMEBOX::ClearMap()
{
	memset(gamemap,0,sizeof(gamemap));
	squareNow.id=INVALID;
	squareNext.id=INVALID;

	iTime=0;

	iStartBomb=0;//ֹͣ��Ч
	iScale=6;
}

//�����µķ���
void GAMEBOX::CreateNext()
{
	squareNext.id=rand()%7;
	squareNext.icolor=rand()%4+1;//��ɫ
	squareNext.pos.x=0;
	squareNext.pos.y=0;
	memcpy(squareNext.chip, &gl_square[squareNext.id*4],4*sizeof(POINT));

}

void GAMEBOX::ShowSquare()
{
	int i;
	int x0,y0;//����ԭ��
	int m,n;

	//���Ͻ���ʾ��һ��
	x0=RIGHT_RECT_X+2*ITEM_EDGE;
	y0=RIGHT_RECT_Y+2*ITEM_EDGE;

	for(i=0;i<4;i++)
	{
		bmSquare.Show(squareNext.icolor,
			x0+squareNext.chip[i].x*ITEM_EDGE,
			y0+squareNext.chip[i].y*ITEM_EDGE);
	}

	//��ǰ�ƶ��ķ���
	x0=LEFT_RECT_X+squareNow.pos.x*ITEM_EDGE;
	y0=LEFT_RECT_Y+squareNow.pos.y*ITEM_EDGE;

	if(squareNow.id!=INVALID)
	{
		for(i=0;i<4;i++)
		{
			//�����ڽ����ڣ�����ʾ
			if(squareNow.pos.y+squareNow.chip[i].y>=0)
			{
				bmSquare.Show(squareNow.icolor,
					x0+squareNow.chip[i].x*ITEM_EDGE,
					y0+squareNow.chip[i].y*ITEM_EDGE);
			}
		}
	}

	//�Ѿ����õķ���
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

//��Ϸ��Ҫ�߼����
void GAMEBOX::CheckGame()
{
	//������ڲ����̻�Ч����ֹͣ���
	if(iStartBomb)
		return;

	if(INVALID==squareNow.id)
	{
		//���û�е�ǰ�ƶ��ķ���
		//���ɵ�ǰ����
		memcpy(&squareNow,&squareNext,sizeof(squareNext));
		squareNow.pos.x=4;
		squareNow.pos.y=0;
		iTime=0;

		if(!CanMove())
		{
			//��������ɵķ����޷��ƶ���ʧ��
			iState=GAME_FAIL;
			myclock.ReStart(TIME_FAIL);
		}

		//������һ��
		CreateNext();
	}
	else
	{
		//�ƶ���ǰ����
		iTime++;
		if(iTime>=12-iSpeed)
		{
			iTime=0;
			if(!CanMove())
			{
				//�����ǰ����
				squareNow.id=INVALID;
				//д������
				PutSpare();
			}
			else
			{
				squareNow.pos.y++;
			}
		}
	}

	ClearRow();

	//�ٶ�
	if(iScore>=iSpeed*LEVEL_SCORE)
	{
		if(iSpeed<9)
			iSpeed++;
	}
}

int GAMEBOX::CanMove()
{
	int i;
	int m,n;//����

	for(i=0;i<4;i++)
	{
		//����
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
	int m,n;//����

	for(i=0;i<4;i++)
	{
		m=squareNow.pos.y+squareNow.chip[i].y;
		n=squareNow.pos.x+squareNow.chip[i].x;
		gamemap[m][n]=VALID;//�����з���
	}

}

void GAMEBOX::MoveLeft()
{
	int i;
	int m,n;//����
	int iCan=1;

	for(i=0;i<4;i++)
	{
		m=squareNow.pos.y+squareNow.chip[i].y;
		n=squareNow.pos.x+squareNow.chip[i].x-1;//����
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
	int m,n;//����
	int iCan=1;

	for(i=0;i<4;i++)
	{
		//����
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
	int m,n;//����
	int iNum;
	int iScoreRow[]={0,10,30,60,100};//��ֵ��1��10�֣�2��30��3��60��4��100
	int iRow;//��ȥ������

	iRow=0;
	//��19�У������һ��
	for(m=19;m>0;m--)
	{
		iNum=0;
		for(n=0;n<10;n++)
		{
			iNum+=gamemap[m][n];
		}
		//��ȥһ��
		if(iNum==10)
		{
			iRow++;//ͳ����ȥ������

			for(i=m;i>0;i--)
			{
				//�ƶ�
				memcpy(gamemap[i],gamemap[i-1],10*sizeof(int));
			}
			memset(gamemap[0],0,10*sizeof(int));
			m++;//��Ҫ���ٴμ����һ��
		}
		if(iNum==0)
		{
			//���У������ж�
			break;
		}
	}

	iScore+=iScoreRow[iRow];//���ӷ���
	if(iRow>=2)
	{
		//������������
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
	int m,n;//����
	int iCan=1;
	int temp;

	//�����β���ת
	if(ID_SQAURE==squareNow.id)
		return;

	for(i=0;i<4;i++)
	{
		//��ת���С������
		//��ת��ʽ(x,y)��ת90�ȱ�Ϊ(-y,x)���ټ��ϵ�ǰλ��
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
			//��ת���С������
			squareNow.chip[i].x=-squareNow.chip[i].y;
			squareNow.chip[i].y=temp;
		}
	}
}


void GAMEBOX::ShowFail()
{
	char *str[]={"GAME OVER"};
	char temp[50]={0};

	//����
	SelectObject(hdccanvas,hBrush);
	SelectObject(hdccanvas,hPenWhite);
	Rectangle(hdccanvas,50,170,GAMEWIDTH-50,GAMEHEIGHT-170);

	//�ı���ʧ��
	SelectObject(hdccanvas,hf[3]);
	SetBkColor(hdccanvas,RGB(0,0,0));
	SetTextColor(hdccanvas,RGB(140,200,200));
	TextOut(hdccanvas,110,200,str[0],strlen(str[0]));

}

void GAMEBOX::ShowHelp()
{
	char *str[]={
		"��ת�� ��",
		"�ƶ��� �� �� ��",
		"�˳��� Esc"
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
		"�����ٶ�",
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
			//һ����������������
			bmBomb.ShowNoBack(PIC0,magicobj[0].x,magicobj[0].y);
			//ˢ������
			magicobj[0].y+=magicobj[0].yoff;
			magicobj[0].yoff++;

			if(magicobj[0].yoff>=0)
			{
				iScene=SCENE1;//����2

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
			//�������ף�����
			//iScale:��������
			for(i=0;i<iScale;i++)
			{
				bmBomb.ShowNoBack(rand()%5,magicobj[i].x,magicobj[i].y);
				//ˢ������
				magicobj[i].y+=magicobj[i].yoff;
				magicobj[i].x+=magicobj[i].xoff;
				magicobj[i].yoff++;
			}
			if(magicobj[0].yoff>15)
			{
				iStartBomb=0;//ֹͣ
			}
		}
	}
}

//�����̻�����
void GAMEBOX::BeginBomb(int isize)
{
	int iSizeTable[]={3,4,5,10,20};

	//���û�п����̻�Ч����ֱ�ӷ���
	if(!iUseMagic)
		return;

	//isize��Χ:0��4����5���̻���ģ
	if(isize<0 || isize>4)
		return;

	iStartBomb=1;
	magicobj[0].x=120;
	magicobj[0].y=430;
	magicobj[0].xoff=0;
	magicobj[0].yoff=-16-isize*2;//���ó�ʼ�����ٶ�
	iScene=SCENE0;
	iScale=iSizeTable[isize];//������������
}
