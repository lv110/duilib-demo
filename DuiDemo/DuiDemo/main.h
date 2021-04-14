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
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;
	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;
};

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(10);
	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	// Ĭ��Ƥ��ʹ�� resources\\themes\\default
	// Ĭ������ʹ�� resources\\lang\\zh_CN
	// �����޸���ָ�� Startup �����������
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), true);
	
	DWORD color = ui::GlobalManager::GetTextColor(_T("color_palette9"));
	std::wstring defaultName = ui::GlobalManager::GetDefaultFontName();
	int debug = 10;



	// ui::Box box = ui::GlobalManager::CreateBox(_T(),)

	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���	
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
