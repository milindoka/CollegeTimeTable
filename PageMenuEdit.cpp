// PageMenuEdit.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageMenuEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMenuEdit property page

IMPLEMENT_DYNCREATE(CPageMenuEdit, CPropertyPage)

CPageMenuEdit::CPageMenuEdit() : CPropertyPage(CPageMenuEdit::IDD)
{
	//{{AFX_DATA_INIT(CPageMenuEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageMenuEdit::~CPageMenuEdit()
{
}

void CPageMenuEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMenuEdit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMenuEdit, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMenuEdit)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMenuEdit message handlers
