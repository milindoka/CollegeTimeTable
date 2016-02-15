#if !defined(AFX_WIZARD2_H__FF094054_53F3_4C5E_B9AB_DAA4C9CC0AE1__INCLUDED_)
#define AFX_WIZARD2_H__FF094054_53F3_4C5E_B9AB_DAA4C9CC0AE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizard2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizard2 dialog

class CWizard2 : public CDialog
{
// Construction
public:
    CStringArray classslots;

	CWizard2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWizard2)
	enum { IDD = IDD_WZARD2 };
	CComboBox	m_class;
	CString	m_sub_tr;
	CString	m_curclass;
	int		m_noflectures;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizard2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARD2_H__FF094054_53F3_4C5E_B9AB_DAA4C9CC0AE1__INCLUDED_)
