#pragma once
#include<base/base.h>
#include<duilib/UIlib.h>
#include"BasicForm.h"
class MainThread : public nbase::FrameworkThread {

public:
	MainThread() : nbase::FrameworkThread("MainThread") {}
	virtual ~MainThread() {}
private:
	/**
	* 虚函数，初始化主线程
	* @return void	无返回值
	*/
	virtual void Init() override;
	/**
	* 虚函数，主线程退出时，做一些清理工作
	* @return void	无返回值
	*/
	virtual void Cleanup() override;
};

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(10);
	// 获取资源路径，初始化全局参数
	// 默认皮肤使用 resources\\themes\\default
	// 默认语言使用 resources\\lang\\zh_CN
	// 如需修改请指定 Startup 最后两个参数
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), true);
	
	DWORD color = ui::GlobalManager::GetTextColor(_T("color_palette9"));
	std::wstring defaultName = ui::GlobalManager::GetDefaultFontName();
	int debug = 10;



	// ui::Box box = ui::GlobalManager::CreateBox(_T(),)

	// 创建一个默认带有阴影的居中窗口	
	BasicForm* window = new BasicForm();
	window->Create(NULL, BasicForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW | WS_MAXIMIZEBOX | WS_THICKFRAME,0);
	window->CenterWindow();
	/*DWORD style = GetWindowLong(window->GetHWND(), GWL_STYLE);
	SetWindowLong(window->GetHWND(), GWL_STYLE, style & ~CS_DBLCLKS);*/
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Shutdown();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
