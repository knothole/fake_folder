# Microsoft Developer Studio Project File - Name="Fox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** �ҏW���Ȃ��ł������� **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Fox - Win32 Debug
!MESSAGE ����͗L����Ҳ�̧�قł͂���܂���B ������ۼު�Ă�����ނ��邽�߂ɂ� NMAKE ���g�p���Ă��������B
!MESSAGE [Ҳ�̧�ق̴���߰�] ����ނ��g�p���Ď��s���Ă�������
!MESSAGE 
!MESSAGE NMAKE /f "Fox.mak".
!MESSAGE 
!MESSAGE NMAKE �̎��s���ɍ\�����w��ł��܂�
!MESSAGE ����� ײݏ��ϸۂ̐ݒ���`���܂��B��:
!MESSAGE 
!MESSAGE NMAKE /f "Fox.mak" CFG="Fox - Win32 Debug"
!MESSAGE 
!MESSAGE �I���\������� Ӱ��:
!MESSAGE 
!MESSAGE "Fox - Win32 Release" ("Win32 (x86) Application" �p)
!MESSAGE "Fox - Win32 Debug" ("Win32 (x86) Application" �p)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Fox - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Fox - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Fox - Win32 Release"
# Name "Fox - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Encode.cpp
# End Source File
# Begin Source File

SOURCE=.\FileApi.cpp
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\FileString.cpp"
# End Source File
# Begin Source File

SOURCE=.\Folder.cpp
# End Source File
# Begin Source File

SOURCE=.\Fox.cpp
# End Source File
# Begin Source File

SOURCE=.\Fox.rc
# End Source File
# Begin Source File

SOURCE=.\FoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FoxIni.cpp
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\Ini.cpp"
# End Source File
# Begin Source File

SOURCE=.\MainPage.cpp
# End Source File
# Begin Source File

SOURCE=.\RegEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingPage.cpp
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\ShellControl.cpp"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutPage.h
# End Source File
# Begin Source File

SOURCE=.\Encode.h
# End Source File
# Begin Source File

SOURCE=.\FileApi.h
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\FileString.h"
# End Source File
# Begin Source File

SOURCE=.\Folder.h
# End Source File
# Begin Source File

SOURCE=.\Fox.h
# End Source File
# Begin Source File

SOURCE=.\FoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\FoxIni.h
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\Ini.h"
# End Source File
# Begin Source File

SOURCE=.\MainPage.h
# End Source File
# Begin Source File

SOURCE=.\RegEdit.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SettingPage.h
# End Source File
# Begin Source File

SOURCE="..\�֐��N���X\ShellControl.h"
# End Source File
# Begin Source File

SOURCE=.\SpecialFolder.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Fox.ico
# End Source File
# Begin Source File

SOURCE=.\res\Fox.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\not.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
