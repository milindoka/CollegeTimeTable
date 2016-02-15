// CollegeTimeTable.h : main header file for the COLLEGETIMETABLE application
//

#if !defined(AFX_COLLEGETIMETABLE_H__F937564C_4CDB_467A_80D4_56923B3C6D8D__INCLUDED_)
#define AFX_COLLEGETIMETABLE_H__F937564C_4CDB_467A_80D4_56923B3C6D8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableApp:
// See CollegeTimeTable.cpp for the implementation of this class
//

class CCollegeTimeTableApp : public CWinApp
{
public:
	CCollegeTimeTableApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollegeTimeTableApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCollegeTimeTableApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLEGETIMETABLE_H__F937564C_4CDB_467A_80D4_56923B3C6D8D__INCLUDED_)
