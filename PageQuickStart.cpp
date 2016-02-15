// PageQuickStart.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageQuickStart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageQuickStart property page

IMPLEMENT_DYNCREATE(CPageQuickStart, CPropertyPage)

CPageQuickStart::CPageQuickStart() : CPropertyPage(CPageQuickStart::IDD)
{
	//{{AFX_DATA_INIT(CPageQuickStart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageQuickStart::~CPageQuickStart()
{
}

void CPageQuickStart::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageQuickStart)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageQuickStart, CPropertyPage)
	//{{AFX_MSG_MAP(CPageQuickStart)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageQuickStart message handlers
