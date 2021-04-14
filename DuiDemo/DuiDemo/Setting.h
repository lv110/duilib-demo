#pragma once
#include<Windows.h>

//dpi
BOOL bNeedDpiScale = FALSE;

//MenuGap
const static INT menuGap = 10;

#define MAX_FONT_LEN 100
const static TCHAR nofocusFont[MAX_FONT_LEN] = _T("system_12");
const static TCHAR focusFont[MAX_FONT_LEN] = _T("system_bold_12");

#ifdef _DEBUG
#define _DEBUG_LOG(str,num1,num2,num3) \
{\
	TCHAR buff[100];\
	swprintf(buff,_T("%s %d %d %d \n"),str,num1,num2,num3);	\
	OutputDebugString(buff);\
}

#else

#endif

#define MAX_MENU_BTN_NUM 20
#define MAX_XML_NAME_LEN 100

const static TCHAR* menuBtnFile[MAX_MENU_BTN_NUM] = { _T("new_btn"),_T("open_btn") ,_T("open_recent_btn") ,_T("save_btn") 
,_T("save_as_btn") ,_T("save_copy_as_btn") ,_T("close_btn") ,_T("close_all_btn")};
const static INT menuBtnFileNum = 8;

namespace mhelper {
	inline VOID CR2SR (ui::UiRect &cr,HWND hwnd) {		
		POINT plt = { cr.left,cr.right };
		POINT prb = { cr.right,cr.bottom };
		ClientToScreen(hwnd, &plt);
		ClientToScreen(hwnd, &prb);
		cr.left = plt.x;
		cr.top = plt.y;
		cr.right = prb.x;
		cr.bottom = prb.y;
	}

	inline void  MoveRectTo(ui::UiRect &rect,INT x, INT y) {
		INT width = rect.right - rect.left;
		INT height = rect.bottom - rect.top;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
	}
	
	inline BOOL InRect(ui::UiRect& rect, POINT& point) {
		if (point.x<rect.left || point.x>rect.right || point.y<rect.top || point.y>rect.bottom) return false;
		return true;
	}

}