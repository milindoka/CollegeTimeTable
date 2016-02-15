// HelpSheet.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "HelpSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpSheet

IMPLEMENT_DYNAMIC(CHelpSheet, CPropertySheet)

CHelpSheet::CHelpSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

AddPage(&intro);
AddPage(&quick);
AddPage(&menufile);
AddPage(&menuedit);
AddPage(&menuTools);
AddPage(&menuSet);
CWnd *pWnd = GetDlgItem( IDOK );
pWnd->ShowWindow( FALSE );



}

CHelpSheet::CHelpSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
AddPage(&intro);
AddPage(&quick);
AddPage(&menufile);
AddPage(&menuedit);
AddPage(&menuTools);
AddPage(&menuSet);

 


}

CHelpSheet::~CHelpSheet()
{
}


BEGIN_MESSAGE_MAP(CHelpSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CHelpSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpSheet message handlers

BOOL CHelpSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	CWnd *pWnd = GetDlgItem( IDCANCEL );
    pWnd->ShowWindow( FALSE );
    
	 pWnd = GetDlgItem( IDOK );
	
	pWnd->SetWindowText("Close Help");
	return bResult;
}
