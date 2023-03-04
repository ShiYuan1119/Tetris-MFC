
// DlgGameCode.cpp : implementation file


#include "stdafx.h"
#include "squareM1.h"
#include "DlgGameCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGameCode dialog


CDlgGameCode::CDlgGameCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGameCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGameCode)
	m_strGame = _T("");
	//}}AFX_DATA_INIT
}


void CDlgGameCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGameCode)
	DDX_Text(pDX, IDC_EDIT_GAME, m_strGame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGameCode, CDialog)
	//{{AFX_MSG_MAP(CDlgGameCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGameCode message handlers

BOOL CDlgGameCode::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	char chEnter[]={13,10,0};//回车字符
	/*char gameText[]="3D游戏："
"#仿CS游戏源码"
"#http://download.csdn.net/source/1124443 "
"#2D游戏："
"#俄罗斯方块源码(带烟花)"
"#http://download.csdn.net/source/1519525 "
"#挖金子修订版源码和文档"
"#http://download.csdn.net/source/1421628 "
"#超级玛丽制作揭秘文档"
"#http://download.csdn.net/source/808632 "
"#超级玛丽第一版源码"
"#http://download.csdn.net/source/497676 "
"#超级玛丽增强版源码"
"#http://download.csdn.net/source/584350 "
"#纸牌源码"
"#http://download.csdn.net/source/432977 "
"#挖金子第一版源码"
"#http://download.csdn.net/source/412278 ";*/

	m_strGame="";
	m_strGame.Replace("#",chEnter);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
