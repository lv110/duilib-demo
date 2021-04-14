#pragma once
#include <duilib/UIlib.h>
#include"Setting.h"
class MenuForm :public ui::WindowImplBase {
public:
	MenuForm() { xmlName = (TCHAR*)L"title_menu.xml"; }
	~MenuForm() {}

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual void InitWindow() override;

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	//inline interface
	inline void MenuShow(BOOL bNeedDpiScale);
	inline void MenuHide();	
	inline BOOL isVisible() {return menuState;}
	void MenuInit(const TCHAR* menuBtnName[MAX_MENU_BTN_NUM],INT menuBtnNum);

private:
	void OnLoadedResourceFile(const std::wstring& xml);
	

public:
	static const std::wstring kClassName;
	static INT isSelected;
	ui::UiRect menuRect;
	INT* titleBtnState=nullptr;
	ui::Button* titleButton=nullptr;
	HWND mainWnd;

private:
	INT menuState = 0;
	INT menuBtnNum;
	
	//Menu button
	ui::Button* menuButtons[MAX_MENU_BTN_NUM];
	TCHAR* xmlName;
};

const std::wstring MenuForm::kClassName = L"Menu";
INT MenuForm::isSelected = 0;

//my interface
void MenuForm::MenuInit(const TCHAR* menuBtnName[MAX_MENU_BTN_NUM], INT menuBtnNum) {
	for (int i = 0; i < menuBtnNum; i++) {
		menuButtons[i] = dynamic_cast<ui::Button*>(FindControl(menuBtnName[i]));
	}
}

inline void MenuForm::MenuShow(BOOL bNeedDpiScale) {
	this->SetPos(menuRect, bNeedDpiScale, 0);
	this->ShowWindow();
	menuState = 1;
}

inline void MenuForm::MenuHide() {
	isSelected = 0;
	::ShowWindow(this->GetHWND(), SW_HIDE);
}

std::wstring MenuForm::GetSkinFolder() {
	return L"menu";
}

std::wstring MenuForm::GetSkinFile() {
	return xmlName;
}

std::wstring MenuForm::GetWindowClassName() const {
	return kClassName;
}

void MenuForm::InitWindow() {
	menuRect = this->GetPos();
}

LRESULT MenuForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT MenuForm::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	//OutputDebugString(L"Menu killFocus \n");
	
	if (titleButton != nullptr) {

		static ui::UiRect rect;
		static POINT pos;

		rect=titleButton->GetPos();
		GetCursorPos(&pos);
		ScreenToClient(mainWnd, &pos);

		//disable button show menu
		if (mhelper::InRect(rect, pos)) {
			*titleBtnState = 0;
		}
		
	}
	
	menuState = 0;
	isSelected = 0;
	this->titleButton->SetFont(nofocusFont);
	::ShowWindow(this->GetHWND(), SW_HIDE);
	return 0;
}
