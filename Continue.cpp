// Continue.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "Continue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContinue dialog


CContinue::CContinue(CWnd* pParent /*=NULL*/)
	: CDialog(CContinue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContinue)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CContinue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContinue)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContinue, CDialog)
	//{{AFX_MSG_MAP(CContinue)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContinue message handlers

BOOL CContinue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(10,50,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CContinue::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(10);
	OnOK();
	
	CDialog::OnTimer(nIDEvent);
}

void CContinue::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CContinue::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(10);
	CDialog::OnCancel();
}
