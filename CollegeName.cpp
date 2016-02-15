// CollegeName.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "CollegeName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollegeName dialog


CCollegeName::CCollegeName(CWnd* pParent /*=NULL*/)
	: CDialog(CCollegeName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCollegeName)
	m_collegename = _T("");
	//}}AFX_DATA_INIT
}


void CCollegeName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCollegeName)
	DDX_Text(pDX, IDC_COLLNAME, m_collegename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCollegeName, CDialog)
	//{{AFX_MSG_MAP(CCollegeName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollegeName message handlers
