// PageMenuSet.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageMenuSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMenuSet property page

IMPLEMENT_DYNCREATE(CPageMenuSet, CPropertyPage)

CPageMenuSet::CPageMenuSet() : CPropertyPage(CPageMenuSet::IDD)
{
	//{{AFX_DATA_INIT(CPageMenuSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageMenuSet::~CPageMenuSet()
{
}

void CPageMenuSet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMenuSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMenuSet, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMenuSet)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMenuSet message handlers
