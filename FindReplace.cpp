// FindReplace.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "FindReplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindReplace dialog


CFindReplace::CFindReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CFindReplace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindReplace)
	m_replace = _T("");
	m_find = _T("");
	//}}AFX_DATA_INIT
}


void CFindReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindReplace)
	DDX_Text(pDX, IDC_REPLACE, m_replace);
	DDX_Text(pDX, IDC_FIND, m_find);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindReplace, CDialog)
	//{{AFX_MSG_MAP(CFindReplace)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindReplace message handlers
