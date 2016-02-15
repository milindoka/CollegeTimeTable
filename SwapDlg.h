#if !defined(AFX_SWAPDLG_H__4856225C_A0D5_4040_85AD_C7222E3ADAA1__INCLUDED_)
#define AFX_SWAPDLG_H__4856225C_A0D5_4040_85AD_C7222E3ADAA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwapDlg dialog

class CSwapDlg : public CDialog
{
// Construction
public:
	CSwapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSwapDlg)
	enum { IDD = IDD_SWAPDLG };
	CString	m_tea1;
	CString	m_tea2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSwapDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWAPDLG_H__4856225C_A0D5_4040_85AD_C7222E3ADAA1__INCLUDED_)
