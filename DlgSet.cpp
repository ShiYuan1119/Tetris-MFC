
// DlgSet.cpp : implementation file


#include "stdafx.h"
#include "squareM1.h"
#include "DlgSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSet dialog


CDlgSet::CDlgSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSet)
	m_strSpeed = _T("");
	m_UseMagic = -1;
	//}}AFX_DATA_INIT
}


void CDlgSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSet)
	DDX_Text(pDX, IDC_TEXT_SPEED, m_strSpeed);
	DDX_Radio(pDX, IDC_RADIO_MAGIC, m_UseMagic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSet, CDialog)
	//{{AFX_MSG_MAP(CDlgSet)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_MAGIC, OnRadioMagic)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSet message handlers

void CDlgSet::OnButtonLeft() 
{
	// TODO: Add your control notification handler code here
	if(m_speed>1)
		m_speed--;
	m_strSpeed.Format("%d",m_speed);
	UpdateData(false);	
}

void CDlgSet::OnButtonRight() 
{
	// TODO: Add your control notification handler code here
	if(m_speed<9)
		m_speed++;
	m_strSpeed.Format("%d",m_speed);
	UpdateData(false);	
}

void CDlgSet::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_strSpeed.Format("%d",m_speed);
	UpdateData(false);
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgSet::OnRadioMagic() 
{
	// TODO: Add your control notification handler code here
	m_UseMagic=0;
	UpdateData(false);
}

void CDlgSet::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_UseMagic=1;
	UpdateData(false);	
}
