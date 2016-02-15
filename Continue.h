#if !defined(AFX_CONTINUE_H__ECD0D139_1D71_4F59_A04D_A175D8C3DD5E__INCLUDED_)
#define AFX_CONTINUE_H__ECD0D139_1D71_4F59_A04D_A175D8C3DD5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Continue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContinue dialog

class CContinue : public CDialog
{
// Construction
public:
	CContinue(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CContinue)
	enum { IDD = IDD_CONTINUE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContinue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CContinue)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTINUE_H__ECD0D139_1D71_4F59_A04D_A175D8C3DD5E__INCLUDED_)
