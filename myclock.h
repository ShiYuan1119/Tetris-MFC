///////////////////////////////////////////////////
//
// 制作 programking    2009年7月
// 博客 http://blog.csdn.net/programking
//
///////////////////////////////////////////////////

// 定时器

#ifndef __MYCLOCK
#define __MYCLOCK

#include "stdio.h"

#include "time.h"

class MYCLOCK
{
public:
	MYCLOCK()
	{
		iNumClip=0;
		iNumDest=20;

		timenow=clock();
		timeclip=CLOCKS_PER_SEC/40;
	}
	~MYCLOCK()
	{
		//关闭定时器
		KillTimer(hWndClock, 1);
	}

	//统计时间片
	int clockcount()
	{
		int t;

		t=clock()-timenow;
		if(t > timeclip)
		{
			timenow=clock();
			return 1;
		}
		return 0;
	}

	//计时：iNumClip变化过程 0，1，2，...，24，0，1，2
	//从0到24表示1秒
	int clipcount()
	{
		iNumClip++;
		if(iNumClip>=25)
		{
			// 到达1秒
			iNumClip=0;
			iNumDest--;
			if(iNumDest<=0)
			{
				// 到达指定时间
				return 1;
			}
		}	
		return 0;
	}

	void ReStart(int timetotal)
	{
		iNumDest=timetotal;	
		iNumClip=0;	
	}

	//windows定时器
	void Init(HWND hWnd,int timetotal)
	{
		SetTimer(hWnd,1,40,NULL);//每40ms刷新一次

		iNumDest=timetotal;	
		iNumClip=0;	
		hWndClock=hWnd;
	}
	//显示
	void Show(HDC hDC)
	{
		char temp[20]={0};

		sprintf(temp,"D %d,C %d ",iNumDest,iNumClip);
		TextOut(hDC,50,50,temp,strlen(temp));
	}


public:
	int iNumClip;
	int iNumDest;
	
	clock_t timenow;
	int timeclip;
	
	//windows
	HWND hWndClock;
};


#endif