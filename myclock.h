///////////////////////////////////////////////////
//
// ���� programking    2009��7��
// ���� http://blog.csdn.net/programking
//
///////////////////////////////////////////////////

// ��ʱ��

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
		//�رն�ʱ��
		KillTimer(hWndClock, 1);
	}

	//ͳ��ʱ��Ƭ
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

	//��ʱ��iNumClip�仯���� 0��1��2��...��24��0��1��2
	//��0��24��ʾ1��
	int clipcount()
	{
		iNumClip++;
		if(iNumClip>=25)
		{
			// ����1��
			iNumClip=0;
			iNumDest--;
			if(iNumDest<=0)
			{
				// ����ָ��ʱ��
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

	//windows��ʱ��
	void Init(HWND hWnd,int timetotal)
	{
		SetTimer(hWnd,1,40,NULL);//ÿ40msˢ��һ��

		iNumDest=timetotal;	
		iNumClip=0;	
		hWndClock=hWnd;
	}
	//��ʾ
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