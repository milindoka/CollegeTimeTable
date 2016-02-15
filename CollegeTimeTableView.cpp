// CollegeTimeTableView.cpp : implementation of the CCollegeTimeTableView class
//
//#pragma warning(disable:4089)

#include "stdafx.h"
#include "CollegeTimeTable.h"

#include "CollegeTimeTableDoc.h"
#include "CollegeTimeTableView.h"

#include "CollegeName.h"


//#include <afxcoll.h>

#include "FindReplace.h"
#include "SwapDlg.h"
#include "MultiDisableDlg.h"
#include "Continue.h"
#include "Wizard1Dlg.h"
#include "Wizard2.h"
#include "ExpNameDlg.h"


#include "helpsheet.h"

//#include "afxtempl.h"

#define ROWS 300  // no. of rows in master
#define COLS 7    // no.of cols in master
#define RO 30     // no. of rows in individual/class

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////

CString IArr[150][RO][COLS];
int cc[150],dc[150],gc[150];



CFindReplace FR;
CSwapDlg SDlg;
CMultiDisableDlg mdd;
CWizard1Dlg wiz;
CWizard2 wiz2;
CExpNameDlg expand;
int DispIndexIndi=0;
int DispIndexClas=0;
int cellcount;
int TotalTrs=0;


COLORREF YELLOW=RGB(255,255,160);
COLORREF WHITE=RGB(255,255,255);
COLORREF RED=RGB(255,200,200);
COLORREF GREEN=RGB(200,255,200);
COLORREF BLACK=RGB(0,0,0);

int GlobalGapCount,GlobalClashCount,GlobalDubCount;


CContinue cont;

void pop(int ttt)
{ CString tmp;
  tmp.Format("%d",ttt);
  AfxMessageBox(tmp);
}



/////////Page Description Class ///////////////

class  CPage 
{public :
  CUIntArray Line;//stores line no.s of master that can be accomodated on single page
                  // first index is line of lecture time
 public :
  	CPage() {}
	~CPage(){}
    CPage& CPage::operator=(const CPage& ss){ Line.RemoveAll();	return *this;}
	/// This dummy overloaded operator is required in order to add an empty element
};


class CPrintPage
{public : 
 CStringArray Codes; /// Individuals or classes that can be accommodated
							////on a single page
public :
	CPrintPage(){}
	~CPrintPage(){}
	CPrintPage& CPrintPage::operator=(const CPrintPage& ss){ Codes.RemoveAll();	return *this;}
	/// This dummy overloaded operator is required in order to add an empty element
};

CArray <CPrintPage,CPrintPage&> ClassOrIndPageArray; // array containg print page
                                                     //description for ind or class

CArray <CPage,CPage&> PageArray;  ////array containg print description for master 



/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView

IMPLEMENT_DYNCREATE(CCollegeTimeTableView, CFormView)

BEGIN_MESSAGE_MAP(CCollegeTimeTableView, CFormView)
	//{{AFX_MSG_MAP(CCollegeTimeTableView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_COMMAND(ID_FILE_PRINTTYPECLASSES, OnFilePrinttypeclasses)
	ON_COMMAND(ID_FILE_PRINTTYPEINDIVIDUALS, OnFilePrinttypeindividuals)
	ON_COMMAND(ID_FILE_PRINTTYPEMASTER, OnFilePrinttypemaster)
	ON_COMMAND(ID_FILE_SEVAS, OnFileSevas)
	ON_COMMAND(ID_FILE_SEV, OnFileSev)
	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_COMMAND(ID_FILENU, OnFilenu)
	ON_COMMAND(ID_SET_COLLEGENAME, OnSetCollegename)
	ON_COMMAND(ID_EDIT_INSERTROW, OnEditInsertrow)
	ON_COMMAND(ID_EDIT_DELETEROW, OnEditDeleterow)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_PRINTCURRENT, OnFilePrintcurrent)
	ON_COMMAND(ID_EDIT_FINDANDREPLACE, OnEditFindandreplace)
	ON_COMMAND(ID_EDIT_SWAPTEACHERS, OnEditSwapteachers)
	ON_COMMAND(ID_EDIT_DISABLECELL, OnEditDisablecell)
	ON_COMMAND(ID_TOOLS_DISPLAYGAPREPORT, OnToolsDisplaygapreport)
	ON_COMMAND(ID_TOOLS_AUTOREDUCEGAPS, OnToolsAutoreducegaps)
	ON_COMMAND(ID_TOOLS_DISPLAYCLASHREPORT, OnToolsDisplayclashreport)
	ON_COMMAND(ID_EDIT_DISABLEMULTIPLECELLS, OnEditDisablemultiplecells)
	ON_COMMAND(ID_EDIT_ENABLEALLCELLS, OnEditEnableallcells)
	ON_COMMAND(ID_TOOLS_TIMETABLEWIZARD, OnToolsTimetablewizard)
	ON_COMMAND(ID_TOOLS_TIMETABLEWIZARDSTEPII, OnToolsTimetablewizardstepII)
	ON_COMMAND(ID_SET_FULLNAMES, OnSetFullnames)
	ON_COMMAND(ID_EDIT_DEFREEZE_ON_STRING, OnEditDefreezeOnString)
	ON_COMMAND(ID_EDIT_SELECTMAKEBLUECELLSCONTAINGGIVENSTRING, OnEditSelectOnGivenString)
	ON_COMMAND(ID_TOOLS_DISPLAYNEXTINDIVIDUAL, OnToolsDisplaynextindividual)
	ON_COMMAND(ID_TOOLS_DISPLAYPREVINDIVIDUAL, OnToolsDisplayprevindividual)
	ON_COMMAND(ID_TOOLS_REFRESHTEACHERANDCLASSLISTS, OnToolsRefreshteacherandclasslists)
	ON_COMMAND(ID_TOOLS_DISPLAYNEXTCLASS, OnToolsDisplaynextclass)
	ON_COMMAND(ID_TOOLS_DISPLAYPREVCLASS, OnToolsDisplayprevclass)
	ON_COMMAND(ID_TOOLS_SHOWALLCOUNTS, OnToolsShowallcounts)
	ON_COMMAND(ID_HELP_HOWTOUSETIMETABLE, OnHelpHowtousetimetable)
	ON_MESSAGE(WM_USER,OnDisplay)
	ON_COMMAND(ID_HELP_LOADSAMPETIMETABLE, OnHelpLoadsampetimetable)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView construction/destruction





CCollegeTimeTableView* g_GetView()
{
        return (CCollegeTimeTableView*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveView();
}

void MyGlobalFunc()
{
  g_GetView()->Bye();
}


void CCollegeTimeTableView::Bye()
{   //MessageBox("Bye");
	OnAppExit();
}

CCollegeTimeTableView::CCollegeTimeTableView()
	: CFormView(CCollegeTimeTableView::IDD)
{
	//{{AFX_DATA_INIT(CCollegeTimeTableView)
	m_search = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CCollegeTimeTableView::~CCollegeTimeTableView()
{
 }

void CCollegeTimeTableView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCollegeTimeTableView)
	DDX_Text(pDX, IDC_SEARCHBOX, m_search);
	//}}AFX_DATA_MAP
}

BOOL CCollegeTimeTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}


void CCollegeTimeTableView::OnInitialUpdate()
{ college="COLLEGE NAME";
	CString wdays[]={"MON","TUE","WED","THU","FRI","SAT"};
    LinesPerPage=46;
	PrintType=0;
	tcodes.SetSize(150); //// initial 150 teachers to avoid freq. mem alloc
    AllClasses.SetSize(20);
	PageArray.SetSize(100);  /// 100 pages, large enough to avoid mem alloc
	CRect rect(0,0,509,630);
	m_master.Create(rect,this, 21111);
	m_master.SetRowCount(ROWS);
	m_master.SetColumnCount(COLS);
	m_master.SetFixedRowCount();
	//m_master.SetFixedColumnCount();
	for(int i=1;i<7;i++)
	   { m_master.SetColumnWidth(i,68);
	     m_master.SetItemText(0,i,wdays[i-1]);
		 m_master.SetItemFormat(0,i-1,ES_CENTER | ES_UPPERCASE);
		}
	m_master.SetItemText(0,0,"MASTER");
	m_master.SetItemFormat(0,6,ES_CENTER | ES_UPPERCASE);
	   
    CRect rect1(509,80,1018,580);
    m_indiv.Create(rect1,this, 21112);
	m_indiv.SetEditable(FALSE);
	m_indiv.SetRowCount(RO);
	m_indiv.SetColumnCount(7);
	m_indiv.SetFixedRowCount();
	//m_indiv.SetFixedColumnCount();
	for(i=1;i<7;i++)
	   { m_indiv.SetColumnWidth(i,68);
	     m_indiv.SetItemText(0,i,wdays[i-1]);
		 m_indiv.SetItemFormat(0,i-1,ES_CENTER | ES_UPPERCASE | ES_READONLY);
		}
	
	m_indiv.SetColumnWidth(6,68);
	m_indiv.SetItemFormat(0,6,ES_CENTER | ES_UPPERCASE);

	m_indiv.SetColumnWidth(0,84);

 
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
 ResizeParentToFit();
 curfilename="Untitled";
 CFrameWnd* pfr=GetParentFrame();
 pfr->SetWindowText("College Time Table :  "+curfilename);
 DuplicateData(DataBefore);
 cxScr = GetSystemMetrics(SM_CXSCREEN)/2 - 150;
 cyScr = GetSystemMetrics(SM_CYSCREEN)/2;
 

}

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView printing

BOOL CCollegeTimeTableView::OnPreparePrinting(CPrintInfo* pInfo)
{

 switch(PrintType)  // 0 for master, 1 for individual, 2 for class
	{
	 //case 2: OnPrepareMasterPrint(pInfo);break;
	 case 3: OnPrepareSinglePrint(pInfo);break;
	}
 return DoPreparePrinting(pInfo);
}


void CCollegeTimeTableView::OnPrepareSinglePrint(CPrintInfo* pInfo)
{
}


void CCollegeTimeTableView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{

	//int Heightmm=pDC->GetDeviceCaps(VERTSIZE);
   //pop(Heightmm);
    ///double fff;
   
    //fff=Heightmm/6.46;
    //LinesPerPage=int(fff);	

 switch(PrintType)  // 0 for master, 1 for individual, 2 for class
	{case 0: DoPaginationForIndi(pDC,pInfo);break;
     case 1: DoPaginationForClass(pDC,pInfo);break;
	 case 2: DoPaginationForMaster(pDC,pInfo);break;
	 case 3: OnPrepareSinglePrint(pInfo);break;
	}

}

void CCollegeTimeTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{CFrameWnd* pfr=GetParentFrame();
 pfr->SetWindowText("College Time Table :  "+curfilename);

}

void CCollegeTimeTableView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{int lastindex;
 CString temp;

 for(lastindex=ROWS-1;lastindex>0;lastindex--)
   {temp=m_master.GetItemText(lastindex,0);if(!temp.IsEmpty()) break;}
 if(lastindex<=0) return; /////Empty Master !!!!


 switch(PrintType)  // 0 for master, 1 for individual, 2 for class 3 for single current
	{case 0: PrintIndividual(pDC,pInfo);break;
     case 1: PrintClass(pDC,pInfo);break;
	 case 2: PrintMaster(pDC,pInfo);break;
	 case 3: PrintSingle(pDC,pInfo);break;
	}
}

