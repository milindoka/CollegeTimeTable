// PageMenuFile.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "PageMenuFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMenuFile property page

IMPLEMENT_DYNCREATE(CPageMenuFile, CPropertyPage)

CPageMenuFile::CPageMenuFile() : CPropertyPage(CPageMenuFile::IDD)
{
	//{{AFX_DATA_INIT(CPageMenuFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageMenuFile::~CPageMenuFile()
{
}

void CPageMenuFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMenuFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMenuFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMenuFile)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMenuFile message handlers
