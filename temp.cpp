// CollegeTimeTableView.cpp : implementation of the CCollegeTimeTableView class
//

#include "stdafx.h"
#include "CollegeTimeTable.h"

#include "CollegeTimeTableDoc.h"
#include "CollegeTimeTableView.h"


//#include <afxcoll.h>


//#include "Field.h"

//#include "afxtempl.h"

#define ROWS 300  // no. of rows in master
#define COLS 7    // no.of cols in master
#define RO 30     // no. of rows in individual/class

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////Page Description Class ///////////////

class  CPage 
{public :
  CUIntArray Line;//stores line numbers of a single page
                  // first index is line of lecture time
 public :
  	CPage() {}
	~CPage(){}
    CPage& CPage::operator=(const CPage& ss){ Line.RemoveAll();	return *this;}
};


CArray <CPage,CPage&> PageArray;



/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView

IMPLEMENT_DYNCREATE(CCollegeTimeTableView, CFormView)

BEGIN_MESSAGE_MAP(CCollegeTimeTableView, CFormView)
	//{{AFX_MSG_MAP(CCollegeTimeTableView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_SET_ROWSONSCREEN, OnSetRowsonscreen)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_MESSAGE(WM_USER,OnDisplay)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView construction/destruction

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
{   
	CString wdays[]={"MON","TUE","WED","THU","FRI","SAT"};
    LinesPerPage=35;
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
	m_master.SetItemFormat(0,6,ES_CENTER | ES_UPPERCASE);
	   
    CRect rect1(509,80,1018,580);
    m_indiv.Create(rect1,this, 21112);
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

}

/////////////////////////////////////////////////////////////////////////////
// CCollegeTimeTableView printing

BOOL CCollegeTimeTableView::OnPreparePrinting(CPrintInfo* pInfo)
{pInfo->SetMinPage(1);
 CString temp;
 CStringArray arr;
 arr.SetSize(20);   //// for parallel lecture splitting in diff strings
 int height,maxheight;
 int LineCounter=0,PageIndex=0;
 PageArray.RemoveAll();   ////// Reset Page Description Array
 CPage tempage;
 PageArray.Add(tempage);
 BOOL bLastEmpty=FALSE;
 for(int i=1;i<ROWS;i++) ////// Preapre Page Description
	{maxheight=1;
	 temp=m_master.GetItemText(i,0);
     if(temp.IsEmpty()){ if(bLastEmpty) continue;  /// keep atmost one empty row
                         if((LineCounter+1)<LinesPerPage) 
							{LineCounter++;
						     PageArray[PageIndex].Line.Add(i);
                             bLastEmpty=TRUE;
							 continue;
							}
						  else
						  {PageIndex++;
						   PageArray.Add(tempage);
						   LineCounter=0;
						   continue;
						  }
						}
	 bLastEmpty=FALSE;
	 GetParallelLectureList(temp,arr);// Get Parallel lectures in CStringarray arr
     height=arr.GetSize();
	 if(height<1) height=1;
	 if(height>maxheight) maxheight=height; ///max cell height,>1 for parallel lectures
     if((LineCounter+maxheight)<LinesPerPage)
		{LineCounter+=maxheight; //include lines
	     PageArray[PageIndex].Line.Add(i); continue;  ///go for more lines
		}
	 PageIndex++;   /// Page Full, go for next page
	 PageArray.Add(tempage);///Create Empty Page Struct
	 LineCounter=maxheight;  ///
	 PageArray[PageIndex].Line.Add(i);
	}
	pInfo->SetMaxPage(PageIndex+1);

 return DoPreparePrinting(pInfo);
}

void CCollegeTimeTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCollegeTimeTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCollegeTimeTableView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{  int j,k,height,maxheight;
	UINT line;
   CString temp;
   CStringArray arr;
   arr.SetSize(20);
   
   CFont fon;
   CFont* oldfont;
   fon.CreateFont(18,8,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"COURIER NEW");

   oldfont=pDC->SelectObject(&fon); 


   pDC->SetMapMode(MM_LOENGLISH);
   pDC->SetBkMode(TRANSPARENT);
   CPoint PP(70,-25);
   CPoint QQ(771,-25);
   CPoint tempPP,tempQQ;
   UINT lastline=PageArray[(pInfo->m_nCurPage)-1].Line.GetUpperBound();///
   for(line=0;line<=lastline;line++)
   {    maxheight=1;
	   for(j=0;j<7;j++)
		{tempPP=PP;//tempQQ=QQ;
		 temp=m_master.GetItemText(PageArray[(pInfo->m_nCurPage)-1].Line[line],j);
         GetParallelLectureList(temp,arr);// in CStringarray arr
         height=arr.GetSize();
		 if(height<1) height=1;
		 if(height>maxheight) maxheight=height;
		 for(k=0;k<height;k++)
			{pDC->TextOut(74+j*100,PP.y-2,arr[k]);
		     PP.Offset(0,-25);
			 }
         PP=tempPP;//Reset to normal lecture line
		}
		QQ.Offset(0,-25*maxheight);
		DisplayGrid(PP,QQ,1,7,pDC);
		PP.Offset(0,-25*maxheight);
   }  

pDC->SelectObject(&oldfont); 
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


void CCollegeTimeTableView::OnFileOpen() 
{	CFileDialog cfd(TRUE,"tit","*.tit");
    if(cfd.DoModal()==IDOK)
	{ CString token;
	  CString college;
	  CString filepath=cfd.GetPathName();
	  CFile thefile;
	  CFileException exc;

	  thefile.Open(filepath,CFile::modeRead,&exc);
     CArchive archive(&thefile,CArchive::load);
       
        int i,j;

		CString temp;
        
		archive>>token
		       >>college;
        for (i=1;i<ROWS;i++)
			for(j=0;j<COLS;j++)  
			{ archive>>temp;
			  m_master.SetItemText(i,j,temp);
			}	
    	RefreshFormat();
		archive.Close();
		thefile.Close();
	}
}

void CCollegeTimeTableView::OnFileSaveAs() 
{	CFileDialog cfd(FALSE,"tit","*.tit");
    if(cfd.DoModal()==IDOK)
	{ CString token="TimeTable";
	  CString college="College Name";
	  CString filepath=cfd.GetPathName();
	  CFile thefile;
	  CFileException exc;
      thefile.Open(filepath,CFile::modeCreate | CFile::modeWrite,&exc);
      CArchive archive(&thefile,CArchive::store);
       
        int i,j;
		CString temp;
		archive<<token
		       <<college;
        for (i=1;i<ROWS;i++)
			for(j=0;j<COLS;j++)  
			{ temp=m_master.GetItemText(i,j);
			  archive<<temp;
			}	
	}
}

LONG CCollegeTimeTableView::OnDisplay(UINT wParam, LONG lparam)
{
	    CCellID cid=m_master.GetFocusCell();        
		int row=cid.row;
		int col=cid.col;
        CString temp=m_master.GetItemText(row,col);
		if(col==0) //if any class is selected
			GenerateClass(temp);
		///otherwise it is individual display
        else
		{ temp=PickTeacherCode(temp);
		 GenerateIndividual(temp);
		}

 return TRUE;
}

void CCollegeTimeTableView::OnSetRowsonscreen() 
{
	// TODO: Add your command handler code here
	
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

CString CCollegeTimeTableView::PickTeacherCode(CString str)
{int left=str.Find('(');
 int rite=str.Find(')');
 if(left>rite) return "";
 return str.Mid(left+1,rite-left-1);
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

void CCollegeTimeTableView::GenerateIndividual(CString tcode)
{   int i,j,k,lastidx;	CString temp,temp2,temp3="("+tcode+")",temp4,temptime;
	CString timearr[RO]; //Max RO  lectures per day for an individual, index 1 to RO-1
    CStringArray entry;
	CUIntArray count;

    for(i=1;i<RO;i++)    /// Clean Individual timetable Area
		for(j=0;j<7;j++)
			{m_indiv.SetItemText(i,j,""); 
			 m_indiv.SetItemBkColour(i,j,RGB(255,255,255));
			 m_indiv.RedrawCell(i,j);
			}
	
	m_indiv.SetItemText(0,0,""); m_indiv.RedrawCell(0,0); //clean topleft corner	
	
	if(tcode.IsEmpty()) return;


	lastidx=1;
	for(i=1;i<ROWS;i++)   ///Collect All Lecture Timings i.e numerics in col 0
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue;
		 if(temp[0]>='0' && temp[0]<='9') 
			{ timearr[lastidx]=temp; if(j<RO-1) lastidx++; else  break;} 
		}

	if(lastidx+2<RO) lastidx+=2;
	

	for(i=1;i<RO;i++) {m_indiv.SetItemText(i,0,timearr[i]); m_indiv.RedrawCell(i,0);}
	
	int rowindex=0;
	for(i=1;i<ROWS;i++)
		for(j=1;j<COLS;j++)
		{temp=m_master.GetItemText(i,j);
		 if(temp.IsEmpty()) continue;
		 k=temp.Find(temp3); ///find  (tcode)
		 if(k!=-1) /// if (tcode) found 
			{m_indiv.SetItemText(0,0,tcode);
		     m_indiv.RedrawCell(0,0);
			 temptime=PickLectureTime(i);
             
		     for(rowindex=1;rowindex<RO;rowindex++)
				 if(timearr[rowindex]==temptime)
					{temp4=m_indiv.GetItemText(rowindex,j);//Get spot to check clash
				     temp2=m_master.GetItemText(i,0); // get class
					 temp2+="-"+temp.Mid(k-3,3); //attach subject
				     if(temp4.IsEmpty())  ///cell empty so no clash
					 m_indiv.SetItemText(rowindex,j,temp2);
					 else  //clash occurs
						{temp4+=","; temp4+=temp2;
						 m_indiv.SetItemText(rowindex,j,temp4);
						 m_indiv.SetItemBkColour(rowindex,j,RGB(255,200,200));
						}
					 m_indiv.RedrawCell(rowindex,j); //refresh class entry
					  ///	now add this to splitting chart
                     int syze=entry.GetSize();
                     if(syze==-1) {entry.Add(temp2); count.Add(1); continue;}
					 BOOL found=FALSE; // found=false
					 for(int k=0;k<syze;k++)
						 if(entry[k]==temp2) { count[k]++; found=TRUE; break;} 
					  if(!found) {entry.Add(temp2);count.Add(1);}
					}
			}
		}
		int syze=entry.GetSize();
		if(syze==-1) return;
		for(k=0;k<syze;k++)
			{m_indiv.SetItemText(lastidx+k/3,1+2*(k%3),entry[k]);
			 m_indiv.RedrawCell(lastidx+k/3,1+2*(k%3));
			 temp.Format("%2d",count[k]);
			 m_indiv.SetItemText(lastidx+k/3,2+2*(k%3),temp);
			 m_indiv.RedrawCell(lastidx+k/3,2+2*(k%3));
			}
}
		     
void CCollegeTimeTableView::RefreshFormat()
{ int i,j;
  CString temp;
  for (i=1;i<ROWS;i++)
	for(j=0;j<COLS;j++)  
	{ temp=m_master.GetItemText(i,j);
	  if(temp.IsEmpty()) 
	  {m_master.SetItemBkColour(i,j,RGB(255,255,255));
	   m_master.RedrawCell(i,j);continue;
	  }
	   if(temp[0]>='0' && temp[0]<='9')
		   m_master.SetItemBkColour(i,j,RGB(200,255,200));
	       else
			m_master.SetItemBkColour(i,j,RGB(255,255,255));
       m_master.RedrawCell(i,j);
	}
}


void CCollegeTimeTableView::GenerateClass(CString classcode)  //for ex FYJC-I
{   int i,j;	CString temp;
	CString timearr[RO],temptime; //Max RO lectures per day index 1 to RO-1
	j=1;

    for(i=1;i<RO;i++)    /// Clean Individual timetable Area
		for(j=0;j<7;j++)
			{m_indiv.SetItemText(i,j,"");
			 m_indiv.SetItemBkColour(i,j,RGB(255,255,255));
		     m_indiv.RedrawCell(i,j);
			}
    
	m_indiv.SetItemText(0,0,""); m_indiv.RedrawCell(0,0); //clean topleft corner
    if(classcode.IsEmpty()) return;
    if(classcode[0]>='0' && classcode[0]<='9') return; ///it is time entry NOT class

    j=1;
	for(i=1;i<ROWS;i++)   ///Collect All Lecture Timings i.e numerics in col 0
		{temp=m_master.GetItemText(i,0);
		 if(temp.IsEmpty()) continue;
		 if(temp[0]>='0' && temp[0]<='9') 
			{ timearr[j]=temp; if(j<RO-1) j++; else  break;} 
		}
	
	for(i=1;i<RO;i++) {m_indiv.SetItemText(i,0,timearr[i]); m_indiv.RedrawCell(i,0);}
	
	m_indiv.SetItemText(0,0,classcode);
	m_indiv.RedrawCell(0,0);
	
	int rowindex=0;
	for(i=1;i<ROWS;i++)
		{ temp=m_master.GetItemText(i,0);
		 //if(temp.IsEmpty()) continue;
		  if(temp==classcode)  /// include this entry 
			{temptime=PickLectureTime(i);
		     for(rowindex=1;rowindex<RO;rowindex++)  ///
				 if(timearr[rowindex]==temptime)
					{for(j=1;j<7;j++)
						{m_indiv.SetItemText(rowindex,j,m_master.GetItemText(i,j));
						 m_indiv.RedrawCell(rowindex,j); //refresh class entry
						}
					  break;
					}
			}
		}
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
		 { m_master.SetFocusPublic(i,j);
		  return;
		 }
		}
}

void CCollegeTimeTableView::DisplayGrid(CPoint tl,CPoint br,int rows,int cols,CDC* pDC)
{  CPen pPen,*pPenold;
   pPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
   pPenold=pDC->SelectObject(&pPen);
   //CGdiObject *pOldBrush;
   //pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
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