void CCollegeTimeTableView::PrintSingle(CDC* pDC, CPrintInfo* pInfo)
{
//UpdateData(TRUE);
 int i,j;
 CString temp;
 if(m_search.IsEmpty()) return;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{ temp=m_master.GetItemText(i,j);
		  if(temp.IsEmpty()) continue;
		  if(temp.Find(m_search)!=-1)
		  { if(j==0)
			{GenerateClass(m_search); PrintOneClass(pDC); return;}
            else
            { GenerateIndividual(m_search);
			  PrintOne(pDC);return;}
		  }
		}

}

void CCollegeTimeTableView::GetParallelLectureList(CString str,CStringArray &arr)
{ arr.RemoveAll();
  int idx;
  while((idx=str.Find(','))!=-1)
	{arr.Add(str.Left(idx));
     str=str.Mid(idx+1);
	 }
  arr.Add(str);
}
/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView diagnostics

#ifdef _DEBUG
void CCollegeTimeTableView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCollegeTimeTableView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCollegeTimeTableDoc* CCollegeTimeTableView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCollegeTimeTableDoc)));
	return (CCollegeTimeTableDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView message handlers



LONG CCollegeTimeTableView::OnDisplay(UINT wParam, LONG lparam)
{
	    CCellID cid=m_master.GetFocusCell();        
		int row=cid.row;
		int col=cid.col;
        CString temp=m_master.GetItemText(row,col);
		if(col==0) //if any class is selected
		{GenerateClass(temp);m_search=temp;UpdateData(FALSE);}
		///otherwise it is individual display
        else
		{ temp=PickTeacherCode(temp); m_search=temp;UpdateData(FALSE);GenerateIndividual(temp);	}
      
 return TRUE;
}

void CCollegeTimeTableView::OnEditCopy() 
{m_master.OnEditCopy();}

void CCollegeTimeTableView::OnEditCut() 
{m_master.OnEditCut();RefreshFormat();}

void CCollegeTimeTableView::OnEditPaste() 
{m_master.SetFocus();
 m_master.OnEditPaste();
 RefreshFormat();
}

void CCollegeTimeTableView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

CString CCollegeTimeTableView::PickTeacherCode(CString str)//return teacher code as XY
{int left=str.Find('(');                                   
 int rite=str.Find(')');
 if(left>rite) return "";
 return str.Mid(left+1,rite-left-1);
}

CString CCollegeTimeTableView::PickTeacherCode2(CString &str)//return teacher code and CUT
{int left=str.Find('(');                                    //  the string
 int rite=str.Find(')');
 if(left>rite) return "";
 CString temp=str.Mid(left+1,rite-left-1);
 CString temp2=str.Mid(rite+1);
 str=temp2;
 return temp;

}



CString CCollegeTimeTableView::PickLectureTime(int row)
{ CString temp;
	for(int i=row;i>=1;i--) // go through leftmost time column upwards
	{temp=m_master.GetItemText(i,0);
	 if(temp.IsEmpty()) continue;
	 if(temp[0]>='0' && temp[0]<='9') return temp;
	}
 return "?";
}

void CCollegeTimeTableView::SetGapAndClashCount(int lasttimerow)
{int i,j,k;
 int first,last;
 gapcount=0;dubcount=0;
 CString temp,temp1;
 for(j=1;j<7;j++)  ////through all six colums
	{   first=last=0;
    	 
		 for(i=1;i<=lasttimerow;i++)              ///first nonempty row index;
			{temp=m_indiv.GetItemText(i,j);
			if(temp.IsEmpty() || temp=="RECESS") continue; else {first=i;break;}
			}

   	 for(i=lasttimerow;i>0;i--)   ///last non-empty row index
		{temp=m_indiv.GetItemText(i,j);
	 if(temp.IsEmpty() || temp=="RECESS") continue; else {last=i; break;}
		}

     
     if(first==0) continue;  ////last has to be zero
     
	 ////now count gaps and also count double lectures

     for(i=first;i<=last;i++)
		{temp=m_indiv.GetItemText(i,j);
	     if(temp.IsEmpty() || temp=="RECESS") {gapcount++;continue;}
		 for(k=i+1;k<=last;k++)
			{temp1=m_indiv.GetItemText(k,j);
		 if(temp==temp1) dubcount++;

			}
		}

 }

}


void CCollegeTimeTableView::GenerateIndividual(CString tcode)
{int i,j,k,lastidx,syze;
 clashcount=0;
 gapcount=0;
 dubcount=0;
	CString temp,temp2,temp3="("+tcode+")",temp4,temptime,tempclash;
	CString timearr[RO]; //Max RO  lectures per day for an individual, index 1 to RO-1
 CStringArray entry;
	CUIntArray count;
	int TotalLectures=0; ///Workload,  0 in the beginning

    for(i=1;i<RO;i++)    /// Clean Individual timetable Area
		for(j=0;j<7;j++)
			{m_indiv.SetItemText(i,j,""); 
			 m_indiv.SetItemBkColour(i,j,WHITE);
			 m_indiv.RedrawCell(i,j);
			}
	
	m_indiv.SetItemText(0,0,""); m_indiv.RedrawCell(0,0); //clean topleft corner	
	
	if(tcode.IsEmpty()) return;


	lastidx=1;
	for(i=1;i<ROWS;i++)   ///Collect All Lecture Timings i.e all numerics in col 0
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue;
		 if(temp[0]>='0' && temp[0]<='9') 
			{ timearr[lastidx]=temp; if(j<RO-1) lastidx++; else  break;} 
		}  /// timearr contains all lecture timings 

	if(lastidx+1<RO) lastidx+=1;
	

	for(i=1;i<=lastidx;i++) {m_indiv.SetItemText(i,0,timearr[i]); m_indiv.RedrawCell(i,0);}
	
	int rowindex=0;
	for(i=1;i<ROWS;i++)
		for(j=1;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 k=temp.Find(temp3); ///find  (tcode) , teachercode encluding brackets
            if(temp.Find("//")!=-1)
               { temptime=PickLectureTime(i);
                 for(rowindex=1;rowindex<RO;rowindex++)
				                if(timearr[rowindex]==temptime)
                     { m_indiv.SetItemText(rowindex,3,"RECESS");
                       m_indiv.RedrawCell(rowindex,3);
                       break;
                      }                         
                }

		 if(k!=-1) /// if (tcode) found 
			{
			 temptime=PickLectureTime(i);
             
		   for(rowindex=1;rowindex<RO;rowindex++)
				  if(timearr[rowindex]==temptime)
					   { temp4=m_indiv.GetItemText(rowindex,j);//Get spot to check clash
				      temp2=m_master.GetItemText(i,0); // get class
					     temp2+="-"+temp.Mid(k-3,3); //attach subject
				      if(temp4.IsEmpty())  ///cell empty so no clash
					      m_indiv.SetItemText(rowindex,j,temp2);
					      else  //clash occurs
						     {temp4+=","; temp4+=temp2;
						      m_indiv.SetItemText(rowindex,j,temp4);
						      m_indiv.SetItemBkColour(rowindex,j,RED);//red
							  clashcount++;
					    	  }
					     m_indiv.RedrawCell(rowindex,j); //refresh class entry
					     ///	now add this entry to splitting chart
					     ////   i.e lecture entry & corresponding count
          syze=entry.GetSize();
          if(syze==-1) { entry.Add(temp2); count.Add(1); ///this is first entry
                      TotalLectures++; continue;
                     }
					      BOOL found=FALSE; // Set found=false
					    for(int k=0;k<syze;k++)
						     if(entry[k]==temp2) { count[k]++; found=TRUE; 
											                     	TotalLectures++;break;
												                    } //if entry already there count++
					        ////otherwise add entry and set count=1 for it
						  if(!found) {entry.Add(temp2);count.Add(1);TotalLectures++;}

					   }
			}
		}

         SetGapAndClashCount(lastidx);
		
		tempclash.Format("Clash Count : %d",clashcount);
		SetDlgItemText(IDC_CLASHCOUNT,tempclash);

        tempclash.Format("Double Count : %d",dubcount);
		SetDlgItemText(IDC_DUBCOUNT,tempclash);

		//MessageBox(tempclash);
		tempclash.Format("Gap Count : %d",gapcount);
		SetDlgItemText(IDC_GAPCOUNT,tempclash);
        
		syze=entry.GetSize();
		if(syze==0) return;
		for(k=0;k<syze;k++)
			{m_indiv.SetItemText(lastidx+k/3,1+2*(k%3),entry[k]);
			 m_indiv.RedrawCell(lastidx+k/3,1+2*(k%3));
			 temp.Format("%2d",count[k]);
			 m_indiv.SetItemText(lastidx+k/3,2+2*(k%3),temp);
			 m_indiv.RedrawCell(lastidx+k/3,2+2*(k%3));
			}
		temp.Format(" - %d",TotalLectures);
		tcode+=temp;
		m_indiv.SetItemText(0,0,tcode);
		m_indiv.RedrawCell(0,0);
}
		     
void CCollegeTimeTableView::RefreshFormat()
{ int i,j;
  CString temp;
  for (i=1;i<ROWS;i++)
	for(j=0;j<COLS;j++)  
	{ temp=m_master.GetItemText(i,j);
	if(temp[0]>='0' && temp[0]<='9') { m_master.SetItemBkColour(i,j,GREEN);m_master.RedrawCell(i,j);continue;}
	  if(m_master.GetItemBkColour(i,j)==YELLOW) ; //do nothing
	  else
	  m_master.SetItemBkColour(i,j,WHITE);
	   m_master.RedrawCell(i,j);continue;
	  }

}


void CCollegeTimeTableView::GenerateClass(CString classcode)  //for ex FYJC-I
{int i,j,k,l,syze,lastidx,paralect;	
 CString temp;
 CStringArray entry;
 CStringArray arr;
 CUIntArray count;
	CString timearr[RO],temptime; //Max RO lectures per day index 1 to RO-1
	j=1;

 for(i=1;i<RO;i++)    /// Clean Individual timetable Area
	 	for(j=0;j<7;j++)
		  	{m_indiv.SetItemText(i,j,"");
			   m_indiv.SetItemBkColour(i,j,WHITE);
		    m_indiv.RedrawCell(i,j);
			  }
    
	m_indiv.SetItemText(0,0,""); m_indiv.RedrawCell(0,0); //clean topleft corner
 if(classcode.IsEmpty()) return;
 if(classcode[0]>='0' && classcode[0]<='9') return; ///it is time entry NOT class

 j=1;
	for(i=1;i<ROWS;i++)   ///Collect All Lecture Timings i.e numerics in col 0
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue;
		 if(temp[0]>='0' && temp[0]<='9') { timearr[j]=temp; if(j<RO-1) j++; else  break;} 
		}
	
	for(i=1;i<RO;i++) {m_indiv.SetItemText(i,0,timearr[i]); m_indiv.RedrawCell(i,0);}
	
	m_indiv.SetItemText(0,0,classcode);
	m_indiv.RedrawCell(0,0);
	
	int rowindex=0;
	for(i=1;i<ROWS;i++)
		{ temp=m_master.GetItemText(i,0);
		  if(temp==classcode)  /// include this entry 
			   {temptime=PickLectureTime(i);
		     for(rowindex=1;rowindex<RO;rowindex++)  ///
				    if(timearr[rowindex]==temptime)
					      for(j=1;j<7;j++)
						        { m_indiv.SetItemText(rowindex,j,m_master.GetItemText(i,j));
						          m_indiv.RedrawCell(rowindex,j); //refresh class entry
        						}
			   }
  

    for(j=1;j<7;j++)
       {  temp=m_master.GetItemText(i,j);
          if(temp.Find("//")!=-1)
               { temptime=PickLectureTime(i);
                 for(rowindex=1;rowindex<RO;rowindex++)
				                if(timearr[rowindex]==temptime)
                     { m_indiv.SetItemText(rowindex,3,"RECESS");
                       m_indiv.RedrawCell(rowindex,3);
                       break;
                      }                         
                }
        }


		}

  
