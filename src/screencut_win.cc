#include "commons.h"
#include "windows.h"
#include <cstdio>
#include "screencut_wnd.h"
#include "constants.h"


using namespace ui;

#if defined(WIN32_GUI)
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  BOOL open_console = FALSE;
#else
int _tmain(int argc, TCHAR **argv) {
  LPTSTR lpCmdLine = argc > 1 ? argv[1] : _T("");
  HINSTANCE hInstance = GetModuleHandle(NULL);
#endif
  HANDLE hMutex = CreateMutex(NULL, TRUE, _T("screencut"));
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    CloseHandle(hMutex);
    return -1;
  }

  SAVE_RULE save_rule = SAVE_CLIPBOARD;
  LPTSTR lpFileType = NULL;
  int filetype_filter_index = 0;

  if (StrStr(lpCmdLine, _T("file")) != NULL) {
    lpFileType = lpCmdLine + 5;
    save_rule = SAVE_FILE;
#if defined(WIN32_GUI)
    open_console = TRUE;
#endif
  } else if (StrStr(lpCmdLine, _T("clipboard"))) {
#if defined(WIN32_GUI)
    open_console = TRUE;
#endif
  }

#if defined(WIN32_GUI)
  if (open_console) {
#endif
    if (::AllocConsole()) {
      freopen("CONOUT$", "w", stdout);
    }
#if defined(WIN32_GUI)
  }
#endif

  if (lpFileType) {
    filetype_filter_index = -1;
    for (int i = 0; i < FILERNAMES_LEN; i++) {
      if (NULL == StrCmp(lpFileType, FILTERNAME_ARR[i] + 1)) {
        filetype_filter_index = i;
        break;
      }
    }
    if (filetype_filter_index == -1) {
      wprintf(_T("{\"status\":\"error\",\"messsage\":\"filetype(%s) not support\"}"), lpFileType);
      return 0;
    }
  }

  CWndImpl::SetInstance(hInstance);
  CScreenCutWnd* pScreenCut = new CScreenCutWnd;
  pScreenCut->SetDesotryByWindow(FALSE);
  pScreenCut->SetSaveRule(save_rule);
  pScreenCut->SetDefaultFilterIndex(filetype_filter_index);

  pScreenCut->Create(NULL, _T("ScreenCut"), WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, SCREEN_RC);
  UpdateWindow(pScreenCut->GetSafeHwnd());

  CWndImpl::MsgLoop();

#if defined(WIN32_GUI)
  if (open_console) {
#endif
    CString strJson;
    strJson.Append(_T("{\"status\":\""));
    switch (pScreenCut->GetFinishStatus()) {
    case FINISH_SAVE:
      strJson.Append(_T("save"));
      break;
    case FINISH_SAVEAS:
      strJson.Append(_T("saveas"));
      break;
    case FINISH_CANCEL:
      strJson.Append(_T("cancel"));
      break;
    default:
      strJson.Append(_T("error"));
      break;
    }
    strJson.Append(_T("\""));

    if ((pScreenCut->GetFinishStatus() == FINISH_SAVE && save_rule == SAVE_FILE) || pScreenCut->GetFinishStatus() == FINISH_SAVEAS) {
      strJson.Append(_T(",\"file\":\""));
      CString strTempJsonPath = pScreenCut->GetImageSavedFilePath();
      strTempJsonPath.Replace(_T("\\"), _T("\\\\"));
      strJson.Append(strTempJsonPath);
      strJson.Append(_T("\""));
    } else if (pScreenCut->GetFinishStatus() == FINISH_SAVE && save_rule == SAVE_CLIPBOARD) {
      strJson.Append(_T(",\"clipboard\":true"));
    }
    strJson.Append(_T("}"));
    wprintf(_T("%s"), strJson);
#if defined(WIN32_GUI)
  }
#endif

  delete pScreenCut;
  CloseHandle(hMutex);
  return 0;
}