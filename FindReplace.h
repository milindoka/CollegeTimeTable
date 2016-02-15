#if !defined(AFX_FINDREPLACE_H__1942288F_1D65_4238_863C_0683A4D000A6__INCLUDED_)
#define AFX_FINDREPLACE_H__1942288F_1D65_4238_863C_0683A4D000A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindReplace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindReplace dialog

class CFindReplace : public CDialog
{
// Construction
public:
	CFindReplace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindReplace)
	enum { IDD = IDD_DIALOG1 };
	CString	m_replace;
	CString	m_find;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindReplace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindReplace)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDREPLACE_H__1942288F_1D65_4238_863C_0683A4D000A6__INCLUDED_)