///Now fill Lecture Count Chart
int TotalLectures=0;
BOOL found;
for(lastidx=RO-1;lastidx>0;lastidx--)
   {temp=m_indiv.GetItemText(lastidx,0);
    if(!temp.IsEmpty()) break;
   }///Get Last Time-Rowo of index of Indiv in lastidx


//Now traverse all non-time cells
for(i=1;i<=lastidx;i++)
  for(j=1;j<7;j++)
    {temp=m_indiv.GetItemText(i,j);
     if(temp.IsEmpty()) continue;
     GetParallelLectureList(temp,arr);
     paralect=arr.GetUpperBound();
     if(paralect==-1) {MessageBox("Error in Class Generation"); return;}
     for(k=0;k<=paralect;k++)
        {//arr[k].TrimLeft();arr[k].TrimRight();
         if(arr[k].IsEmpty()) continue;
         syze=entry.GetUpperBound();
         if(syze==-1) { entry.Add(arr[k]); count.Add(1); ///this is first entry
                        TotalLectures++; continue;
                      }
         //check repeat count
         found=FALSE;
         for(l=0;l<=syze;l++)
            if(entry[l]==arr[k]) {found=TRUE; break;}
         if(found){ count[l]++;TotalLectures++;}
         else 
            {entry.Add(arr[k]); count.Add(1);TotalLectures++;}
         
         }
     }
  lastidx+=2;  


syze=entry.GetSize();
		if(syze==0) return;
		for(k=0;k<syze;k++)
			{m_indiv.SetItemText(lastidx+k/3,1+2*(k%3),entry[k]);
			 m_indiv.RedrawCell(lastidx+k/3,1+2*(k%3));
			 temp.Format("%2d",count[k]);
			 m_indiv.SetItemText(lastidx+k/3,2+2*(k%3),temp);
			 m_indiv.RedrawCell(lastidx+k/3,2+2*(k%3));
			}
		temp.Format(" - %d",TotalLectures);
		classcode+=temp;
		m_indiv.SetItemText(0,0,classcode);
		m_indiv.RedrawCell(0,0);
}

void CCollegeTimeTableView::OnGenerate() 
{UpdateData(TRUE);
 int i,j;
 CString temp;
 if(m_search.IsEmpty()) return;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 if(temp.Find(m_search)!=-1)
		 { if(j==0)
            GenerateClass(m_search);
            else
            { GenerateIndividual(m_search);
			 }

		  return;
		 }
		}
}

void CCollegeTimeTableView::DisplayGrid(CPoint tl,CPoint br,int rows,int cols,CDC* pDC)
{  CPen pPen,*pPenold;
   pPen.CreatePen(PS_SOLID,1,BLACK);
   pPenold=pDC->SelectObject(&pPen);
   
          int xn=(br.x-tl.x)/cols;
	      int yn=(br.y-tl.y)/rows;  
          for(int i=0;i<=cols;i++)
           { pDC->MoveTo(tl.x+i*xn,tl.y);
             pDC->LineTo(tl.x+i*xn,br.y);
           }
		  
          for(i=0;i<=rows;i++)   
            {pDC->MoveTo(tl.x,tl.y+i*yn);
             pDC->LineTo(br.x,tl.y+i*yn);
            } 
      pDC->SelectObject(pPenold);
     //  pDC->SelectObject(pOldBrush);          
}


void CCollegeTimeTableView::CentreText(int y,CString str,CDC* pDC)
{CSize tt;
 tt=pDC->GetTextExtent(str);
 int xx=70+(700-tt.cx)/2;
 pDC->TextOut(xx,y,str);
}


void CCollegeTimeTableView::PrintMaster(CDC* pDC, CPrintInfo* pInfo)
{  int j,k,height,maxheight;
	UINT line;
   CString temp;
   CStringArray arr;
   
   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");

   oldfont=pDC->SelectObject(&fon); 

   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   CPoint PP(70,-25);
   CPoint QQ(771,-25);
   CPoint tempPP,tempQQ;
   if(pInfo->m_nCurPage==1) CentreText(-25,college,pDC);
   int LineCounter=0;
   UINT lastline=PageArray[(pInfo->m_nCurPage)-1].Line.GetUpperBound();///
   for(line=0;line<=lastline;line++)
   { maxheight=1;
	    for(j=0;j<7;j++)
		    { tempPP=PP;//tempQQ=QQ;
		       temp=m_master.GetItemText(PageArray[(pInfo->m_nCurPage)-1].Line[line],j);
		       if(temp[0]>='0' && temp[0]<='9')
		         {PP.Offset(0,-25); 
		          pDC->TextOut(74+100,PP.y-2,"    MON");
		          pDC->TextOut(74+200,PP.y-2,"    TUE");
		          pDC->TextOut(74+300,PP.y-2,"    WED");
		          pDC->TextOut(74+400,PP.y-2,"    THU");
		          pDC->TextOut(74+500,PP.y-2,"    FRI");
		          pDC->TextOut(74+600,PP.y-2,"    SAT");
   		       tempPP=PP;QQ.Offset(0,-25);  /////create blank space between lecture blocks
		         }
        GetParallelLectureList(temp,arr);// in CStringarray arr
        height=arr.GetSize();
		      if(height<1) height=1;
		      if(height>maxheight) maxheight=height;
		      for(k=0;k<height;k++)
			       {pDC->TextOut(74+j*100,PP.y-2,arr[k]);  PP.Offset(0,-25); }
       PP=tempPP;//Reset to normal lecture line
		     } //end of j=0 loop
		   QQ.Offset(0,-25*maxheight);
		   DisplayGrid(PP,QQ,1,7,pDC);
	  	 PP.Offset(0,-25*maxheight);
   }  /// end of line=0 loop  
pDC->SelectObject(&oldfont); 
}  /// end of PrintMaster fn

void CCollegeTimeTableView::DoPaginationForMaster(CDC* pDC,CPrintInfo* pInfo)
{pInfo->SetMinPage(1);
 CString temp;//,temp2;
 CStringArray arr;
 arr.SetSize(20);   //// for parallel lecture splitting in diff strings
 int height,maxheight,i,j;
 int LineCounter=0,PageIndex=0;
 PageArray.RemoveAll();   ////// Reset Page Description Array
 CPage tempage;
 PageArray.Add(tempage);

 for(int lastindex=ROWS-1;lastindex>0;lastindex--)
	{temp=m_master.GetItemText(lastindex,0); if(!temp.IsEmpty()) break;}
 if(lastindex<=0) return; /////Empty Master !!!!
 if(lastindex<1) lastindex=1;

 for(i=1;i<=lastindex;i++) ////// Preapre Page Description
	{maxheight=1;
	 temp=m_master.GetItemText(i,0);
     if(temp.IsEmpty()) continue;
   //temp2=m_master.GetItemText(i,1);
   //if(
	if(temp[0]>='0' && temp[0]<='9') 
		maxheight=2; // for lecture time skip one line
	for(j=1;j<7;j++)
	{temp=m_master.GetItemText(i,j);
	 GetParallelLectureList(temp,arr);// Get Parallel lectures in CStringarray arr
     height=arr.GetSize();
	 if(height<1) height=1;
	 if(height>maxheight) maxheight=height; ///max cell height,>1 for parallel lectures
	}
     if((LineCounter+maxheight)<LinesPerPage) /// check whether line(s) fit in page
		{LineCounter+=maxheight; //if yes, include lines
	     PageArray[PageIndex].Line.Add(i); continue;  ///go for more lines on page
		}
	 PageIndex++;   /// otherwise Page is Full, go for next page
	 PageArray.Add(tempage);///Create Empty Page Struct
	 LineCounter=maxheight;  /// include current line(s)
	 PageArray[PageIndex].Line.Add(i);
	}
	pInfo->SetMaxPage(PageIndex+1);///Max Page no. can now be set
}


///////------------------------------------------------------------------------
///////          Printing Individual Time Tables
///////------------------------------------------------------------------------



void CCollegeTimeTableView::Fill_AllIndividuals_in_tcodesArray()
{ CString temp,temp2;
  tcodes.RemoveAll();   ////Reset teacher codes list
  CStringArray paralist; /// collect all sharing(llel) lecture entries
  BOOL found;
  int i,j,k,l,paratotal;
  for(i=1;i<ROWS;i++)   ///traverse through master
	 for(j=1;j<7;j++)
		{temp=m_master.GetItemText(i,j);
	     if(temp.IsEmpty()) continue;
		 GetParallelLectureList(temp,paralist);
         paratotal=paralist.GetUpperBound();
		 if(paratotal==-1) { MessageBox("Improper Entry"); continue;}
         for(k=0;k<=paratotal;k++)
			{temp2=PickTeacherCode(paralist[k]);
		     found=FALSE;
		     for(l=0;l<tcodes.GetSize();l++)
				 if(tcodes[l]==temp2){found=TRUE;break;}
				 if(!found) tcodes.Add(temp2);
			}
		}
 int II=tcodes.GetSize();
   for(j=1;j<II;j++)
	   for(i=0;i<j;i++)
		   if(tcodes[i]>tcodes[j]) {temp=tcodes[i];tcodes[i]=tcodes[j];tcodes[j]=temp;}
	if(tcodes[0].IsEmpty()) tcodes.RemoveAt(0);
}

void CCollegeTimeTableView::PrintOneClass(CDC* pDC)
{int i,j,k,height,maxheight,lastindex,firstindex;
//  	UINT codeidx;
   CString temp;
   CStringArray arr;
   arr.SetSize(20);
   
   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");

   oldfont=pDC->SelectObject(&fon); 

   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   CPoint PP(70,-5);
   CPoint QQ(771,-5);
   CPoint tempPP,tempQQ;

   int LineCounter=0;

  

   for(firstindex=0;firstindex<RO;firstindex++) 
	   for(j=1;j<7;j++)          /// Get first non-empty row index
		{temp=m_indiv.GetItemText(firstindex,j);if(!temp.IsEmpty()) goto GotFirstIndex;
		}

   
GotFirstIndex :

   if(firstindex>RO-1)firstindex=RO-1;
  
   for(lastindex=RO-1;lastindex>=firstindex;lastindex--) /// Get last time-cell  index
		{temp=m_indiv.GetItemText(lastindex,0);if(!temp.IsEmpty()) break;}
         CentreText(PP.y,college,pDC);
         PP.Offset(0,-25); 
		 QQ.Offset(0,-25);
        for(i=firstindex;i<=lastindex;i++)
			{ maxheight=1;
			  for(j=0;j<7;j++)
				{ tempPP=PP;tempQQ=QQ;
		          temp=m_indiv.GetItemText(i,j);
				  GetParallelLectureList(temp,arr);// in CStringarray arr
		          height=arr.GetSize();
		          if(height<1) height=1;
		          if(height>maxheight) maxheight=height;
		          for(k=0;k<height;k++)
			        {pDC->TextOut(74+j*100,PP.y-2,arr[k]);
		             PP.Offset(0,-25);
			         }
                  PP=tempPP;//Reset to normal lecture line
				}///end loop for(j=0
		     QQ.Offset(0,-25*maxheight);
		     DisplayGrid(PP,QQ,1,7,pDC);
		     PP.Offset(0,-25*maxheight);
		} ///end loop for(codeidx=0
       PP.Offset(0,-25);
       QQ.Offset(0,-25);
     //}  ///end of loop for(i=0

pDC->SelectObject(&oldfont);

}

