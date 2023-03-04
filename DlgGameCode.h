#if !defined(AFX_DLGGAMECODE_H__B14ABECC_FBD6_4D82_8F3A_8651377E9FC3__INCLUDED_)
#define AFX_DLGGAMECODE_H__B14ABECC_FBD6_4D82_8F3A_8651377E9FC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGameCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGameCode dialog

class CDlgGameCode : public CDialog
{
// Construction
public:
	CDlgGameCode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGameCode)
	enum { IDD = IDD_DIALOG_GAMECODE };
	CString	m_strGame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGameCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGameCode)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGAMECODE_H__B14ABECC_FBD6_4D82_8F3A_8651377E9FC3__INCLUDED_)
