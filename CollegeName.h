#if !defined(AFX_COLLEGENAME_H__D4C35A40_C61F_481A_9B05_F676ACAF1F7C__INCLUDED_)
#define AFX_COLLEGENAME_H__D4C35A40_C61F_481A_9B05_F676ACAF1F7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CollegeName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCollegeName dialog

class CCollegeName : public CDialog
{
// Construction
public:
	CCollegeName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCollegeName)
	enum { IDD = IDD_COLLEGENAME };
	CString	m_collegename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollegeName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCollegeName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLEGENAME_H__D4C35A40_C61F_481A_9B05_F676ACAF1F7C__INCLUDED_)