void CCollegeTimeTableView::PrintOne(CDC* pDC)
{  int j,k;
   CString temp,temp1,temp3;
   int lastindex,firstindex;
   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");
   oldfont=pDC->SelectObject(&fon); 
   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   pDC->SelectStockObject(NULL_BRUSH);

   CPoint PP(70,-5);
   CPoint QQ(771,-30);
   int ee=expand.ExpandedNames.GetSize();
   if(ee>0)
	 for(j=0;j<ee;j++) if (expand.ExpandedNames[j].Left(2)==m_search) {temp3=expand.ExpandedNames[j].Mid(2); break;} 
  
   temp=college;
	 temp+=" : ";
	 temp+=temp3;
     temp1.Format(" : [CC:%d][GC:%d][DC:%d]",clashcount,gapcount,dubcount);
	 temp+=temp1;
	 
     pDC->TextOut(PP.x,PP.y,temp);

for(firstindex=1;firstindex<RO;firstindex++) 
	   for(j=1;j<7;j++)          /// Get first non-empty row index
		{temp=m_indiv.GetItemText(firstindex,j);if(!temp.IsEmpty()) goto GotFirstNonemptyRow;
		}

   
GotFirstNonemptyRow :
     if(firstindex>RO-1) firstindex=RO-1;

	 for(lastindex=RO-1;lastindex>0;lastindex--) /// Get last time-cell  index
			    { temp=m_indiv.GetItemText(lastindex,0);if(!temp.IsEmpty()) break;}
      int lastindex1=lastindex;

	  for(j=lastindex;j>0;j--)
			for(k=1;k<7;k++)
			{ temp=m_indiv.GetItemText(j,k);
			 if(!temp.IsEmpty()) goto lastcell;}
				 
	  lastcell : 
	  lastindex=j;

int LineCounter=0;
     
      
      PP.Offset(0,-25); 
		    QQ.Offset(0,-25);
      pDC->TextOut(74+100,PP.y-2,"    MON");
		    pDC->TextOut(74+200,PP.y-2,"    TUE");
		    pDC->TextOut(74+300,PP.y-2,"    WED");
		    pDC->TextOut(74+400,PP.y-2,"    THU");
		    pDC->TextOut(74+500,PP.y-2,"    FRI");
		    pDC->TextOut(74+600,PP.y-2,"    SAT");
      DisplayGrid(PP,QQ,1,7,pDC);
      pDC->TextOut(74,PP.y-2,m_indiv.GetItemText(0,0));
   
		    for(j=firstindex;j<=lastindex;j++)
			      { PP.Offset(0,-25); 
		         QQ.Offset(0,-25);
			        for(k=0;k<7;k++)
				         { temp=m_indiv.GetItemText(j,k);
				           pDC->TextOut(74+k*100,PP.y-2,temp);//print cell text
				         }
			        DisplayGrid(PP,QQ,1,7,pDC); ///Print each row with enclosing grid
			       }
    //// now print lecture counts
		    QQ.Offset(0,-12); ///keep some spacing
		    PP.Offset(0,-30); //// slight lower the top-left for count box 
		    BOOL FirstLine=TRUE;
		    //PP=QQ;
		    //lastindex+=2;///locate lecture count part in individual
			
		    lastindex=lastindex1+2;///locate lecture count part in individual
		    for(j=lastindex;j<RO;j++)
			      { temp=m_indiv.GetItemText(j,1);
		         if(temp.IsEmpty()) break;     ///if end of counts then stop
			        if(!FirstLine) QQ.Offset(0,-25); //else next line,  no spacing for top table 
			        temp1=m_indiv.GetItemText(j,2);
			        temp=temp+" -"+temp1;///make one convenient string to print
           pDC->TextOut(74+1*100,QQ.y-2,temp);//print cell text
			        temp=m_indiv.GetItemText(j,3);
		         if(temp.IsEmpty()) break;///if end of counts
			        temp1=m_indiv.GetItemText(j,4);
			        temp=temp+" -"+temp1;///make one convenient string to print
           pDC->TextOut(74+3*100,QQ.y-2,temp);//print cell text
			        temp=m_indiv.GetItemText(j,5);
		         if(temp.IsEmpty()) break;///if end of counts
			        temp1=m_indiv.GetItemText(j,6);
			        temp=temp+" -"+temp1;///make one convenient string to print
             pDC->TextOut(74+5*100,QQ.y-2,temp);//print cell text
			    			 FirstLine=FALSE;  ///now allow next line spacing on top
			      }
       QQ.Offset(0,-25);  //next line
       DisplayGrid(PP,QQ,1,1,pDC);
    			QQ.Offset(0,-25);  ///leave gap between two individuals
			    PP.y=QQ.y;
			   QQ.Offset(0,-25);
//		  } ///end of loop codeidx = 0...
pDC->SelectObject(&oldfont); 
  
}

				 

void CCollegeTimeTableView::PrintIndividual(CDC* pDC,CPrintInfo* pInfo)
{ int j,k,ee;
  UINT codeidx;
   CString temp,temp1,temp3;
   int lastindex,firstindex;
   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");

   oldfont=pDC->SelectObject(&fon); 

   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   pDC->SelectStockObject(NULL_BRUSH);

   CPoint PP(70,-3);
   CPoint QQ(771,-28);
	
  ee=expand.ExpandedNames.GetSize();
int LineCounter=0;
   UINT lastcode=ClassOrIndPageArray[(pInfo->m_nCurPage)-1].Codes.GetUpperBound();///
   for(codeidx=0;codeidx<=lastcode;codeidx++)
   { 
	 temp3=ClassOrIndPageArray[(pInfo->m_nCurPage)-1].Codes[codeidx];
	 GenerateIndividual(temp3);
     if(ee>0)
	 for(j=0;j<ee;j++) if (expand.ExpandedNames[j].Left(2)==temp3) {temp3=expand.ExpandedNames[j].Mid(2); break;} 
     temp=college;
	 temp+=" : ";
	 temp+=temp3;
     temp1.Format(" : [CC:%d][GC:%d][DC:%d]",clashcount,gapcount,dubcount);
	 temp+=temp1;
	 

     pDC->TextOut(PP.x,PP.y,temp);
     
   
   for(firstindex=1;firstindex<RO;firstindex++) 
	   for(j=1;j<7;j++)          /// Get first non-empty row index
		{temp=m_indiv.GetItemText(firstindex,j);if(!temp.IsEmpty()) goto GotFirstNonempty;
		}

   
GotFirstNonempty :
     if(firstindex>RO-1) firstindex=RO-1;



	 for(lastindex=RO-1;lastindex>0;lastindex--) /// Get last time-cell  index
			    { temp=m_indiv.GetItemText(lastindex,0);if(!temp.IsEmpty()) break;}
      int lastindex1=lastindex;
	  for(j=lastindex;j>0;j--)
			for(k=1;k<7;k++)
			{ temp=m_indiv.GetItemText(j,k);
			 if(!temp.IsEmpty()) goto lastcell;}
				 
	  lastcell : 
	  lastindex=j;
      //CentreText(PP.y,college,pDC);

	  
      PP.Offset(0,-25); 
		    QQ.Offset(0,-25);
    
    
      pDC->TextOut(74+100,PP.y-2,"    MON");
		    pDC->TextOut(74+200,PP.y-2,"    TUE");
		    pDC->TextOut(74+300,PP.y-2,"    WED");
		    pDC->TextOut(74+400,PP.y-2,"    THU");
		    pDC->TextOut(74+500,PP.y-2,"    FRI");
		    pDC->TextOut(74+600,PP.y-2,"    SAT");
      DisplayGrid(PP,QQ,1,7,pDC);
	
	   
      pDC->TextOut(74,PP.y-2,m_indiv.GetItemText(0,0));
   
		    for(j=firstindex;j<=lastindex;j++)
			      { PP.Offset(0,-25); 
		         QQ.Offset(0,-25);
			        for(k=0;k<7;k++)
				         { temp=m_indiv.GetItemText(j,k);
				           pDC->TextOut(74+k*100,PP.y-2,temp);//print cell text
				         }
			        DisplayGrid(PP,QQ,1,7,pDC); ///Print each row with enclosing grid
			       }
		    BOOL FirstLine=TRUE;
		    lastindex=lastindex1+2;///locate lecture count part in individual
		    for(j=lastindex;j<RO;j++)
			      { temp=m_indiv.GetItemText(j,1);
		         if(temp.IsEmpty()) break;     ///if end of counts then stop
			        if(!FirstLine) QQ.Offset(0,-25); //else next line,  no spacing for top table 
			        temp1=m_indiv.GetItemText(j,2);
			        temp=temp+" -"+temp1;///make one convenient string to print
           pDC->TextOut(74+1*100,QQ.y-2,temp);//print cell text
			        temp=m_indiv.GetItemText(j,3);
		         if(temp.IsEmpty()) break;///if end of counts
			        temp1=m_indiv.GetItemText(j,4);
			        temp=temp+" -"+temp1;///make one convenient string to print
           pDC->TextOut(74+3*100,QQ.y-2,temp);//print cell text
			        temp=m_indiv.GetItemText(j,5);
		         if(temp.IsEmpty()) break;///if end of counts
			        temp1=m_indiv.GetItemText(j,6);
			        temp=temp+" -"+temp1;///make one convenient string to print
             pDC->TextOut(74+5*100,QQ.y-2,temp);//print cell text
			    			 FirstLine=FALSE;  ///now allow next line spacing on top
			      }
       QQ.Offset(0,-25);  //next line
       DisplayGrid(PP,QQ,1,1,pDC);
    			QQ.Offset(0,-25);  ///leave gap between two individuals
			    PP.y=QQ.y;
			   QQ.Offset(0,-25);
		  } ///end of loop codeidx = 0...
pDC->SelectObject(&oldfont); 
}

///////------------------------------------------------
///////          Printing Class Time Tables
///////------------------------------------------------


