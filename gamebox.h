#ifndef GAMEBOX_H
#define GAMEBOX_H

struct SQUARE
{
	int id;

	POINT chip[4];//四个小块的坐标
	int icolor;
	POINT pos;
};

//焰火
struct MAGIC
{
	int x;
	int y;
	int xoff;
	int yoff;
};
//动画阶段
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
	//显示图片
	void Show();
	//时钟处理
	int Check();
	//鼠标移动处理
	void MouseMove(int x,int y);
	//鼠标单击
	int LButtonUp(int x,int y);
	//按键处理
	void KeyProc(int iKey);
	//初始化字体数组
	void InitFont();

	//分数
	void ShowInfoNow();
	void ClearMap();//清除数组
	void CreateNext();//创建新的方块



public:
	void BeginBomb(int isize);//初始化特效
	void ShowBomb();//播放焰火

	void ShowSet();//设置速度
	void ShowHelp();//显示操作信息
	void ShowFail();//显示gameover

	//旋转、移动
	void Rotate();
	void MoveDown();
	void ClearRow();
	void MoveRight();
	void MoveLeft();
	void PutSpare();//一个方块落底，写入数组
	int CanMove();//是否能移动

	void CheckGame();//游戏中检测
	void ShowSquare();//游戏中绘制

	//游戏数据
	int iState;
	//画笔，画刷
	HBRUSH hBrush;
	HPEN hPen,hPenWhite;
	//字体
	HFONT hf[10];

	/////////////////////
	//动画
	int iAni;

	//游戏数据
	int gamemap[20][10];
	struct SQUARE squareNow;
	struct SQUARE squareNext;
	int iSpeed;//游戏中的方块降落速度
	int iTime;

	//玩家数据
	int iScore;
	int iSpeedSet;//在设置菜单中，设置的速度
	////////////////////////////////
	int iStartBomb;
	int iScene;
	struct MAGIC magicobj[MAGIC_NUM];
	int iScale;//粒子数量

	////////////// MFC 版本
	int iUseMagic;
};

#endif