# Microsoft Developer Studio Project File - Name="CollegeTimeTable" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CollegeTimeTable - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CollegeTimeTable.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CollegeTimeTable.mak" CFG="CollegeTimeTable - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CollegeTimeTable - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CollegeTimeTable - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CollegeTimeTable - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /machine:I386
# SUBTRACT LINK32 /map /nodefaultlib

!ELSEIF  "$(CFG)" == "CollegeTimeTable - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CollegeTimeTable - Win32 Release"
# Name "CollegeTimeTable - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CollegeName.cpp
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTable.cpp
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTable.rc
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTableDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTableView.cpp
# End Source File
# Begin Source File

SOURCE=.\Continue.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindReplace.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiDisableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageIntroduction.cpp
# End Source File
# Begin Source File

SOURCE=.\PageMenuEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PageMenuFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PageMenuSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PageMenuTools.cpp
# End Source File
# Begin Source File

SOURCE=.\PageQuickStart.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SwapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\Wizard1Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Wizard2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\CollegeName.h
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTable.h
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTableDoc.h
# End Source File
# Begin Source File

SOURCE=.\CollegeTimeTableView.h
# End Source File
# Begin Source File

SOURCE=.\Continue.h
# End Source File
# Begin Source File

SOURCE=.\ExpNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindReplace.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\HelpSheet.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\MultiDisableDlg.h
# End Source File
# Begin Source File

SOURCE=.\PageIntroduction.h
# End Source File
# Begin Source File

SOURCE=.\PageMenuEdit.h
# End Source File
# Begin Source File

SOURCE=.\PageMenuFile.h
# End Source File
# Begin Source File

SOURCE=.\PageMenuSet.h
# End Source File
# Begin Source File

SOURCE=.\PageMenuTools.h
# End Source File
# Begin Source File

SOURCE=.\PageQuickStart.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SwapDlg.h
# End Source File
# Begin Source File

SOURCE=.\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\Wizard1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Wizard2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CollegeTimeTable.ico
# End Source File
# Begin Source File

SOURCE=.\res\CollegeTimeTable.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CollegeTimeTableDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\TT-02-Ind-256color.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
