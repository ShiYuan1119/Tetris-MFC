
// DlgHelp.cpp : implementation file

#include "stdafx.h"
#include "squareM1.h"
#include "DlgHelp.h"

#include "DlgGameCode.h"

CDlgGameCode dlgGame;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHelp dialog


CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialog)
	//{{AFX_MSG_MAP(CDlgHelp)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_MOREGAME, OnButtonMoregame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHelp message handlers

void CDlgHelp::OnButtonOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CDlgHelp::OnButtonMoregame()
{
	// TODO: Add your control notification handler code here
	dlgGame.DoModal();
}
