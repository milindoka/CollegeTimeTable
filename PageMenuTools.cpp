// PageMenuTools.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageMenuTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMenuTools property page

IMPLEMENT_DYNCREATE(CPageMenuTools, CPropertyPage)

CPageMenuTools::CPageMenuTools() : CPropertyPage(CPageMenuTools::IDD)
{
	//{{AFX_DATA_INIT(CPageMenuTools)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageMenuTools::~CPageMenuTools()
{
}

void CPageMenuTools::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMenuTools)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMenuTools, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMenuTools)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMenuTools message handlers
