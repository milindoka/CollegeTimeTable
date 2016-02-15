// ExpNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "ExpNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpNameDlg dialog


CExpNameDlg::CExpNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpNameDlg)
	m_fullname = _T("");
	m_shortnem = _T("");
	//}}AFX_DATA_INIT
}


void CExpNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpNameDlg)
	DDX_Text(pDX, IDC_FULLNEM, m_fullname);
	DDX_Text(pDX, IDC_SHORTNEM, m_shortnem);
	DDV_MaxChars(pDX, m_shortnem, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpNameDlg, CDialog)
	//{{AFX_MSG_MAP(CExpNameDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpNameDlg message handlers

void CExpNameDlg::OnNext() 
{ UpdateData(TRUE); 
  if(m_shortnem.IsEmpty()) return;
  if(NameIndex<=LastIndex)
  { ExpandedNames[NameIndex]=m_shortnem;
    ExpandedNames[NameIndex]+=m_fullname;
	
  }
  if(NameIndex==LastIndex) {ExpandedNames.Add("");LastIndex++;}
	NameIndex++;
    
	m_shortnem=ExpandedNames[NameIndex].Left(2);
    m_fullname=ExpandedNames[NameIndex].Mid(2);
	UpdateData(FALSE);

}

void CExpNameDlg::OnPrev() 
{ UpdateData(TRUE); 
  
  if(NameIndex>0)
  { ExpandedNames[NameIndex]=m_shortnem;
    ExpandedNames[NameIndex]+=m_fullname;
	NameIndex--;
  
	m_shortnem=ExpandedNames[NameIndex].Left(2);
    m_fullname=ExpandedNames[NameIndex].Mid(2);
	UpdateData(FALSE);
  }
	
}

BOOL CExpNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LastIndex=ExpandedNames.GetSize()-1;
    NameIndex=0;
	m_shortnem=ExpandedNames[NameIndex].Left(2);
	m_fullname=ExpandedNames[NameIndex].Mid(2);
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CExpNameDlg::PreTranslateMessage(MSG* pMsg) 
{
	
if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_NEXT) OnNext();
if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_PRIOR) OnPrev();	
	return CDialog::PreTranslateMessage(pMsg);
}


void CExpNameDlg::OnOK() 
{   UpdateData(TRUE);
	ExpandedNames[NameIndex]=m_shortnem;
    ExpandedNames[NameIndex]+=m_fullname;
	CDialog::OnOK();
}
