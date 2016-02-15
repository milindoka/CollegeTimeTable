#if !defined(AFX_PAGEINTRODUCTION_H__3D330405_4AE0_42D5_8506_F1AEE8461974__INCLUDED_)
#define AFX_PAGEINTRODUCTION_H__3D330405_4AE0_42D5_8506_F1AEE8461974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageIntroduction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageIntroduction dialog

class CPageIntroduction : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageIntroduction)

// Construction
public:
	CPageIntroduction();
	~CPageIntroduction();

// Dialog Data
	//{{AFX_DATA(CPageIntroduction)
	enum { IDD = IDD_INRODUCTION };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageIntroduction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageIntroduction)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINTRODUCTION_H__3D330405_4AE0_42D5_8506_F1AEE8461974__INCLUDED_)
