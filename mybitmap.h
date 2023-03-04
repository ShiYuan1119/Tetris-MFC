#ifndef MYBITMAP_H
#define MYBITMAP_H

class MYBITMAP
{
public:
	MYBITMAP();
	~MYBITMAP();
	//初始化
	void Init(HINSTANCE hInstance,int iResource);
	void SetDevice(HDC hdest,HDC hsrc);
	//设置图像大小
	void InitSizeList(int num, int w,int h);
	void InitSizeList(int num, int w,int h,int ismask);
	void InitSizeList(int num, int *pw,int *ph,int ismask);
	//显示	
	void Show(int id,int x,int y);
	//去背显示
	void ShowNoBack(int id,int x,int y);
	void ShowNoBack(int id,int x,int y,int frame);
	//拉伸显示
	void Stretch(int id,int x,int y,int wdest,int ydest);
	
public:
	//位图句柄
	HBITMAP hBm;
	//
	HDC hdcdest;
	HDC hdcsrc;	

	//宽度 高度 纵坐标
	int wlist[20];
	int hlist[20];
	int ylist[20];
};

class MYBUTTON:public MYBITMAP
{
public:
	MYBUTTON()
	{
		idMouseOver=-1;
		//全部可见
		memset(IsShow,1,sizeof(IsShow));
	}
	~MYBUTTON()
	{
	}	
	//初始化按钮矩形
	void InitButton(int num,RECT *pRect);
	//显示	
	void Show(int id);
	//鼠标检测
	int MouseOver(int x,int y);

	void Hide(int id);

public:
	void Show2(int id);
	void HideAll();
	int idMouseOver;//鼠标在哪一个按钮上
	RECT *pRect;	
	int iBtNum;

	int IsShow[10];//是否可见
};



#endif
