#if !defined(AFX_PAGEMENUSET_H__AD51E5BB_E715_4DBF_A35F_85C5EF187704__INCLUDED_)
#define AFX_PAGEMENUSET_H__AD51E5BB_E715_4DBF_A35F_85C5EF187704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMenuSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMenuSet dialog

class CPageMenuSet : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMenuSet)

// Construction
public:
	CPageMenuSet();
	~CPageMenuSet();

// Dialog Data
	//{{AFX_DATA(CPageMenuSet)
	enum { IDD = IDD_SETHELP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMenuSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMenuSet)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMENUSET_H__AD51E5BB_E715_4DBF_A35F_85C5EF187704__INCLUDED_)
