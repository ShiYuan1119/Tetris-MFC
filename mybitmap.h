#ifndef MYBITMAP_H
#define MYBITMAP_H

class MYBITMAP
{
public:
	MYBITMAP();
	~MYBITMAP();
	//��ʼ��
	void Init(HINSTANCE hInstance,int iResource);
	void SetDevice(HDC hdest,HDC hsrc);
	//����ͼ���С
	void InitSizeList(int num, int w,int h);
	void InitSizeList(int num, int w,int h,int ismask);
	void InitSizeList(int num, int *pw,int *ph,int ismask);
	//��ʾ	
	void Show(int id,int x,int y);
	//ȥ����ʾ
	void ShowNoBack(int id,int x,int y);
	void ShowNoBack(int id,int x,int y,int frame);
	//������ʾ
	void Stretch(int id,int x,int y,int wdest,int ydest);
	
public:
	//λͼ���
	HBITMAP hBm;
	//
	HDC hdcdest;
	HDC hdcsrc;	

	//��� �߶� ������
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
		//ȫ���ɼ�
		memset(IsShow,1,sizeof(IsShow));
	}
	~MYBUTTON()
	{
	}	
	//��ʼ����ť����
	void InitButton(int num,RECT *pRect);
	//��ʾ	
	void Show(int id);
	//�����
	int MouseOver(int x,int y);

	void Hide(int id);

public:
	void Show2(int id);
	void HideAll();
	int idMouseOver;//�������һ����ť��
	RECT *pRect;	
	int iBtNum;

	int IsShow[10];//�Ƿ�ɼ�
};



#endif
