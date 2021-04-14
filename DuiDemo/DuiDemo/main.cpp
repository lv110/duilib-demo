
#include<base/base.h>
#include<duilib/UIlib.h>
#include<Windows.h>
#include"main.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow){

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MainThread thread;
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

	return 0;
}
