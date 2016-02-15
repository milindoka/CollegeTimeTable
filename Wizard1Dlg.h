#if !defined(AFX_WIZARD1DLG_H__CB1E9870_1EDF_4260_9F7C_F86E9220B85F__INCLUDED_)
#define AFX_WIZARD1DLG_H__CB1E9870_1EDF_4260_9F7C_F86E9220B85F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizard1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizard1Dlg dialog

class CWizard1Dlg : public CDialog
{
public :
	CStringArray timeslots,classslots; ///

// Construction
public:
	CWizard1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWizard1Dlg)
	enum { IDD = IDD_WIZARD1 };
	CListBox	m_classslot;
	CListBox	m_timeslot;
	CString	m_newtime;
	CString	m_newclass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizard1Dlg)
	afx_msg void OnAddslot();
	afx_msg void OnAddclass();
	afx_msg void OnDeleteslot();
	afx_msg void OnDeleteclass();
	virtual void OnOK();
	afx_msg void OnSetfocusNewtime();
	afx_msg void OnSetfocusNewclass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARD1DLG_H__CB1E9870_1EDF_4260_9F7C_F86E9220B85F__INCLUDED_)
