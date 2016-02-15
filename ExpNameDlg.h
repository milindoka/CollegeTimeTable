#if !defined(AFX_EXPNAMEDLG_H__7DE776EB_403C_4B3F_AAA0_8C6F8E2E09BE__INCLUDED_)
#define AFX_EXPNAMEDLG_H__7DE776EB_403C_4B3F_AAA0_8C6F8E2E09BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExpNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExpNameDlg dialog

class CExpNameDlg : public CDialog
{
// Construction
public:
	int LastIndex;
	int NameIndex;
	CStringArray ExpandedNames; /// Expanded Names in the ??*****  Format eg MOMilind Oak
	CExpNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpNameDlg)
	enum { IDD = IDD_EXPNAMEDLG };
	CString	m_fullname;
	CString	m_shortnem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpNameDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpNameDlg)
	afx_msg void OnNext();
	afx_msg void OnPrev();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPNAMEDLG_H__7DE776EB_403C_4B3F_AAA0_8C6F8E2E09BE__INCLUDED_)
