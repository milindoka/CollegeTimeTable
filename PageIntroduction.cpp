// PageIntroduction.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageIntroduction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageIntroduction property page

IMPLEMENT_DYNCREATE(CPageIntroduction, CPropertyPage)

CPageIntroduction::CPageIntroduction() : CPropertyPage(CPageIntroduction::IDD)
{
	//{{AFX_DATA_INIT(CPageIntroduction)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageIntroduction::~CPageIntroduction()
{
}

void CPageIntroduction::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageIntroduction)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageIntroduction, CPropertyPage)
	//{{AFX_MSG_MAP(CPageIntroduction)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageIntroduction message handlers
