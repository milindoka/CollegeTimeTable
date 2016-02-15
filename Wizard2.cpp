// Wizard2.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "Wizard1Dlg.h"
#include "Wizard2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




extern CWizard1Dlg wiz;

/////////////////////////////////////////////////////////////////////////////
// CWizard2 dialog


CWizard2::CWizard2(CWnd* pParent /*=NULL*/)
	: CDialog(CWizard2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizard2)
	m_sub_tr = _T("");
	m_curclass = _T("");
	m_noflectures = 0;
	//}}AFX_DATA_INIT
}


void CWizard2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizard2)
	DDX_Control(pDX, IDC_CLASS, m_class);
	DDX_Text(pDX, IDC_SUBTR, m_sub_tr);
	DDX_CBString(pDX, IDC_CLASS, m_curclass);
	DDX_Text(pDX, IDC_NOFLECTURES, m_noflectures);
	DDV_MinMaxInt(pDX, m_noflectures, 1, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizard2, CDialog)
	//{{AFX_MSG_MAP(CWizard2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard2 message handlers

BOOL CWizard2::OnInitDialog() 
{ 

	CDialog::OnInitDialog();
	
     int i,classes;
    m_noflectures=1;
    classes=wiz.classslots.GetSize();

    for(i=0;i<classes;i++) m_class.AddString(wiz.classslots[i]);



	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
