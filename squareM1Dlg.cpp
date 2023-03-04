///////////////////////////////////////////////////
//
// programking游戏工作室    2009年8月
// 博客 http://blog.csdn.net/programking
//
///////////////////////////////////////////////////

// squareM1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "squareM1.h"
#include "squareM1Dlg.h"

//
//游戏框架
#include "gamebox.h"
//图片处理
#include "mybitmap.h"
//时钟
#include "myclock.h"
#include "filereport.h"
//dialog
#include "dlghelp.h"
#include "dlgset.h"

//跟踪打印
//FILEREPORT f1;

extern CSquareM1App theApp;

//DIALOG
CDlgHelp dlgHelp;	
CDlgSet dlgSet;	

HWND theWnd;

MYCLOCK myclock;

//游戏框架
GAMEBOX gb;

//DC:窗口，画布，临时内存
CDC *pDCwindow;
HDC hdccanvas,hdcmem;

//空位图
HBITMAP hmapnull;
//位图
MYBITMAP bmStart,bmBack,bmSquare,bmBomb;

//按钮
MYBUTTON mybutton;
//按钮坐标 宽 高 x,y,w,h
RECT BtRect[]={
	{160,210,100,30},
	{160,270,100,30},
	{160,330,100,30},
	{160,390,100,30},
	{110,280,50,30},
	{260,280,50,30},
};

//


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquareM1Dlg dialog

CSquareM1Dlg::CSquareM1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSquareM1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSquareM1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSquareM1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSquareM1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSquareM1Dlg, CDialog)
	//{{AFX_MSG_MAP(CSquareM1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquareM1Dlg message handlers

BOOL CSquareM1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int x,y;
   	//窗口居中, 高度包含标题栏的30
	x=GetSystemMetrics(SM_CXSCREEN);
	y=GetSystemMetrics(SM_CYSCREEN);	
	MoveWindow((x-GAMEWIDTH)/2,(y-GAMEHEIGHT-30)/2,GAMEWIDTH,GAMEHEIGHT+30,false);	

	//初始化数据
	HINSTANCE hInstance=theApp.m_hInstance;//程序实例
	theWnd=m_hWnd;//当前窗口句柄

	pDCwindow=GetDC();//DC

	hdccanvas=CreateCompatibleDC(pDCwindow->m_hDC);
	hdcmem=CreateCompatibleDC(pDCwindow->m_hDC);
	//用空位图初始化DC
	hmapnull=CreateCompatibleBitmap(pDCwindow->m_hDC,GAMEWIDTH,GAMEHEIGHT);
	SelectObject(hdccanvas,hmapnull);
	SelectObject(hdcmem,hmapnull);

	//位图初始化
	bmStart.Init(hInstance,IDB_BITMAP_START);
	bmStart.SetDevice(hdccanvas,hdcmem);
	bmStart.InitSizeList(1,PICW,PICH);

	bmBack.Init(hInstance,IDB_BITMAP_BACK);
	bmBack.SetDevice(hdccanvas,hdcmem);
	bmBack.InitSizeList(1,200,200);

	bmSquare.Init(hInstance,IDB_BITMAP_SQUARE);
	bmSquare.SetDevice(hdccanvas,hdcmem);
	bmSquare.InitSizeList(5,22,22);

	bmBomb.Init(hInstance,IDB_BITMAP_BOMB);
	bmBomb.SetDevice(hdccanvas,hdcmem);
	bmBomb.InitSizeList(5,22,22,1);

	//按钮
	mybutton.Init(hInstance,IDB_BITMAP_BUTTON);
	mybutton.SetDevice(hdccanvas,hdcmem);
	mybutton.InitButton(6,BtRect);//按钮

	//时钟
	myclock.Init(m_hWnd,TIME_INFO);
	
	//初始化随机函数
	srand((unsigned)time(NULL));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSquareM1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSquareM1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		///////////////////////////////////////
		// 图像显示
		//初始化空图
		SelectObject(hdccanvas,hmapnull);
		//绘制
		gb.Show();
		//刷新屏幕
		BitBlt(pDCwindow->m_hDC,0,0,GAMEWIDTH,GAMEHEIGHT,hdccanvas,0,0,SRCCOPY);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSquareM1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSquareM1Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	gb.Check();
	//刷新窗口
	InvalidateRect(NULL,false);
	
	CDialog::OnTimer(nIDEvent);
}

void CSquareM1Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//鼠标移动
	gb.MouseMove(point.x,point.y);
	InvalidateRect(NULL,false);

	CDialog::OnMouseMove(nFlags, point);
}

void CSquareM1Dlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int iButton;
	//鼠标单击
	iButton=gb.LButtonUp(point.x,point.y);
	switch(iButton)
	{
	case BT_HELP:
		//操作说明
		dlgHelp.DoModal();
		break;


	case BT_SET:
		dlgSet.m_speed=gb.iSpeedSet;
		dlgSet.m_UseMagic=gb.iUseMagic;		
		//打开对话框
		dlgSet.DoModal();
		//刷新设置选项
		gb.iSpeedSet=dlgSet.m_speed;
		gb.iUseMagic=dlgSet.m_UseMagic;		
		break;
	}
	InvalidateRect(NULL,false);

	CDialog::OnLButtonUp(nFlags, point);
}

//在此处屏蔽一些按键
BOOL CSquareM1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message) 
	{
	case WM_KEYDOWN:
		//键盘处理
		gb.KeyProc(pMsg->wParam);				
		InvalidateRect(NULL,false);					

		//回车键,ESC键会关闭对话框，此处屏蔽，不能往下传。
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return 1;		
		}
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
