
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
			//�����mask������ͼƬ�ļ���߶�Ҫ����2
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
			//�����mask������ͼƬ�ļ���߶�Ҫ����2
			ylist[i]=ylist[i-1]+hlist[i-1]*2;
		}
		else
		{
			ylist[i]=ylist[i-1]+hlist[i-1];
			
		}
	}
}

/////////// ��ť�� /////////////////////////////////////////////

void MYBUTTON::InitButton(int num,RECT *p)
{
	int i;

	pRect=p;
	//����right bottom
	for(i=0;i<num;i++)
	{
		wlist[i]=pRect[i].right;
		hlist[i]=pRect[i].bottom;

		pRect[i].right=pRect[i].left+pRect[i].right;
		pRect[i].bottom=pRect[i].top+pRect[i].bottom;
	}

	//����ͼƬ������
	ylist[0]=0;
	for(i=1;i<num;i++)
	{
		ylist[i]=ylist[i-1]+hlist[i-1];
	}

	iBtNum=num;//��ť����
}
void MYBUTTON::Show(int id)
{
	//���ɼ���ֱ�ӷ���
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
		//���а�ťȫ�ɼ���1��ʾ�ɼ�
		memset(IsShow,1,sizeof(IsShow));
	}
	else
	{
		IsShow[id]=0;//��ť��Ϊ���ɼ�
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

	//���ɼ�������-1
	if(!IsShow[idMouseOver])
	{
		idMouseOver=-1;
		return -1;
	}

	return idMouseOver;
}


void MYBUTTON::HideAll()
{
	//�������а�ť��0��ʾ���ɼ�
	memset(IsShow,0,sizeof(IsShow));
}

//��ʾ��ȡ������
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