void CCollegeTimeTableView::DoPaginationForClass(CDC* pDC,CPrintInfo* pInfo)
{//LinesPerPage=46;
 CString temp;
 pInfo->SetMinPage(1);
 int i,j,k,l,rowheight,height,lastindex,LineCounter,ClassHeight;
 
 BOOL found;
 CStringArray arr;        /// array to store parallel lectures
 arr.SetSize(20);         /// max 20 lectures before mem allocation
  /// Collect All Classes (***Do not Allow Duplicates) 
 ClassOrIndPageArray.RemoveAll();   ////// Reset Page Description Array
 CPrintPage tempage;
 ClassOrIndPageArray.Add(tempage);  /// now PageIndex is 0  (for first page)
 int PageIndex=0;

 for(i=1;i<ROWS;i++)      /// All classes are in the first column of the master
	{temp=m_master.GetItemText(i,0);
     if(temp.IsEmpty()) continue;               /// skip empty cells
	 if(temp[0]>='0' && temp[0]<='9') continue; /// and also skip time cells
     
	 k=AllClasses.GetSize();
	
	 if(k==0)  {AllClasses.Add(temp);continue;} ///initial entry
	
	 found=FALSE;
     for(j=0;j<k;j++)
		if(temp==AllClasses[j]) {found=TRUE; break;}
		  ///// if no duplicate class found then add
		if(!found) AllClasses.Add(temp); 
	}
  ///start pagination for class printouts
  k=AllClasses.GetSize();
  LineCounter=0;   ///initialize line count, it should be maximum but < LinesPerPage
  
  for(i=0;i<k;i++)
  { GenerateClass(AllClasses[i]);
    for(lastindex=RO-1;lastindex>0;lastindex--)
		     {temp=m_indiv.GetItemText(lastindex,0); 
		      if(temp.IsEmpty()) continue; else break; 
		     }
       //if(lastindex<=0) return; /////Empty Class !!!!
       ClassHeight=1;
	   for(j=1;j<=lastindex;j++)
			{ rowheight=1;
              for(l=1;l<7;l++)
			     {temp=m_indiv.GetItemText(j,l);///Examine each cell for height
  	              if(temp.IsEmpty()) continue;  ///Height will be >1 for sharing lectures
    	          GetParallelLectureList(temp,arr);// Get Parallel lectures in CStringarray arr
                  height=arr.GetSize();
				  if(height<1) {rowheight=1;break;}
	              if(height>rowheight) rowheight=height; ///max cell height,>1 for parallel lectures
				}///end of l=1 loop
				ClassHeight+=rowheight;
			}////end of j=1 loop
		 ClassHeight+=3;///for college title  + Weekday line + Seperation
		 LineCounter+=ClassHeight;
		 //pop(LineCounter);
	    if(LineCounter<LinesPerPage) 
			{//LineCounter+=ClassHeight; /// this class time table fits in page 
		    //	CString tmp;
			// tmp.Format("%d",LineCounter);
			//MessageBox(tmp);
			ClassOrIndPageArray[PageIndex].Codes.Add(AllClasses[i]);
            LineCounter++; continue; ///Add line before next class & go for more classes
			}

		//{CString tmp;
         //tmp.Format("%d",LineCounter);
		 //MessageBox(tmp);}

 	     /// otherwise Page is Full, go for next page
	   ClassOrIndPageArray.Add(tempage);///Create Empty Page Struct
	   LineCounter=ClassHeight;  /// Set Line Counter for the next page
	   PageIndex++;
	   ClassOrIndPageArray[PageIndex].Codes.Add(AllClasses[i]); ///Add class
	  // pop(PageIndex);
       
    ////loop ends...go for more classes.... top of loop
  }  
  
  pInfo->SetMaxPage(PageIndex+1);  /// set maximum page count
  //pop(PageIndex);
}

void CCollegeTimeTableView::PrintClass(CDC* pDC,CPrintInfo* pInfo)
{  int i,j,k,height,maxheight,lastindex;
  	UINT codeidx;
   CString temp;
   CStringArray arr;
   arr.SetSize(20);
  
   
   //pop(pInfo->m_nCurPage);

   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");

   oldfont=pDC->SelectObject(&fon); 

   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   CPoint PP(70,-3);
   CPoint QQ(771,-3);
   CPoint tempPP,tempQQ;
  
   int LineCounter=0;
   UINT lastcode=ClassOrIndPageArray[(pInfo->m_nCurPage)-1].Codes.GetUpperBound();///
   for(codeidx=0;codeidx<=lastcode;codeidx++)
   { GenerateClass(ClassOrIndPageArray[(pInfo->m_nCurPage)-1].Codes[codeidx]);
     for(lastindex=RO-1;lastindex>0;lastindex--) /// Get last time-cell  index
			    {temp=m_indiv.GetItemText(lastindex,0);if(!temp.IsEmpty()) break;}
     
    CentreText(PP.y,college,pDC);
    
	PP.Offset(0,-25); 
	QQ.Offset(0,-25);

     for(i=0;i<=lastindex;i++)
	     { maxheight=1;
		   for(j=0;j<7;j++)
		      { tempPP=PP;tempQQ=QQ;
		        temp=m_indiv.GetItemText(i,j);
                GetParallelLectureList(temp,arr);// in CStringarray arr
                height=arr.GetSize();
		        if(height<1) height=1;
		        if(height>maxheight) maxheight=height;
				if(i==0 || j==0) maxheight=1;
		        for(k=0;k<height;k++)
			        {pDC->TextOut(74+j*100,PP.y-2,arr[k]);
		             PP.Offset(0,-25);
			         }
                PP=tempPP;//Reset to normal lecture line
				}///end loop for(j=0
		     QQ.Offset(0,-25*maxheight);
		     DisplayGrid(PP,QQ,1,7,pDC);
			 //MessageBox("!");
		     PP.Offset(0,-25*maxheight);

       } ///end loop for(codeidx=0
       PP.Offset(0,-25);
       QQ.Offset(0,-25);
     }  ///end of loop for(i=0

pDC->SelectObject(&oldfont);
} //end classprint

void CCollegeTimeTableView::OnFilePrinttypeclasses() 
{ PrintType=1; PostMessage(WM_COMMAND,ID_FILE_PRINT,0); 
}

void CCollegeTimeTableView::OnFilePrinttypeindividuals() 
{ PrintType=0; PostMessage(WM_COMMAND,ID_FILE_PRINT,0); 
}

void CCollegeTimeTableView::OnFilePrinttypemaster() 
{PrintType=2; PostMessage(WM_COMMAND,ID_FILE_PRINT,0); 
}

void CCollegeTimeTableView::OnFileSevas() 
{
	// TODO: Add your command handler code here
		CFileDialog cfd(FALSE,"tit","*.tit");
 CString filename;
    if(cfd.DoModal()==IDOK)
	{ CString token="TimeTable";
	  //college="College Name";
	  CString filepath=cfd.GetPathName();
   filename=cfd.GetFileName();
	  CFile thefile;
	  CFileException exc;
      thefile.Open(filepath,CFile::modeCreate | CFile::modeWrite,&exc);
      CArchive archive(&thefile,CArchive::store);
       
        int i,j;
        int totnames=expand.ExpandedNames.GetSize();
		CString temp;
		COLORREF tempcolour;
		archive<<token
		       <<college;    //// college name
        for (i=1;i<ROWS;i++)
			for(j=0;j<COLS;j++)  
			{ temp=m_master.GetItemText(i,j);
			  tempcolour=m_master.GetItemBkColour(i,j);
			  archive<<temp<<tempcolour;

			}
		archive	<<totnames;  //// total expanded names
        for(i=0;i<totnames;i++) archive<<expand.ExpandedNames[i];
   curpath=filepath;	
   curfilename=filename;
   CFrameWnd* pfr=GetParentFrame();
   pfr->SetWindowText("College Time Table :  "+filename);
	}
 DuplicateData(DataBefore);
}
void CCollegeTimeTableView::OnFileSev() 
{if(curpath.IsEmpty()) { OnFileSevas(); return;}

 m_master.Down();

 


 CString token="TimeTable";
 CFile thefile;
 CFileException exc;
 thefile.Open(curpath,CFile::modeCreate | CFile::modeWrite,&exc);
 CArchive archive(&thefile,CArchive::store);
       
        int i,j;
		int totnames=expand.ExpandedNames.GetSize();
		CString temp;
		COLORREF tempcolour;
		archive<<token
		       <<college;
        for (i=1;i<ROWS;i++)
			for(j=0;j<COLS;j++)  
			{ temp=m_master.GetItemText(i,j);
			  tempcolour=m_master.GetItemBkColour(i,j);
			  archive<<temp<<tempcolour;
			}
     archive<<totnames;  //// total expanded names
        for(i=0;i<totnames;i++) archive<<expand.ExpandedNames[i];
 DuplicateData(DataBefore);
 DisplayToolTip();
 SetTimer(1,3000,NULL);
	}

void CCollegeTimeTableView::OnFileLoad() 
{
	// TODO: Add your command handler code here
CFileDialog cfd(TRUE,"tit","*.tit");
    if(cfd.DoModal()==IDOK)
	{ CString token;
	  CString filepath=cfd.GetPathName();
   CString filename=cfd.GetFileName();
	  CFile thefile;
	  CFileException exc;

	  thefile.Open(filepath,CFile::modeRead,&exc);
     CArchive archive(&thefile,CArchive::load);
       
        int i,j,totnames;

		CString temp;
        COLORREF colref;
        
		archive>>token
		       >>college;
        for (i=1;i<ROWS;i++)
			for(j=0;j<COLS;j++)  
			{ archive>>temp;
		      archive>>colref;
			  m_master.SetItemText(i,j,temp);
		      m_master.SetItemBkColour(i,j,colref);
			}
			expand.ExpandedNames.RemoveAll();
		archive	>> totnames;  //// total expanded names
		
        for(i=0;i<totnames;i++) { archive>>temp;expand.ExpandedNames.Add(temp);}
    	RefreshFormat();
		OnToolsRefreshteacherandclasslists();
		archive.Close();
		thefile.Close();
  	
curpath=filepath;
curfilename=filename;
CFrameWnd* pfr=GetParentFrame();
 pfr->SetWindowText("College Time Table :  "+filename);
 DuplicateData(DataBefore);
	}
RefreshFormat();
}


void CCollegeTimeTableView::OnFilenu() 
{ int i,j; 



 for(i=1;i<RO;i++)    /// Clean Individual timetable Area
		for(j=0;j<7;j++)
			{m_indiv.SetItemText(i,j,""); 
			 m_indiv.SetItemBkColour(i,j,WHITE);
			 m_indiv.RedrawCell(i,j);
			}
	
	m_indiv.SetItemText(0,0,""); m_indiv.RedrawCell(0,0); //clean topleft corner	




  for(i=1;i<ROWS;i++)    /// Clean Master timetable Area
		  for(j=0;j<7;j++)
			{m_master.SetItemText(i,j,""); 
			 m_master.SetItemBkColour(i,j,WHITE);
			 m_master.RedrawCell(i,j);
			}
curpath="";
curfilename="Untitled";
CFrameWnd* pfr=GetParentFrame();
pfr->SetWindowText("College Time Table :  "+curfilename);

}

void CCollegeTimeTableView::OnSetCollegename() 
{CCollegeName ccn;
 ccn.m_collegename=college;
 if(ccn.DoModal()==IDOK)
  {college=ccn.m_collegename;}
	
}




void CCollegeTimeTableView::OnEditInsertrow() 
{CCellID cid;
 cid=m_master.GetFocusCell();
 //CString tmp;
 // tmp.Format("%d",cid.row);
 //MessageBox(tmp);
if(cid.row==-1) return;
int i,j;
CString tmp;
for(i=ROWS-1;i>=cid.row;i--)
    for(j=0;j<7;j++)
       { tmp=m_master.GetItemText(i,j);
         m_master.SetItemText(i+1,j,tmp);
         m_master.RedrawCell(i+1,j);
        }
for(j=0;j<7;j++)                        ///make current row empty
   {m_master.SetItemText(cid.row,j,"");
   m_master.RedrawCell(cid.row,j);
   }
   RefreshFormat();
}

void CCollegeTimeTableView::OnEditDeleterow() 
{CCellID cid;
 cid=m_master.GetFocusCell();
 //CString tmp;
 // tmp.Format("%d",cid.row);
 //MessageBox(tmp);
if(cid.row==-1) return;
int i,j;
CString tmp;
for(i=cid.row;i<ROWS-1;i++)
    for(j=0;j<7;j++)
       { tmp=m_master.GetItemText(i+1,j);
         m_master.SetItemText(i,j,tmp);
         m_master.RedrawCell(i,j);
        }
for(j=0;j<7;j++)                        ///make last row empty
   {m_master.SetItemText(ROWS-1,j,"");
   m_master.RedrawCell(ROWS-1-1,j);
   }
   RefreshFormat();
}
void CCollegeTimeTableView::DuplicateData(CString &Str) /// Backup Master Before or After
{CString temp;
 Str.Empty();
 int i,j;
  for(i=1;i<ROWS;i++)
    for(j=0;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
         Str+=temp;
		 }
	//MessageBox(Str);
}


