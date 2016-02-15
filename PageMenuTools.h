#if !defined(AFX_PAGEMENUTOOLS_H__8DDA378A_CFDA_4B2C_9F49_67EB03950547__INCLUDED_)
#define AFX_PAGEMENUTOOLS_H__8DDA378A_CFDA_4B2C_9F49_67EB03950547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMenuTools.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMenuTools dialog

class CPageMenuTools : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMenuTools)

// Construction
public:
	CPageMenuTools();
	~CPageMenuTools();

// Dialog Data
	//{{AFX_DATA(CPageMenuTools)
	enum { IDD = IDD_TOOLSHELP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMenuTools)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMenuTools)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMENUTOOLS_H__8DDA378A_CFDA_4B2C_9F49_67EB03950547__INCLUDED_)
