#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>
#include<shlobj.h>
TCHAR szClassName[]=TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HWND hEdit;
	switch(msg)
	{
	case WM_CREATE:
		TCHAR szPath[MAX_PATH];
		if(!(SHGetSpecialFolderPath(0,szPath,CSIDL_DESKTOP,0)))
		{
			lstrcpy(szPath,TEXT("デスクトップのパスが取得できませんでした。"));
		}
		hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("EDIT"),szPath,WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_READONLY,10,10,9999,30,hWnd,0,((LPCREATESTRUCT)lParam)->hInstance,0);
		break;
	case WM_SETFOCUS:
		SendMessage(hEdit,EM_SETSEL,0,-1);
		SetFocus(hEdit);
		break;
	case WM_SIZE:
		MoveWindow(hEdit,10,10,LOWORD(lParam)-20,30,1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	HINSTANCE hInstance=GetModuleHandle(0);
	WNDCLASS wndclass={CS_HREDRAW|CS_VREDRAW,WndProc,0,0,hInstance,0,LoadCursor(0,IDC_ARROW),(HBRUSH)(COLOR_WINDOW+1),0,szClassName};
	RegisterClass(&wndclass);
	HWND hWnd=CreateWindow(szClassName,TEXT("デスクトップのパス"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,CW_USEDEFAULT,0,0,0,hInstance,0);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(msg.wParam);
}

#if _DEBUG
void main(){}
#endif