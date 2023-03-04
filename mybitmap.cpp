
///////////////////////////////////////////////////
#include "stdafx.h"
#include "mybitmap.h"

MYBITMAP::MYBITMAP()
{

}

MYBITMAP::~MYBITMAP()
{
	DeleteObject(hBm);
}

void MYBITMAP::Init(HINSTANCE hInstance,int iResource)
{
	hBm=LoadBitmap(hInstance,MAKEINTRESOURCE(iResource));
}

void MYBITMAP::SetDevice(HDC hdest,HDC hsrc)
{
	hdcdest=hdest;
	hdcsrc=hsrc;
}

void MYBITMAP::Show(int id,int x,int y)
{
	SelectObject(hdcsrc,hBm);
	BitBlt(hdcdest,x,y,wlist[id],hlist[id],
		hdcsrc,0,ylist[id],SRCCOPY);	
}

void MYBITMAP::ShowNoBack(int id,int x,int y)
{
	SelectObject(hdcsrc,hBm);
	
	BitBlt(hdcdest,x,y,wlist[id],hlist[id],
		hdcsrc,0,ylist[id]+hlist[id],SRCAND);

	BitBlt(hdcdest,x,y,wlist[id],hlist[id],
		hdcsrc,0,ylist[id],SRCPAINT);
}
void MYBITMAP::ShowNoBack(int id,int x,int y,int frame)
{
	SelectObject(hdcsrc,hBm);
	
	BitBlt(hdcdest,x,y,wlist[id],hlist[id],
		hdcsrc,frame*wlist[id],ylist[id]+hlist[id],SRCAND);

	BitBlt(hdcdest,x,y,wlist[id],hlist[id],
		hdcsrc,frame*wlist[id],ylist[id],SRCPAINT);
}
void MYBITMAP::Stretch(int id,int x,int y, int wdest, int ydest)
{
	SelectObject(hdcsrc,hBm);
	StretchBlt(hdcdest,x,y,
		wdest,ydest,
		hdcsrc,
		0,ylist[id],
		wlist[id],hlist[id],
		SRCCOPY);	
}

void MYBITMAP::InitSizeList(int num, int w,int h)
{
	int i;

	for(i=0;i<num;i++)
	{
		wlist[i]=w;
		hlist[i]=h;
		ylist[i]=i*h;
	}
}
void MYBITMAP::InitSizeList(int inum, int w,int h,int ismask)
{
	int i;

	for(i=0;i<inum;i++)
	{
		wlist[i]=w;
		hlist[i]=h;
		if(ismask)
		{			
			//如果是mask，两张图片的间隔高度要乘以2
			ylist[i]=2*i*h;
		}
		else
		{
			ylist[i]=i*h;
			
		}
	}
}

void MYBITMAP::InitSizeList(int inum, int *pw,int *ph,int ismask)
{
	int i;
	memcpy(wlist, pw, inum*sizeof(int));
	memcpy(hlist, ph, inum*sizeof(int));

	ylist[0]=0;
	for(i=1;i<inum;i++)
	{
		if(ismask)
		{			
			//如果是mask，两张图片的间隔高度要乘以2
			ylist[i]=ylist[i-1]+hlist[i-1]*2;
		}
		else
		{
			ylist[i]=ylist[i-1]+hlist[i-1];
			
		}
	}
}

/////////// 按钮类 /////////////////////////////////////////////

void MYBUTTON::InitButton(int num,RECT *p)
{
	int i;

	pRect=p;
	//修正right bottom
	for(i=0;i<num;i++)
	{
		wlist[i]=pRect[i].right;
		hlist[i]=pRect[i].bottom;

		pRect[i].right=pRect[i].left+pRect[i].right;
		pRect[i].bottom=pRect[i].top+pRect[i].bottom;
	}

	//设置图片纵坐标
	ylist[0]=0;
	for(i=1;i<num;i++)
	{
		ylist[i]=ylist[i-1]+hlist[i-1];
	}

	iBtNum=num;//按钮数量
}
void MYBUTTON::Show(int id)
{
	//不可见，直接返回
	if(!IsShow[id])
		return;

	SelectObject(hdcsrc,hBm);

	if(idMouseOver == id)
	{
		BitBlt(hdcdest,pRect[id].left,pRect[id].top,
			wlist[id],hlist[id],
			hdcsrc,
			wlist[id],ylist[id],SRCCOPY);
	}
	else
	{
		BitBlt(hdcdest,pRect[id].left,pRect[id].top,
			wlist[id],hlist[id],
			hdcsrc,
			0,ylist[id],SRCCOPY);
	}

}

void MYBUTTON::Hide(int id)
{
	if(id<0)
	{
		//所有按钮全可见。1表示可见
		memset(IsShow,1,sizeof(IsShow));
	}
	else
	{
		IsShow[id]=0;//按钮设为不可见
	}
}

int MYBUTTON::MouseOver(int x,int y)
{
	int i;

	idMouseOver=-1;
	for(i=0;i<iBtNum;i++)
	{
		if(x>pRect[i].left
			&& x<pRect[i].right
			&& y>pRect[i].top 
			&& y<pRect[i].bottom)
		{
			idMouseOver=i;
			break;
		}
	}	

	//不可见，返回-1
	if(!IsShow[idMouseOver])
	{
		idMouseOver=-1;
		return -1;
	}

	return idMouseOver;
}


void MYBUTTON::HideAll()
{
	//隐藏所有按钮。0表示不可见
	memset(IsShow,0,sizeof(IsShow));
}

//显示并取消隐藏
void MYBUTTON::Show2(int id)
{
	IsShow[id]=1;

	SelectObject(hdcsrc,hBm);

	if(idMouseOver == id)
	{
		BitBlt(hdcdest,pRect[id].left,pRect[id].top,
			wlist[id],hlist[id],
			hdcsrc,
			wlist[id],ylist[id],SRCCOPY);
	}
	else
	{
		BitBlt(hdcdest,pRect[id].left,pRect[id].top,
			wlist[id],hlist[id],
			hdcsrc,
			0,ylist[id],SRCCOPY);
	}
}
