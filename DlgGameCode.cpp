
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
	char chEnter[]={13,10,0};//�س��ַ�
	/*char gameText[]="3D��Ϸ��"
"#��CS��ϷԴ��"
"#http://download.csdn.net/source/1124443 "
"#2D��Ϸ��"
"#����˹����Դ��(���̻�)"
"#http://download.csdn.net/source/1519525 "
"#�ڽ����޶���Դ����ĵ�"
"#http://download.csdn.net/source/1421628 "
"#�����������������ĵ�"
"#http://download.csdn.net/source/808632 "
"#����������һ��Դ��"
"#http://download.csdn.net/source/497676 "
"#����������ǿ��Դ��"
"#http://download.csdn.net/source/584350 "
"#ֽ��Դ��"
"#http://download.csdn.net/source/432977 "
"#�ڽ��ӵ�һ��Դ��"
"#http://download.csdn.net/source/412278 ";*/

	m_strGame="";
	m_strGame.Replace("#",chEnter);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
