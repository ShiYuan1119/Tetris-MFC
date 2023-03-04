#if !defined(AFX_DLGSET_H__92306499_2AC1_439A_820D_5EDE2D700482__INCLUDED_)
#define AFX_DLGSET_H__92306499_2AC1_439A_820D_5EDE2D700482__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSet dialog

class CDlgSet : public CDialog
{
// Construction
public:
	int m_speed;
	CDlgSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSet)
	enum { IDD = IDD_DIALOG_SET };
	CString	m_strSpeed;
	int		m_UseMagic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSet)
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnPaint();
	afx_msg void OnRadioMagic();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSET_H__92306499_2AC1_439A_820D_5EDE2D700482__INCLUDED_)
