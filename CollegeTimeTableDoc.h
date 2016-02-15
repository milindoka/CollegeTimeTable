// CollegeTimeTableDoc.h : interface of the CCollegeTimeTableDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLEGETIMETABLEDOC_H__3638FB16_D105_4586_845F_CC0320BEB133__INCLUDED_)
#define AFX_COLLEGETIMETABLEDOC_H__3638FB16_D105_4586_845F_CC0320BEB133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "GridCtrl.h"


class CCollegeTimeTableDoc : public CDocument
{
protected: // create from serialization only
	CCollegeTimeTableDoc();
	DECLARE_DYNCREATE(CCollegeTimeTableDoc)

// Attributes
public:
    CString temp;
//	CGridCtrl m_master;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollegeTimeTableDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollegeTimeTableDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollegeTimeTableDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLEGETIMETABLEDOC_H__3638FB16_D105_4586_845F_CC0320BEB133__INCLUDED_)
