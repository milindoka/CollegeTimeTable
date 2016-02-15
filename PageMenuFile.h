#if !defined(AFX_PAGEMENUFILE_H__D476ACE0_806C_4A79_A1C5_79E78F8C5D99__INCLUDED_)
#define AFX_PAGEMENUFILE_H__D476ACE0_806C_4A79_A1C5_79E78F8C5D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMenuFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMenuFile dialog

class CPageMenuFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMenuFile)

// Construction
public:
	CPageMenuFile();
	~CPageMenuFile();

// Dialog Data
	//{{AFX_DATA(CPageMenuFile)
	enum { IDD = IDD_FILEHELP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMenuFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMenuFile)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMENUFILE_H__D476ACE0_806C_4A79_A1C5_79E78F8C5D99__INCLUDED_)
