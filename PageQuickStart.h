#if !defined(AFX_PAGEQUICKSTART_H__7B52CF22_7E4C_4090_8641_9D1E50ED7245__INCLUDED_)
#define AFX_PAGEQUICKSTART_H__7B52CF22_7E4C_4090_8641_9D1E50ED7245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageQuickStart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageQuickStart dialog

class CPageQuickStart : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageQuickStart)

// Construction
public:
	CPageQuickStart();
	~CPageQuickStart();

// Dialog Data
	//{{AFX_DATA(CPageQuickStart)
	enum { IDD = IDD_QUICKSTART };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageQuickStart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageQuickStart)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEQUICKSTART_H__7B52CF22_7E4C_4090_8641_9D1E50ED7245__INCLUDED_)
