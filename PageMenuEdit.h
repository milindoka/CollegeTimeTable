#if !defined(AFX_PAGEMENUEDIT_H__BFC7E64D_1E08_4430_80C5_8A1CB796B50F__INCLUDED_)
#define AFX_PAGEMENUEDIT_H__BFC7E64D_1E08_4430_80C5_8A1CB796B50F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMenuEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMenuEdit dialog

class CPageMenuEdit : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMenuEdit)

// Construction
public:
	CPageMenuEdit();
	~CPageMenuEdit();

// Dialog Data
	//{{AFX_DATA(CPageMenuEdit)
	enum { IDD = IDD_EDITHELP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMenuEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMenuEdit)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMENUEDIT_H__BFC7E64D_1E08_4430_80C5_8A1CB796B50F__INCLUDED_)
