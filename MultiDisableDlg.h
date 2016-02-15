#if !defined(AFX_MULTIDISABLEDLG_H__C48511A8_2BD7_476B_BC57_C57F5B78B0CD__INCLUDED_)
#define AFX_MULTIDISABLEDLG_H__C48511A8_2BD7_476B_BC57_C57F5B78B0CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiDisableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiDisableDlg dialog

class CMultiDisableDlg : public CDialog
{
// Construction
public:
	CMultiDisableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiDisableDlg)
	enum { IDD = IDD_MULTIDISABLEDLG };
	CString	m_mdstring;
	CString	m_freezmsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiDisableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMultiDisableDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIDISABLEDLG_H__C48511A8_2BD7_476B_BC57_C57F5B78B0CD__INCLUDED_)