void CCollegeTimeTableView::OnAppExit() 
{ int ans;
  DuplicateData(DataAfter);
  //MessageBox(DataAfter);
  if(DataBefore!=DataAfter)
      { ans=MessageBox("Time Table Modified. Save Changes ?","College Time Table",MB_YESNOCANCEL | MB_ICONQUESTION);
        if(ans==IDNO) goto quit;
        if(ans==IDCANCEL) return;
        OnFileSev();
        goto quit;
    ////PostMeExitInstance();
        
      }  
    quit :
 PostMessage(WM_QUIT);
 //OnFileExit();
	}

BOOL CCollegeTimeTableView::PreTranslateMessage(MSG* pMsg) 
{   
	
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN)) 
	{   //CWnd* pdlg=GetDlgItem(IDC_SEARCHBOX);
        //pdlg->GetWindowText(m_search);
		OnGenerate();
		return TRUE;
	}      
	
	return CFormView::PreTranslateMessage(pMsg);
}


void CCollegeTimeTableView::DisplayToolTip()
{
 CString m_text="   The Time Table File Has Been Updated   ";
	if (!bToolTip)
	{
		unsigned int uid = 0;       // for ti initialization

		// CREATE A TOOLTIP WINDOW
		hwndTT = CreateWindowEx(WS_EX_TOPMOST,
								TOOLTIPS_CLASS,
								NULL,
								TTS_NOPREFIX | TTS_ALWAYSTIP,		
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								NULL,
								NULL,
								NULL,
								NULL
							   );

// INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
	
		
//changing tool tip font
//Great idea and it works. The code is:
//CToolTipCtrl tool;
//tool.Create(this);
//CFont *f = tool.GetFont();
//LOGFONT pLogFont;
//f-&gt;GetLogFont(&pLogFont);
//m_fontText.CreateFontIndirect(&pLogFont);
//Thank you


		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_TRACK;
		ti.hwnd = NULL;
		ti.hinst = NULL;
		ti.uId = uid;
		ti.lpszText = (LPSTR)(LPCSTR) m_text;		
        // ToolTip control will cover the whole window
		ti.rect.left = 0;
		ti.rect.top = 0;
		ti.rect.right = 0;
		ti.rect.bottom = 0;

		// SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW
		::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);

		::SendMessage(hwndTT, TTM_TRACKPOSITION, 0, (LPARAM)(DWORD) MAKELONG(cxScr,cyScr));
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO) &ti);
		
		bToolTip=TRUE;
	}
	else
	{
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO) &ti);
	
		bToolTip=FALSE;
	}
}
 

void CCollegeTimeTableView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==1) { DisplayToolTip(); KillTimer(1); }
	
	
	CFormView::OnTimer(nIDEvent);
}

void CCollegeTimeTableView::OnFilePrintcurrent() 
{PrintType=3; PostMessage(WM_COMMAND,ID_FILE_PRINT,0); 
	
}

void CCollegeTimeTableView::OnEditFindandreplace() 
{
  CString temp;
  int totaloccur=0;
  again :
  if(FR.DoModal()==IDOK)
  { if(FR.m_find.IsEmpty() || FR.m_replace.IsEmpty()) { MessageBox("Empty String"); goto again;}
   
    totaloccur=FR_WithoutPrompt(FR.m_find,FR.m_replace);
  }
  temp.Format("Replaced %d Occurrences",totaloccur);
  MessageBox(temp);
}


int CCollegeTimeTableView::FR_WithoutPrompt(CString one,CString two)
{
  int occur;
  CString temp;
  int totaloccur=0;
	int i,j; 
    for(i=1;i<ROWS;i++)    
		  for(j=0;j<7;j++)
			{temp=m_master.GetItemText(i,j); 
		     occur=0;
		     occur=temp.Replace(one,two);
			 if(occur) { m_master.SetItemText(i,j,temp); totaloccur+=occur;
						 m_master.RedrawCell(i,j);
						}
			}
   return totaloccur;
 }


void CCollegeTimeTableView::OnEditSwapteachers() 
{   
  CString temp;
  CString t1="(";
  CString t2="(";

  again:
  
  if(SDlg.DoModal()==IDOK)
  { if(SDlg.m_tea1.IsEmpty() || SDlg.m_tea2.IsEmpty()) { MessageBox("Empty String"); goto again;}
     
    t1+=SDlg.m_tea1; t1+=")";
    t2+=SDlg.m_tea2; t2+=")";
	FR_WithoutPrompt(t1,"@!#@");
    FR_WithoutPrompt(t2,t1);
	FR_WithoutPrompt("@!#@",t2);
	temp.Format("Swapped %s and %s", SDlg.m_tea1,SDlg.m_tea2);
    MessageBox(temp);
  }
  
	
}

void CCollegeTimeTableView::OnEditDisablecell() 
{   
    
	CCellID cid=m_master.GetFocusCell();        
    COLORREF TEMP=m_master.GetItemBkColour(cid.row,cid.col);
	if(TEMP==YELLOW) TEMP=WHITE; else TEMP=YELLOW;
    m_master.SetItemBkColour(cid.row,cid.col,TEMP);
    m_master.RedrawCell(cid.row,cid.col);
	
	  DisableBlueCells();
}


void CCollegeTimeTableView::GetGlobalGapCount()
{int i,j;
 GlobalGapCount=0; 
 GlobalClashCount=0;
 GlobalDubCount=0;
 
 CString temp;
 Fill_AllIndividuals_in_tcodesArray();  // tcodes array contains all teacher names
 j=tcodes.GetSize();
 
 for(i=0;i<j;i++)
	{FastGenerateIndi(i);
	 GlobalGapCount+=gapcount;
	 GlobalClashCount+=clashcount;
	 GlobalDubCount+=dubcount;
	}
 //GapString.Format("Gap Count : %d , Continue ?",GlobalGapCount);
}



void CCollegeTimeTableView::OnToolsDisplaygapreport() 
{
 CStringArray GapRecord;
 int i,j,maxindex;
 GlobalGapCount=0; 
 CString temp,dispstr;
 Fill_AllIndividuals_in_tcodesArray();  // tcodes array contains all teacher names
 j=tcodes.GetSize();
 
 for(i=0;i<j;i++)
	{FastGenerateIndi(i);
     temp.Format("[%02d : %s]",gapcount,tcodes[i]);
	 GapRecord.Add(temp);
	 //dispstr+=temp;
	 GlobalGapCount+=gapcount;
	 
	}
///sort gaprecords
maxindex=GapRecord.GetUpperBound();
for(i=0;i<maxindex;i++)
  for(j=i+1;j<=maxindex;j++)
   if(GapRecord[i]>GapRecord[j]) 
	{temp=GapRecord[i];
	 GapRecord[i]=GapRecord[j];
	 GapRecord[j]=temp;
   }

   for(i=0;i<=maxindex;i++)
   {dispstr+=GapRecord[i];if((i+1)%10==0) dispstr+="\n";}
 temp.Format("\n\nGlobal Gap Count : %d",GlobalGapCount);
 dispstr+=temp;
MessageBox(dispstr);

}


int CCollegeTimeTableView::CreateClashReport()
{int i,j;
 GlobalClashCount=0; 
 CString temp;
 ClashString.Empty();
 Fill_AllIndividuals_in_tcodesArray();  // tcodes array contains all teacher names
 j=tcodes.GetSize();
 
 for(i=0;i<j;i++)
	{FastGenerateIndi(i);
     
     if(clashcount==0) continue;
     temp.Format("[%02d : %s]",clashcount,tcodes[i]);
	 ClashString+=temp;
	 GlobalClashCount+=clashcount;
	 if((i+1)%10==0) ClashString+="\n";
	}
 temp.Format("\n\nGlobal Clash Count : %d",GlobalClashCount);
 ClashString+=temp;

return GlobalClashCount;

}

void CCollegeTimeTableView::OnToolsDisplayclashreport() 
{CreateClashReport();
 MessageBox(ClashString); 

}



void CCollegeTimeTableView::OnEditDisablemultiplecells() 
{ 
  mdd.m_freezmsg="Enter String to Freeze Multiple Cells";	
 if(mdd.DoModal()!=IDOK) return;
 int i,j;
 CString temp;
 
 if(mdd.m_mdstring.IsEmpty()) return;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 if(temp.Find(mdd.m_mdstring)!=-1) ///string found, make YELLOW
		 { m_master.SetItemBkColour(i,j,YELLOW);m_master.RedrawCell(i,j);}
		}

//RefreshFormat();
	
}




void CCollegeTimeTableView::OnEditEnableallcells() 
{int i,j;
 COLORREF tempcolour;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{  tempcolour=m_master.GetItemBkColour(i,j);
		   if(tempcolour==YELLOW)
		   {m_master.SetItemBkColour(i,j,WHITE);
		    m_master.RedrawCell(i,j);
		   }
		}
}

void CCollegeTimeTableView::DisableBlueCells() 
{ int i,j;
  COLORREF tempcolour;
  UINT cellstate;
	for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{    cellstate=m_master.GetItemState(i,j);
		     if(cellstate==GVNI_SELECTED || cellstate==GVIS_DROPHILITED)
				{ tempcolour=m_master.GetItemBkColour(i,j);
		     if(tempcolour==YELLOW) m_master.SetItemBkColour(i,j,WHITE);
				 else 	 m_master.SetItemBkColour(i,j,YELLOW); 
				  m_master.SetItemState(i,j,0);
                  m_master.RedrawCell(i,j);
				}
			      
		}
}


void CCollegeTimeTableView::DoPaginationForIndi(CDC* pDC, CPrintInfo* pInfo)
{
	
 int test;	
	
 CString temp,temp1;
 pInfo->SetMinPage(1);
 int i,j,k,l,height,lastindex,lastime,LineCounter;

 ClassOrIndPageArray.RemoveAll();   ////// Reset Page Description Array
 CPrintPage tempage;                /////  To add empty object
 ClassOrIndPageArray.Add(tempage);  /// now PageIndex is 0  (for first page)
 int PageIndex=0;
 Fill_AllIndividuals_in_tcodesArray();  // tcodes array contains all teacher names
     
  ///start pagination for individual printouts
  k=tcodes.GetSize();
  
  LineCounter=0;   ///initialize line count, it should be maximum but < LinesPerPage

  for(i=0;i<k;i++)
  { GenerateIndividual(tcodes[i]);
    for(lastindex=RO-1;lastindex>0;lastindex--)
		     {temp=m_indiv.GetItemText(lastindex,1); 
		      if(temp.IsEmpty()) continue; else break; 
		     }
    if(lastindex<=0) continue; /////Empty Indi !!!!
	///find last time cell
    for(lastime=RO-1;lastime>0;lastime--)
		     {temp=m_indiv.GetItemText(lastindex,0); 
		      if(temp.IsEmpty()) continue; else break; 
		     }
	for(j=lastime;j>0;j--)
			for(l=1;l<7;l++)
			{ temp=m_indiv.GetItemText(j,l);
			 if(!temp.IsEmpty()) goto stop;}
				 
	  stop : 
	  lastindex=lastindex - lastime + j;
	  

    height=lastindex+1; ///seperation, recess, title-SIWS, Weekday line

 //{
 //   CString tmp;
 //   tmp.Format("%d",height);
 //   MessageBox(tmp);
//	  }
    test=LineCounter+height;
	//pop(test);

    if(test<LinesPerPage) 
        {LineCounter+=height; /// this individual time table fits in page 
         //pop(LineCounter);
		 //pop(LinesPerPage);
         ClassOrIndPageArray[PageIndex].Codes.Add(tcodes[i]);
         LineCounter++; continue; ///Add line before next indi & go for more indi's
        }
 	   /// otherwise Page is Full, go for next page
	   ClassOrIndPageArray.Add(tempage);///Create Empty Page Struct
	   PageIndex++;
	   ClassOrIndPageArray[PageIndex].Codes.Add(tcodes[i]); ///Add indi to next page
		LineCounter=height;  /// Set Line Counter for the next page
    ////loop ends...go for more individuals... top of loop
  }  
     
  pInfo->SetMaxPage(PageIndex+1);  /// set maximum page count

}

