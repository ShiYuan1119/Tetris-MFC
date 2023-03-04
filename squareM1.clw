; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgGameCode
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "squareM1.h"

ClassCount=6
Class1=CSquareM1App
Class2=CSquareM1Dlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_DIALOG_HELP
Resource2=IDR_MAINFRAME
Resource3=IDD_SQUAREM1_DIALOG
Class4=CDlgHelp
Resource4=IDD_DIALOG_SET
Class5=CDlgSet
Resource5=IDD_ABOUTBOX
Class6=CDlgGameCode
Resource6=IDD_DIALOG_GAMECODE

[CLS:CSquareM1App]
Type=0
HeaderFile=squareM1.h
ImplementationFile=squareM1.cpp
Filter=N

[CLS:CSquareM1Dlg]
Type=0
HeaderFile=squareM1Dlg.h
ImplementationFile=squareM1Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSquareM1Dlg

[CLS:CAboutDlg]
Type=0
HeaderFile=squareM1Dlg.h
ImplementationFile=squareM1Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SQUAREM1_DIALOG]
Type=1
Class=CSquareM1Dlg
ControlCount=0

[DLG:IDD_DIALOG_HELP]
Type=1
Class=CDlgHelp
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_BUTTON_MOREGAME,button,1342242816
Control6=IDC_BUTTON_OK,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CDlgHelp]
Type=0
HeaderFile=DlgHelp.h
ImplementationFile=DlgHelp.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgHelp
VirtualFilter=dWC

[DLG:IDD_DIALOG_SET]
Type=1
Class=CDlgSet
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TEXT_SPEED,static,1342308352
Control4=IDC_BUTTON_LEFT,button,1342242816
Control5=IDC_BUTTON_RIGHT,button,1342242816
Control6=IDC_RADIO_MAGIC,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_STATIC,static,1342308352

[CLS:CDlgSet]
Type=0
HeaderFile=DlgSet.h
ImplementationFile=DlgSet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgSet

[DLG:IDD_DIALOG_GAMECODE]
Type=1
Class=CDlgGameCode
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_GAME,edit,1353781444
Control3=IDC_STATIC,static,1342308352

[CLS:CDlgGameCode]
Type=0
HeaderFile=DlgGameCode.h
ImplementationFile=DlgGameCode.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgGameCode

