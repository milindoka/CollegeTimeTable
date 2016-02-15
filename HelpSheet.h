#if !defined(AFX_HELPSHEET_H__3AA06C4A_79CD_4069_B2D6_37C80AF0B1C5__INCLUDED_)
#define AFX_HELPSHEET_H__3AA06C4A_79CD_4069_B2D6_37C80AF0B1C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpSheet



#include "PageIntroduction.h"
#include "PageQuickStart.h"
#include "PageMenuFile.h"
#include "PageMenuEdit.h"

#include "PageMenuTools.h"
#include "PageMenuSet.h"




class CHelpSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CHelpSheet)

// Construction
public:

	CPageIntroduction intro;
    CPageQuickStart quick;
    CPageMenuFile   menufile;
    CPageMenuEdit   menuedit;
	CPageMenuTools  menuTools;
    CPageMenuSet    menuSet;

	
	CHelpSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CHelpSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHelpSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHelpSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPSHEET_H__3AA06C4A_79CD_4069_B2D6_37C80AF0B1C5__INCLUDED_)