void CCollegeTimeTableView::OnToolsTimetablewizard() 
{   CString temp;
    int times,classes,i,j,rowcounter=1;
	if(wiz.DoModal()==IDOK) 
	{ times=wiz.timeslots.GetSize();
      classes=wiz.classslots.GetSize();
    
      for(i=0;i<times;i++)
	  { m_master.SetItemText(rowcounter,0,wiz.timeslots[i]);
	    m_master.SetItemBkColour(rowcounter,0,GREEN);
	    m_master.RedrawCell(rowcounter,0);

	    rowcounter++;
		  for(j=0;j<classes;j++)
		  {m_master.SetItemText(rowcounter,0,wiz.classslots[j]);
		   m_master.RedrawCell(rowcounter,0);
           rowcounter++;
		  }
        rowcounter++;  ///sepearation by an empty row
	  }
	}

}

void CCollegeTimeTableView::OnToolsTimetablewizardstepII() 
{int i,j,lecturecounter;
 CString tempclass,tempentry;
 while(wiz2.DoModal()==IDOK)  ///Keep allocating lectures
	{lecturecounter=wiz2.m_noflectures;
	
	 for(i=2;i<ROWS;i++)
		{if(lecturecounter<=0) break;
		 
		 tempclass=m_master.GetItemText(i,0);
		 
		 if(tempclass==wiz2.m_curclass)
		   for(j=1;j<7;j++)
				{ if(lecturecounter<=0) break;
			      tempentry=m_master.GetItemText(i,j);
                  if(tempentry.IsEmpty())
				  { m_master.SetItemText(i,j,wiz2.m_sub_tr);
				    m_master.RedrawCell(i,j);
                    lecturecounter--;
				  }
				}
		}
	}

	
}

void CCollegeTimeTableView::OnSetFullnames() 
{
 
  if(expand.ExpandedNames.GetSize()<=0)
  {
  int i, tcodesize;
  Fill_AllIndividuals_in_tcodesArray();
  tcodesize=tcodes.GetSize();
  if(tcodesize>0)
  for(i=0;i<tcodesize;i++) expand.ExpandedNames.Add(tcodes[i]);
  else 
  expand.ExpandedNames.Add("");
  }
  expand.DoModal();
	
}



void CCollegeTimeTableView::OnEditDefreezeOnString() 
{

mdd.m_freezmsg="Enter String to DeFreeze Multiple Cells";
if(mdd.DoModal()!=IDOK) return;
 int i,j;
 CString temp;
 
 if(mdd.m_mdstring.IsEmpty()) return;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 if(temp.Find(mdd.m_mdstring)!=-1) ///string found, make YELLOW
		 { m_master.SetItemBkColour(i,j,WHITE);
		 m_master.RedrawCell(i,j);}
		}
}

void CCollegeTimeTableView::OnEditSelectOnGivenString() 
{mdd.m_freezmsg="Enter String to Select Multiple Cells";
 if(mdd.DoModal()!=IDOK) return;
 int i,j;
 CString temp;
 
 if(mdd.m_mdstring.IsEmpty()) return;
 for(i=1;i<ROWS;i++)
		for(j=0;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 if(temp.Find(mdd.m_mdstring)!=-1) ///string found, make YELLOW
		 {m_master.SetItemState(i,j,GVIS_SELECTED);
		  m_master.RedrawCell(i,j);}
		}

	
}

void CCollegeTimeTableView::OnToolsDisplaynextindividual() 
{
if(DispIndexIndi>tcodes.GetUpperBound()) DispIndexIndi=0;
GenerateIndividual(tcodes[DispIndexIndi]);
m_search=tcodes[DispIndexIndi]; UpdateData(FALSE);
DispIndexIndi++;
}


void CCollegeTimeTableView::OnToolsDisplayprevindividual() 
{
if(DispIndexIndi<0) DispIndexIndi=tcodes.GetUpperBound();
GenerateIndividual(tcodes[DispIndexIndi]);
m_search=tcodes[DispIndexIndi]; UpdateData(FALSE);
DispIndexIndi--;
}

void CCollegeTimeTableView::OnToolsRefreshteacherandclasslists() 
{
Fill_AllIndividuals_in_tcodesArray();
Fill_AllClassesArray();
DispIndexIndi=DispIndexClas=0;
}

void CCollegeTimeTableView::OnToolsDisplaynextclass() 
{
 if(DispIndexClas>AllClasses.GetUpperBound()) DispIndexClas=0;
GenerateClass(AllClasses[DispIndexClas]);
m_search=AllClasses[DispIndexClas]; UpdateData(FALSE);
DispIndexClas++;	
}

void CCollegeTimeTableView::OnToolsDisplayprevclass() 
{
 if(DispIndexClas<0) DispIndexClas=AllClasses.GetUpperBound();
GenerateClass(AllClasses[DispIndexClas]);
m_search=AllClasses[DispIndexClas]; UpdateData(FALSE);
DispIndexClas--;
}


void CCollegeTimeTableView::Fill_AllClassesArray()
{int i,j,k; 
 AllClasses.RemoveAll();
 CString temp;
 BOOL found;
for(i=1;i<ROWS;i++)      /// All classes are in the first column of the master
	{temp=m_master.GetItemText(i,0);
     if(temp.IsEmpty()) continue;               /// skip empty cells
	 if(temp[0]>='0' && temp[0]<='9') continue; /// and also skip time cells
     
	 k=AllClasses.GetSize();
	
	 if(k==0)  {AllClasses.Add(temp);continue;} ///initial entry
	
	 found=FALSE;
     for(j=0;j<k;j++)
		if(temp==AllClasses[j]) {found=TRUE; break;}
		  ///// if no duplicate class found then add
		if(!found) AllClasses.Add(temp); 
	}

int II=AllClasses.GetSize();
   for(j=1;j<II;j++)
	   for(i=0;i<j;i++)
		   if(AllClasses[i]>AllClasses[j]) {temp=AllClasses[i];AllClasses[i]=AllClasses[j];AllClasses[j]=temp;}
}


void CCollegeTimeTableView::FastGenerateIndi(int ti) /// teacher index in tcodes two letter Tr code
{
 if(tcodes[ti].IsEmpty()) return;
 int i,j,k,lastidx,syze;
 clashcount=0;
 gapcount=0;
 dubcount=0;
 CString temp,temp2,temp3="("+tcodes[ti]+")",temp4,temptime,tempclash;
 CString timearr[RO]; //Max RO  lectures per day for an individual, index 1 to RO-1
 CStringArray entry;
 CUIntArray count;
 int TotalLectures=0; ///Workload,  0 in the beginning
 for(i=1;i<RO;i++)    /// Clean Individual timetable Area
		for(j=0;j<7;j++)
			{IArr[ti][i][j]=""; 
			 //m_indiv.SetItemBkColour(i,j,WHITE);
			 //m_indiv.RedrawCell(i,j);
			}
	
	IArr[ti][0][0]=""; //clean topleft corner	
	
	
	lastidx=1;
	for(i=1;i<ROWS;i++)   ///Collect All Lecture Timings i.e all numerics in col 0
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue;
		 if(temp[0]>='0' && temp[0]<='9') 
			{ timearr[lastidx]=temp; if(j<RO-1) lastidx++; else  break;} 
		}  /// timearr contains all lecture timings 

	if(lastidx+1<RO) lastidx+=1;
	
	for(i=1;i<=lastidx;i++) IArr[ti][i][0]=timearr[i];
							
	
	int rowindex=0;
	for(i=1;i<ROWS;i++)
		for(j=1;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 k=temp.Find(temp3); ///find  (tcode) , teachercode encluding brackets
            if(temp.Find("//")!=-1)
               { temptime=PickLectureTime(i);
                 for(rowindex=1;rowindex<RO;rowindex++)
				                if(timearr[rowindex]==temptime)
                     { IArr[ti][rowindex][3]="RECESS";
	
                       break;
                      }                         
                }

		 if(k!=-1) /// if (tcode) found 
			{
			 temptime=PickLectureTime(i);
             
		   for(rowindex=1;rowindex<RO;rowindex++)
				  if(timearr[rowindex]==temptime)
					   { 
				         temp4=IArr[ti][rowindex][j];
				      temp2=m_master.GetItemText(i,0); // get class
					     temp2+="-"+temp.Mid(k-3,3); //attach subject
				      if(temp4.IsEmpty())  ///cell empty so no clash
					      IArr[ti][rowindex][j]=temp2;
					      else  //clash occurs
						     {temp4+=","; temp4+=temp2;
                               IArr[ti][rowindex][j]=temp4;
						      //m_indiv.SetItemText(rowindex,j,temp4);
						      //m_indiv.SetItemBkColour(rowindex,j,RED);//red
							  clashcount++;
					    	  }
					     //m_indiv.RedrawCell(rowindex,j); //refresh class entry
					     ///	now add this entry to splitting chart
					     ////   i.e lecture entry & corresponding count
          syze=entry.GetSize();
          if(syze==-1) { entry.Add(temp2); count.Add(1); ///this is first entry
                      TotalLectures++; continue;
                     }
					      BOOL found=FALSE; // Set found=false
					    for(int k=0;k<syze;k++)
						     if(entry[k]==temp2) { count[k]++; found=TRUE; 
											                     	TotalLectures++;break;
												                    } //if entry already there count++
					        ////otherwise add entry and set count=1 for it
						  if(!found) {entry.Add(temp2);count.Add(1);TotalLectures++;}

					   }
			}
		}

         FastSetGapAndDoubleCount(lastidx,ti);
		
}

void CCollegeTimeTableView::FastSetGapAndDoubleCount(int lasttimerow,int ti)
{int i,j,k;
 int first,last;
 gapcount=0;dubcount=0;
 CString temp,temp1;
 for(j=1;j<7;j++)  ////through all six colums
	{   first=last=0;
    	 
		 for(i=1;i<=lasttimerow;i++)              ///first nonempty row index;
			{//temp=m_indiv.GetItemText(i,j);
			 temp=IArr[ti][i][j];
			if(temp.IsEmpty() || temp=="RECESS") continue; else {first=i;break;}
			}

   	 for(i=lasttimerow;i>0;i--)   ///last non-empty row index
		{//temp=m_indiv.GetItemText(i,j);
	     temp=IArr[ti][i][j];
		 if(temp.IsEmpty() || temp=="RECESS") continue; else {last=i; break;}
		}

     
     if(first==0) continue;  ////last has to be zero
     
	 ////now count gaps and also count double lectures

     for(i=first;i<=last;i++)
		{//temp=m_indiv.GetItemText(i,j);
	     temp=IArr[ti][i][j];
		 if(temp.IsEmpty() || temp=="RECESS") {gapcount++;continue;}
		 for(k=i+1;k<=last;k++)
			{//temp1=m_indiv.GetItemText(k,j);
             temp1=IArr[ti][k][j];
		 if(temp==temp1) dubcount++;

			}
		}

 }

}

