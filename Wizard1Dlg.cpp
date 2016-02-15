// Wizard1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "collegetimetable.h"
#include "Wizard1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizard1Dlg dialog


CWizard1Dlg::CWizard1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWizard1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizard1Dlg)
	m_newtime = _T("");
	m_newclass = _T("");
	//}}AFX_DATA_INIT
}


void CWizard1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizard1Dlg)
	DDX_Control(pDX, IDC_CLASSSLOT, m_classslot);
	DDX_Control(pDX, IDC_TIMESLOT, m_timeslot);
	DDX_Text(pDX, IDC_NEWTIME, m_newtime);
	DDX_Text(pDX, IDC_NEWCLASS, m_newclass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizard1Dlg, CDialog)
	//{{AFX_MSG_MAP(CWizard1Dlg)
	ON_BN_CLICKED(IDC_ADDSLOT, OnAddslot)
	ON_BN_CLICKED(IDC_ADDCLASS, OnAddclass)
	ON_BN_CLICKED(IDC_DELETESLOT, OnDeleteslot)
	ON_BN_CLICKED(IDC_DELETECLASS, OnDeleteclass)
	ON_EN_SETFOCUS(IDC_NEWTIME, OnSetfocusNewtime)
	ON_EN_SETFOCUS(IDC_NEWCLASS, OnSetfocusNewclass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard1Dlg message handlers

void CWizard1Dlg::OnAddslot() 
{ CString temp;
  int n,i;
  UpdateData(TRUE);
  if(m_newtime.IsEmpty()) return;
  n=m_timeslot.GetCount();
  for(i=0;i<n;i++)
	{m_timeslot.GetText(i,temp); 
  if(m_newtime==temp) { MessageBox("The time slot is already present");return;}
	}
  m_timeslot.AddString(m_newtime);
  m_newtime.Empty();
  temp.Format("Total Time Slots : %d",n+1);
  SetDlgItemText(IDC_TOTALTIMESLOTS,temp);
  SetDefID(IDC_ADDSLOT);
  UpdateData(FALSE);
}

void CWizard1Dlg::OnAddclass() 
{ CString temp;
  int n,i;
  UpdateData(TRUE);
  if(m_newclass.IsEmpty()) return;
  n=m_classslot.GetCount();
  for(i=0;i<n;i++)
	{m_classslot.GetText(i,temp); 
  if(m_newclass==temp) { MessageBox("The class is already present");return;}
	}
  m_classslot.AddString(m_newclass);
  m_newclass.Empty();
  temp.Format("Total Classes : %d",n+1);
  SetDlgItemText(IDC_TOTALCLASSSLOTS,temp);
  SetDefID(IDC_ADDCLASS);
  UpdateData(FALSE);
}

void CWizard1Dlg::OnDeleteslot() 
{   CString temp;
	int idx=m_timeslot.GetCurSel();
	m_timeslot.DeleteString(idx);
    int n=m_timeslot.GetCount();
    temp.Format("Total Time Slots : %d",n);
    SetDlgItemText(IDC_TOTALTIMESLOTS,temp);	
}


void CWizard1Dlg::OnDeleteclass() 
{	CString temp;
	int idx=m_classslot.GetCurSel();
	m_classslot.DeleteString(idx);
    int n=m_classslot.GetCount();
    temp.Format("Total Classes : %d",n);
    SetDlgItemText(IDC_TOTALCLASSSLOTS,temp);	
}



void CWizard1Dlg::OnOK() 
{   
	timeslots.RemoveAll();
	classslots.RemoveAll();
	
	CString temp;
	int n=m_timeslot.GetCount();
    for(int i=0;i<n;i++)
	{m_timeslot.GetText(i,temp);
    timeslots.Add(temp);
	//MessageBox(temp);
	}

    n=m_classslot.GetCount();
    for(i=0;i<n;i++)
	{m_classslot.GetText(i,temp);
    classslots.Add(temp);
	}

	CDialog::OnOK();
}

void CWizard1Dlg::OnSetfocusNewtime() 
{
  SetDefID(IDC_ADDSLOT);
  UpdateData(FALSE);
	
}

void CWizard1Dlg::OnSetfocusNewclass() 
{
	// TODO: Add your control notification handler code here
  SetDefID(IDC_ADDCLASS);
  UpdateData(FALSE);	
}
