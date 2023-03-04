#ifndef GAMEBOX_H
#define GAMEBOX_H

struct SQUARE
{
	int id;

	POINT chip[4];//�ĸ�С�������
	int icolor;
	POINT pos;
};

//���
struct MAGIC
{
	int x;
	int y;
	int xoff;
	int yoff;
};
//�����׶�
enum magic_scene{
	SCENE0,
	SCENE1,
};
#define MAGIC_NUM 30


class GAMEBOX
{
public:
	GAMEBOX();
	~GAMEBOX();
	//��ʾͼƬ
	void Show();
	//ʱ�Ӵ���
	int Check();
	//����ƶ�����
	void MouseMove(int x,int y);
	//��굥��
	int LButtonUp(int x,int y);
	//��������
	void KeyProc(int iKey);
	//��ʼ����������
	void InitFont();

	//����
	void ShowInfoNow();
	void ClearMap();//�������
	void CreateNext();//�����µķ���



public:
	void BeginBomb(int isize);//��ʼ����Ч
	void ShowBomb();//�������

	void ShowSet();//�����ٶ�
	void ShowHelp();//��ʾ������Ϣ
	void ShowFail();//��ʾgameover

	//��ת���ƶ�
	void Rotate();
	void MoveDown();
	void ClearRow();
	void MoveRight();
	void MoveLeft();
	void PutSpare();//һ��������ף�д������
	int CanMove();//�Ƿ����ƶ�

	void CheckGame();//��Ϸ�м��
	void ShowSquare();//��Ϸ�л���

	//��Ϸ����
	int iState;
	//���ʣ���ˢ
	HBRUSH hBrush;
	HPEN hPen,hPenWhite;
	//����
	HFONT hf[10];

	/////////////////////
	//����
	int iAni;

	//��Ϸ����
	int gamemap[20][10];
	struct SQUARE squareNow;
	struct SQUARE squareNext;
	int iSpeed;//��Ϸ�еķ��齵���ٶ�
	int iTime;

	//�������
	int iScore;
	int iSpeedSet;//�����ò˵��У����õ��ٶ�
	////////////////////////////////
	int iStartBomb;
	int iScene;
	struct MAGIC magicobj[MAGIC_NUM];
	int iScale;//��������

	////////////// MFC �汾
	int iUseMagic;
};

#endif