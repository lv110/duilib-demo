#pragma once
#include<duilib/UIlib.h>
#include"Setting.h"
#include"BasicForm.h"
#include"MenuForm.h"
#include<duilib/Core/Window.h>
#include<duilib/Core/Define.h>
class BasicForm : public ui::WindowImplBase
{
public:	

	BasicForm() ;
	~BasicForm() { }

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	virtual void InitWindow() override;

	//message tackle
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

public:
	const static std::wstring kClassName;
	const static INT buttonNameLen=100;
	const static INT titlebuttonNum=7;
	static INT isSelected;
	const TCHAR* titleButtonName[buttonNameLen];
	static INT titleBtnState[titlebuttonNum];

private:
	ui::Button* titleButtons[titlebuttonNum];
	MenuForm* titleMenu[titlebuttonNum];
	
};

const std::wstring BasicForm::kClassName = _T("Basic");
INT BasicForm::titleBtnState[titlebuttonNum] = { 0 };

BasicForm::BasicForm() :titleButtonName{_T("button_file"),_T("button_edit"),_T("button_layer"),
	_T("button_select"),_T("button_frame"),_T("button_view"),_T("button_help") }, 
	titleMenu{ nullptr }, titleButtons{ nullptr }{ }

std::wstring BasicForm::GetSkinFolder()
{
	return _T("basic");
}

std::wstring BasicForm::GetSkinFile()
{
	return _T("basic.xml");
}

std::wstring BasicForm::GetWindowClassName() const
{
	return kClassName;
}

LRESULT BasicForm::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {

	_DEBUG_LOG(L"OnButtonDown",0,0,0)
	return __super::OnLButtonDown(uMsg,wParam,lParam,bHandled);

}

void BasicForm::InitWindow()
{	
	//menu init
	for (int i = 0; i < titlebuttonNum; i++) {
		titleButtons[i] = dynamic_cast<ui::Button*>(FindControl(titleButtonName[i]));
		this->titleMenu[i] = new MenuForm();
		this->titleMenu[i]->Create(this->GetHWND(), titleButtonName[i], 0, 0, true);
		this->titleMenu[i]->titleBtnState = &titleBtnState[i];
		this->titleMenu[i]->titleButton = titleButtons[i];
		this->titleMenu[i]->mainWnd = this->GetHWND();
		titleBtnState[i] = 1;
		if (i == 0) {
			this->titleMenu[i]->MenuInit(menuBtnFile, menuBtnFileNum);
		}
	}

	for (int i = 0; i < titlebuttonNum; i++) {
		//button click
		titleButtons[i]->AttachClick([i, this](ui::EventArgs* args) {			
			
			//update button position
			ui::UiRect button_rect(titleButtons[i]->GetPos());
			mhelper::CR2SR(button_rect, this->GetHWND());
			mhelper::MoveRectTo(titleMenu[i]->menuRect, button_rect.left, button_rect.bottom + menuGap);

			//menu show
			if (!(((this->titleMenu[i]))->isVisible()) && titleBtnState[i]) {
				(this->titleMenu[i])->MenuShow(bNeedDpiScale);
				for (int j = 0; j < this->titlebuttonNum; j++) {
					if (j != i && this->titleMenu[j] != nullptr) {
						(this->titleMenu[j])->MenuHide();
						this->titleBtnState[j] = 1;
						this->titleButtons[j]->SetFont(nofocusFont);
					}
				}
				this->titleButtons[i]->SetFont(focusFont);
				MenuForm::isSelected = 1;
			}
			titleBtnState[i] = 1;		
			return true; });

		//enter button
		titleButtons[i]->AttachMouseEnter([this,i](ui::EventArgs* args) {
			if (MenuForm::isSelected == 1) {
				if (!(((this->titleMenu[i]))->isVisible())) {
					(this->titleMenu[i])->MenuShow(bNeedDpiScale);
					for (int j = 0; j < this->titlebuttonNum; j++) {
						if (j != i && this->titleMenu[j] != nullptr) {
							(this->titleMenu[j])->MenuHide();
							this->titleBtnState[j] = 1;
							this->titleButtons[j]->SetFont(nofocusFont);
						}
					}
					this->titleButtons[i]->SetFont(focusFont);
					MenuForm::isSelected = 1;
				}
				titleBtnState[i] = 1;
			}
			return true;
		});
	}
}

LRESULT BasicForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT BasicForm::OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {

	//Update Menu Pos	
	for (int i = 0; i < titlebuttonNum; i++) {
		if (this->titleButtons[i] != nullptr && this->titleMenu[i] != nullptr) {
			ui::UiRect button_rect(this->titleButtons[i]->GetPos());
			mhelper::CR2SR(button_rect, this->GetHWND());
			mhelper::MoveRectTo(this->titleMenu[i]->menuRect, button_rect.left, button_rect.bottom + menuGap);
		}
	}
	return 0;
}

LRESULT BasicForm::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnSysCommand(uMsg,wParam,lParam,bHandled);
}

LRESULT BasicForm::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return 0;
}

LRESULT BasicForm::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnKillFocus(uMsg, wParam, lParam, bHandled);
}

LRESULT BasicForm::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnSetFocus(uMsg, wParam, lParam, bHandled);
}