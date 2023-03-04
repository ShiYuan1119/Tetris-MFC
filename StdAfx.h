// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__36B62EF8_708E_4E7A_9BDA_4A35CCEFB98D__INCLUDED_)
#define AFX_STDAFX_H__36B62EF8_708E_4E7A_9BDA_4A35CCEFB98D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//��Ϸ����
//��������
enum eGameState{
	GAME_INFO,
	GAME_MENU,
	GAME_LOAD,
	GAME_IN_PRE,
	GAME_IN,
	GAME_WIN,
	GAME_ITEM,
	GAME_FAIL,
	GAME_PASS
};

//��ʱ(��λ ��)
//programkingƬͷ
#define TIME_INFO 3
//��Ϸʱ��(����ʱ)
#define TIME_MATCH 0
//ʧ��
#define TIME_FAIL 3 

//λͼ
//ͼƬ��Դ
#define PICW 200
#define PICH 160
//ͼƬID
enum bmPicID{
		PIC0,		
		PIC1,		
		PIC2,
		PIC3,
		PIC4,
		PIC5,				
};

//��ťID
enum buttonID{
		BT_START,
		BT_HELP,
		BT_SET,
		BT_OK,
		BT_LEFT,
		BT_RIGHT,
};

#define INVALID -1
#define VALID 1

#define LEVEL_SCORE 300

//��������
#define GAMEWIDTH	430
#define GAMEHEIGHT	480

#define ITEM_EDGE 22
//����
#define RIGHT_RECT_X 266
#define RIGHT_RECT_Y 20

#define LEFT_RECT_X 22
#define LEFT_RECT_Y 20

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__36B62EF8_708E_4E7A_9BDA_4A35CCEFB98D__INCLUDED_)
