// CollegeTimeTableDoc.cpp : implementation of the CCollegeTimeTableDoc class
//

#include "stdafx.h"
#include "CollegeTimeTable.h"

#include "CollegeTimeTableDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableDoc

IMPLEMENT_DYNCREATE(CCollegeTimeTableDoc, CDocument)

BEGIN_MESSAGE_MAP(CCollegeTimeTableDoc, CDocument)
	//{{AFX_MSG_MAP(CCollegeTimeTableDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableDoc construction/destruction

CCollegeTimeTableDoc::CCollegeTimeTableDoc()
{
	// TODO: add one-time construction code here

}

CCollegeTimeTableDoc::~CCollegeTimeTableDoc()
{
}

BOOL CCollegeTimeTableDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

 


/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableDoc serialization

void CCollegeTimeTableDoc::Serialize(CArchive& ar)
{
	
}

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableDoc diagnostics

#ifdef _DEBUG
void CCollegeTimeTableDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCollegeTimeTableDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableDoc commands