void CCollegeTimeTableView::FastShow(int ti)
{int j;
FastGenerateIndi(ti); /// two letter Tr code
for(int i=0;i<RO;i++)
   for(j=0;j<COLS;j++)
   {m_indiv.SetItemText(i,j,IArr[ti][i][j]);
    m_indiv.RedrawCell(i,j);
   }


}

void CCollegeTimeTableView::OnToolsAutoreducegaps() 
{int i,j,lastnonemtpyrow;
 CString temp;

	lastnonemtpyrow=2;
	for(i=ROWS;i>=2;i--)   ///Get last non empty row
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue; else break;
		 
		}
	lastnonemtpyrow=i;

//pop(lastnonemtpyrow);

//pop(lastnonemtpyrow);

BOOL bEND=FALSE;
Again:	
cellcount=(lastnonemtpyrow-1)*6;
bEND=FALSE;

//pop(cellcount);


 CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
 COLORREF tempcolour;
    for(i=2;i<=lastnonemtpyrow;i++)
	   {
		for(j=1;j<COLS;j++)
		  { cellcount--;
		    temp.Format("Global Clash Count : %d    Global Double Count : %d    Global Gap Count : %d       [Remaining Cells : %04d]  -  Press ESC To Stop",GlobalClashCount,GlobalDubCount,GlobalGapCount,cellcount);
		    pFrame->SetMessageText(temp);   
		 
		     tempcolour=m_master.GetItemBkColour(i,j);
		    if(tempcolour==YELLOW) continue;		
            temp=m_master.GetItemText(i,j);
		    if(temp.IsEmpty()) continue; 
	        ReduceGapForCell(i,j);
		
			}
 	    GetGlobalGapCount();
		CreateClashReport();
		if(cont.DoModal()!=IDOK) { bEND=TRUE; break;}
		}
RefreshFormat();
if(bEND) return; else goto Again; 

}



void CCollegeTimeTableView::ReduceGapForCell(int Ox,int Oy)
{ COLORREF tempcolour;
  	
 CString Entry1,Entry2,X,Y,sourceClass,currentClass,temp;
 int i,j,SgcBefore,SccBefore,TgcBefore,TccBefore,SccAfter,SgcAfter,SdcBefore,SdcAfter,TdcBefore;
 int TgcAfter,TccAfter,TdcAfter;
 //int currentR=11,currentC=1;
 Entry1=m_master.GetItemText(Ox,Oy);
 if(Entry1.IsEmpty()) return;
 sourceClass=m_master.GetItemText(Ox,0); ////get class to ensure class exchange only
 if(sourceClass.IsEmpty()) return;
 
 CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

 SgcBefore=SccBefore=SdcBefore=0;
 temp=Entry1;
 while((X=PickTeacherCode2(temp))!="")  ////consume all parallel tr codes
 {  tcodes[0]=X;
    FastGenerateIndi(0);
    SgcBefore+=gapcount;  /// if(X.GetLength()!=2) return;
    SccBefore+=clashcount;
    SdcBefore+=dubcount;
	}
 //MessageBox(X);
for(i=2;i<ROWS;i++)
	for(j=1;j<COLS;j++)
	{   tempcolour=m_master.GetItemBkColour(i,j);
        if(tempcolour==YELLOW) continue;
	
	    currentClass=m_master.GetItemText(i,0);
		if(currentClass!=sourceClass) continue; ///class mismatch ! cannot exchange
		Entry2=m_master.GetItemText(i,j);
		if(Entry2.IsEmpty()) continue;
        TgcBefore=TccBefore=TdcBefore=0;
		temp=Entry2;
       while((Y=PickTeacherCode2(temp))!="")
	   {
        tcodes[0]=Y;
		FastGenerateIndi(0);
        TgcBefore+=gapcount;
        TccBefore+=clashcount;
		TdcBefore+=dubcount;
	   }
         /////Now Exchange Cells
        
		m_master.SetItemText(Ox,Oy,Entry2);
        m_master.SetItemText(i,j,Entry1);
        temp=Entry1;       
		SgcAfter=SccAfter=SdcAfter=0;
 while((X=PickTeacherCode2(temp))!="")
 {   tcodes[0]=X;
    FastGenerateIndi(0); 
    SgcAfter+=gapcount;  /// if(X.GetLength()!=2) return;
    SccAfter+=clashcount;
    SdcAfter+=dubcount;
	}
        temp=Entry2;           		
        TgcAfter=TccAfter=TdcAfter=0;
   while((Y=PickTeacherCode2(temp))!="")
		 {tcodes[0]=Y;
	      FastGenerateIndi(0);
		  TgcAfter+=gapcount;
          TccAfter+=clashcount;
		  TdcAfter+=dubcount;
		}
                  
         
		 if(SccAfter+TccAfter<SccBefore+TccBefore) goto NoRestore; ///clash decreased
		 if(SccAfter+TccAfter>SccBefore+TccBefore) goto RestoreChange; ///clash increased
		 if(SdcAfter+TdcAfter<SdcBefore+TdcBefore) goto NoRestore;
         if(SdcAfter+TdcAfter>SdcBefore+TdcBefore) goto RestoreChange; ///double increased
         
		 if(SgcAfter+TgcAfter>SgcBefore+TgcBefore) goto RestoreChange; /// gap increased
		 //
		 ////No restore i.e changes conformed, 
		 /// Now pick changed cell content from (ox,oy) to exchange with all one by one
		
        NoRestore:
        
        GetGlobalGapCount();
		//CreateClashReport();
        	//temp.Format("Global Clash Count : %d    Global Double Count : %d    Global Gap Count : %d       [Remaining Cells : %d]",GlobalClashCount,GlobalDubCount,GlobalGapCount,cellcount);
		//pFrame->SetMessageText(temp);
		
         Entry1=m_master.GetItemText(Ox,Oy);

         if(Entry1.IsEmpty()) return;
		 sourceClass=m_master.GetItemText(Ox,0); ////get class to ensure class exchange only

         
         SgcBefore=SccBefore=SdcBefore=0;
         temp=Entry1;
         while((X=PickTeacherCode2(temp))!="")
		 { tcodes[0]=X;  
           FastGenerateIndi(0); 
           SgcBefore+=gapcount;  /// if(X.GetLength()!=2) return;
           SccBefore+=clashcount;
           SdcBefore+=dubcount;
		 }
		 continue;
         RestoreChange:
		 m_master.SetItemText(Ox,Oy,Entry1);
         m_master.SetItemText(i,j,Entry2);

		}
}


void CCollegeTimeTableView::OnToolsShowallcounts() 
{CString temp;
GetGlobalGapCount();
CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
temp.Format("Global Clash Count : %d    Global Double Count : %d    Global Gap Count : %d",GlobalClashCount,GlobalDubCount,GlobalGapCount);
pFrame->SetMessageText(temp);   
	
}

void CCollegeTimeTableView::OnHelpHowtousetimetable() 
{
 CHelpSheet propSheet("College Time Table Help", this, 0);

 propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;  //// remove apply button
    
    int result = propSheet.DoModal();
	
}

void CCollegeTimeTableView::OnHelpLoadsampetimetable() 
{
OnFilenu();




CString Load[36][7]={

	{"12:30-01:10"},
	{"FY-A","ENG(MN)","ECO(CD)","SEP(AB)","SEP(AB)","ECO(CD)","SEP(AB)"},
	{"FY-B","ACS(EF)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","ORC(GH)","SEP(AB)","MAR(IJ),HIN(KL)"},
	{"SY-A","ORC(GH)","ACS(EF)","ACS(EF)","ECO(CD)","ACS(EF)","ACS(EF)"},
	{"SY-B","SEP(AB)","ENG(MN)","ORC(GH)","ENG(MN)","ORC(GH)","ORC(GH)"},
	{""},
	{"01:10-01:50"},
	{"FY-A","MAR(IJ),HIN(KL)","ECO(CD)","MAR(IJ),HIN(KL)","ENG(MN)","ENG(MN)","MAR(IJ),HIN(KL)"},
	{"FY-B","SEP(AB)","ACS(EF)","SEP(AB)","SEP(AB)","ACS(EF)","ACS(EF)"},
	{"SY-A","ACS(EF)","ENG(MN)","ORC(GH)","ORC(GH)","ORC(GH)","ORC(GH)"},
	{"SY-B","ORC(GH)","MAR(IJ),HIN(KL)","ECO(CD)","ECO(CD)","SEP(AB)","SEP(AB)"},
	{""},
	{"01:50-02:30"},
	{"FY-A","ECO(CD)","ACS(EF)","ORC(GH)","ORC(GH)","MAR(IJ),HIN(KL)","ORC(GH)"},
	{"FY-B","ENG(MN)","ECO(CD)","ECO(CD)","MAR(IJ),HIN(KL)","ORC(GH)","ENG(MN)"},
	{"SY-A","SEP(AB)","ORC(GH)","ENG(MN)","ENG(MN)","SEP(AB)","MAR(IJ),HIN(KL)"},
	{"SY-B","MAR(IJ),HIN(KL)","SEP(AB)","SEP(AB)","SEP(AB)","ACS(EF)","ACS(EF)"},
	{""},
	{"03:00-03:40"},
	{"FY-A","ORC(GH)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","ACS(EF)","ORC(GH)","ACS(EF)"},
	{"FY-B","MAR(IJ),HIN(KL)","ACS(EF)","ACS(EF)","ENG(MN)","MAR(IJ),HIN(KL)","ECO(CD)"},
	{"SY-A","ENG(MN)","SEP(AB)","SEP(AB)","ECO(CD)","ECO(CD)","SEP(AB)"},
	{"SY-B","ECO(CD)","ORC(GH)","ENG(MN)","ORC(GH)","ENG(MN)","ENG(MN)"},
	{""},
    {"03:40-04:20"}, 
	{"FY-A","SEP(AB)","ORC(GH)","ACS(EF)","ENG(MN)","SEP(AB)","ENG(MN)"},
	{"FY-B","ECO(CD)","SEP(AB)","ORC(GH)","ECO(CD)","ECO(CD)","SEP(AB)"},
	{"SY-A","MAR(IJ),HIN(KL)","ECO(CD)","ECO(CD)","ACS(EF)","ENG(MN)","ECO(CD)"},
	{"SY-B","ACS(EF)","ACS(EF)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)"},
	{""},
	{"04:20-05:00"} ,
	{"FY-A","ACS(EF)","ENG(MN)","ECO(CD)","ECO(CD)","ACS(EF)","SEP(AB)"},
	{"FY-B","ORC(GH)","ORC(GH)","ENG(MN)","ENG(MN)","ENG(MN)","ORC(GH)"},
	{"SY-A","SEP(AB)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","MAR(IJ),HIN(KL)","ENG(MN)"},
	{"SY-B","ENG(MN)","ECO(CD)","ACS(EF)","ACS(EF)","ECO(CD)","ECO(CD)"},
	{""},
	};

for (int i=1;i<=36;i++)
   for(int j=0;j<=7;j++)
     m_master.SetItemText(i,j,Load[i-1][j]);

RefreshFormat();
	
}
