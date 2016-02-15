// SwapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "SwapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwapDlg dialog


CSwapDlg::CSwapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSwapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSwapDlg)
	m_tea1 = _T("");
	m_tea2 = _T("");
	//}}AFX_DATA_INIT
}


void CSwapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSwapDlg)
	DDX_Text(pDX, IDC_TEA1, m_tea1);
	DDX_Text(pDX, IDC_TEA2, m_tea2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSwapDlg, CDialog)
	//{{AFX_MSG_MAP(CSwapDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwapDlg message handlers
