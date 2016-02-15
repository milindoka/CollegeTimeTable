// MultiDisableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "MultiDisableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiDisableDlg dialog


CMultiDisableDlg::CMultiDisableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiDisableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiDisableDlg)
	m_mdstring = _T("");
	m_freezmsg = _T("");
	//}}AFX_DATA_INIT
}


void CMultiDisableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiDisableDlg)
	DDX_Text(pDX, IDC_MDSTRING, m_mdstring);
	DDX_Text(pDX, IDC_FRIZMSG, m_freezmsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiDisableDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiDisableDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiDisableDlg message handlers
