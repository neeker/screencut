#include "commons.h"
#include "windows.h"
#include "screencut_wnd.h"


using namespace ui;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  HANDLE hMutex = CreateMutex(NULL, TRUE, _T("screencut"));
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    CloseHandle(hMutex);
    return -1;
  }

  CWndImpl::SetInstance(hInstance);
  CScreenCutWnd* pScreenCut = new CScreenCutWnd;
  pScreenCut->Create(NULL, _T("ScreenCut"), WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, SCREEN_RC);
  UpdateWindow(pScreenCut->GetSafeHwnd());

  CWndImpl::MsgLoop();

  CloseHandle(hMutex);

  return 0;
}