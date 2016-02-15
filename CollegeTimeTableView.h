// CollegeTimeTableView.h : interface of the CCollegeTimeTableView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLEGETIMETABLEVIEW_H__B6A8536B_F799_4FAA_A8F4_889057AA9999__INCLUDED_)
#define AFX_COLLEGETIMETABLEVIEW_H__B6A8536B_F799_4FAA_A8F4_889057AA9999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GridCtrl.h"

class CCollegeTimeTableView : public CFormView
{
protected: // create from serialization only
	CCollegeTimeTableView();
	DECLARE_DYNCREATE(CCollegeTimeTableView)

public:
	//{{AFX_DATA(CCollegeTimeTableView)
	enum { IDD = IDD_COLLEGETIMETABLE_FORM };
	CString	m_search;
	//}}AFX_DATA

// Attributes
public:
	void FastShow(int ti);
    void FastSetGapAndDoubleCount(int lasttimerow,int ti);
    void FastGenerateIndi(int ti); /// two letter Tr code
	void Bye();
//////Small tool tip kit
	int cxScr, cyScr;
	BOOL bToolTip;
    HWND hwndTT;      // handle to the ToolTip control	
	TOOLINFO ti;     // struct specifying info about tool in ToolTip control
	void DisplayToolTip();

/////End of Small Tool Tip Kit Variables
    
    int clashcount;
	int gapcount;
	//int maxgap;
	int dubcount;

	int  PrintType; ///0 for master,  1  for  individual, 2 for class
	int  LinesPerPage; ///depends on vertical printer length, default 35
 CStringArray tcodes; //// to collect all teacher codes for printing
 CStringArray AllClasses;
 CString ClashString;
 CString GapString;
 CString curpath;
 CString curfilename;
 CString college;
 CString DataBefore;
 CString DataAfter;

void Fill_AllClassesArray();
void  DisableBlueCells();
void  GetGlobalGapCount();
int   CreateClashReport();

void  DoPaginationForMaster(CDC* pDC,CPrintInfo* pInfo);
void  DoPaginationForIndi(CDC* pDC, CPrintInfo* pInfo);
void  DoPaginationForClass(CDC* pDC,CPrintInfo* pInfo);
void  ReduceGapForCell(int Ox,int Oy);
void  SetGapAndClashCount(int lasttimerow);
void  PrintOneClass(CDC* pDC); /// current class
void  DuplicateData(CString &Str);
void  PrintOne(CDC* pDC); /// current indi
void  Fill_AllIndividuals_in_tcodesArray();
void  CentreText(int y,CString str,CDC* pDC);
void  OnPrepareSinglePrint(CPrintInfo* pInfo);
void  PrintSingle(CDC* pDC,CPrintInfo* pInfo);
void  PrintMaster(CDC* pDC, CPrintInfo* pInfo);
void  PrintIndividual(CDC* pDC, CPrintInfo* pInfo);
void  PrintClass(CDC* pDC, CPrintInfo* pInfo);
void  GetParallelLectureList(CString str,CStringArray &arr);
void  DisplayGrid(CPoint tl,CPoint br,int rows,int cols,CDC* pDC);
void  GenerateClass(CString classcode);  //for ex FYJC-I
void  RefreshFormat();
void  GenerateIndividual(CString tcode);
CString PickTeacherCode(CString str); //return teacher code as XY
CString PickTeacherCode2(CString &str);//return teacher code and CUT the string
CString PickLectureTime(int row);
int FR_WithoutPrompt(CString one,CString two);

    CGridCtrl m_master;
	CGridCtrl m_indiv;
	CGridCtrl m_class;

	CCollegeTimeTableDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollegeTimeTableView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollegeTimeTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollegeTimeTableView)
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnGenerate();
	afx_msg void OnFilePrinttypeclasses();
	afx_msg void OnFilePrinttypeindividuals();
	afx_msg void OnFilePrinttypemaster();
	afx_msg void OnFileSevas();
	afx_msg void OnFileSev();
	afx_msg void OnFileLoad();
	afx_msg void OnFilenu();
	afx_msg void OnSetCollegename();
	afx_msg void OnEditInsertrow();
	afx_msg void OnEditDeleterow();
	afx_msg void OnAppExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFilePrintcurrent();
	afx_msg void OnEditFindandreplace();
	afx_msg void OnEditSwapteachers();
	afx_msg void OnEditDisablecell();
	afx_msg void OnToolsDisplaygapreport();
	afx_msg void OnToolsAutoreducegaps();
	afx_msg void OnToolsDisplayclashreport();
	afx_msg void OnEditDisablemultiplecells();
	afx_msg void OnEditEnableallcells();
	afx_msg void OnToolsTimetablewizard();
	afx_msg void OnToolsTimetablewizardstepII();
	afx_msg void OnSetFullnames();
	afx_msg void OnEditDefreezeOnString();
	afx_msg void OnEditSelectOnGivenString();
	afx_msg void OnToolsDisplaynextindividual();
	afx_msg void OnToolsDisplayprevindividual();
	afx_msg void OnToolsRefreshteacherandclasslists();
	afx_msg void OnToolsDisplaynextclass();
	afx_msg void OnToolsDisplayprevclass();
	afx_msg void OnToolsShowallcounts();
	afx_msg void OnHelpHowtousetimetable();
	afx_msg void OnHelpLoadsampetimetable();
	//}}AFX_MSG

	LONG CCollegeTimeTableView::OnDisplay(UINT wParam, LONG lparam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CollegeTimeTableView.cpp
inline CCollegeTimeTableDoc* CCollegeTimeTableView::GetDocument()
   { return (CCollegeTimeTableDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLEGETIMETABLEVIEW_H__B6A8536B_F799_4FAA_A8F4_889057AA9999__INCLUDED_)
