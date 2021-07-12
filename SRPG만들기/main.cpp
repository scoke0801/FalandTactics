// SRPG�����.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "main.h"

//Ÿ��Ʋ �̸��� ������ Ŭ���� �̸� ���̸� �����մϴ�.
#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

CFrameWork  myFramework;
CConsoleManager console(&myFramework);
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SRPG, szWindowClass, MAX_LOADSTRING);
    
	//����� ������ Ŭ������ �����մϴ�.
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SRPG));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			myFramework.PreUpdate();
		}
	}
 
    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style =
		  CS_HREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�. 
		| CS_VREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�.
		| CS_DBLCLKS	//�ش� �������α׷��� ���� Ŭ���� �����ϵ��� �մϴ�.
		;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;	///���� ���α׷��� �ν��Ͻ� �ڵ��� ����մϴ�.
    //MAKEINTRESOURCE : Make Inter Source - ���� ���α׷� ���ο� �ִ� ���ҽ��� �ε����� ��ȯ�ϴ� ��ũ��
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); //������ ������ �����Ѵٸ� �ڵ����� ����Ƿη� �մϴ�.
	wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_SRPG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_StageSelect_Proc;
	wcex.lpszClassName = _T("StageSelect_Class");
	
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_Notice_Proc;
	wcex.lpszClassName = _T("Notice_Class");

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_UnitInfo_Proc;
	wcex.lpszClassName = _T("UnitInfo_Class");

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_CommandSelect_Proc;
	wcex.lpszClassName = _T("CommandSelect_Class");

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_DetailSelect_Proc;
	wcex.lpszClassName = _T("Detail_Class");

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_Login_Proc;
	wcex.lpszClassName = _T("Login_Class");
	
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_ClearCondition_Proc;
	wcex.lpszClassName = _T("ClearCondition_Class");

	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = UI_UnitDetailInfo_Proc;
	wcex.lpszClassName = _T("UnitDetailInfo_Class");

	RegisterClassExW(&wcex);
	wcex.lpfnWndProc = UI_Achievement_Proc;
	wcex.lpszClassName = _T("Achievement_Class");
	//RegisterClassExW(&wcex);

	//wcex.lpfnWndProc = CUI_UnitInfo::ChildProc;
	//wcex.lpszClassName = TEXT("ChildCls");
	//wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//return RegisterClassEx(&wcex); // �ʿ��� �κ��� �����Ͽ� ChildCls�� �� ����Ͽ���. 

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
			
	//������ ��Ÿ���� �����մϴ�.
   DWORD dwStyle =
	   WS_OVERLAPPED //����Ʈ ������.Ÿ��Ʋ �ٿ� ũ�� ������ �ȵǴ� ��輱�� ���� �����츦 ����ϴ�.
	  // | WS_CAPTION	//Ÿ��Ʋ �ٸ� ���� �����츦 ����� WS_BORDER ��Ÿ���� �����մϴ�.
	  // | WS_BORDER	//�ܼ����� �� ��輱(ũ�� ���� �Ұ���)�� ����ϴ�
	   | WS_SYSMENU //�ý��� �޴��� ���� �����츦 ����ϴ�.
	  // | WS_MINIMIZEBOX//�ּ�ȭ ��ư�� ����ϴ�.
	   | WS_CLIPCHILDREN //���ϵ尡 ��ġ�� ������ �׸��� �ʽ��ϴ�.
	   | WS_CLIPSIBLINGS		//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
	   ;
   //����ũ�� ������ ũ�⸦ �����մϴ�.
   RECT rcWinSize;
   ::GetWindowRect(::GetDesktopWindow(), &rcWinSize);

   //Ŭ���̾�Ʈ ũ�⸦ �����մϴ�.
   RECT rcClientSize;
   rcClientSize.left = rcClientSize.top = 0;
   rcClientSize.right = CLIENT_WIDTH;
   rcClientSize.bottom = CLIENT_HEIGHT;

   //������ ������� ���� �߰��Ǵ�(ĸ��, �ܰ���) ũ�⸦ �����մϴ�.
   ::AdjustWindowRect(&rcClientSize, dwStyle, FALSE);

   //Ŭ���̾�Ʈ�� ������ ��ǥ�� ����ũ���� �߾��� �ǵ��� �����մϴ�.
   POINT ptClientPos;
   ptClientPos.x = (rcWinSize.right - CLIENT_WIDTH) / 2;
   ptClientPos.y = (rcWinSize.bottom - CLIENT_HEIGHT) / 2;

   HWND hWnd = CreateWindowW(
	   szWindowClass	//������ Ŭ���� ��
	   , szTitle		//Ÿ��Ʋ�� �Էµ� ���ڿ�
	   , dwStyle		//������ ��Ÿ��
	   , ptClientPos.x	//���� ���α׷��� ���۵� x��ǥ
	   , ptClientPos.y	//���� ���α׷��� ���۵� y��ǥ
	   , CLIENT_WIDTH	//���� ���α׷��� ���� ����
	   , CLIENT_HEIGHT	//���� ���α׷��� ���� ���� 
	   , nullptr		//�θ� ������
	   , nullptr		//�޴� �ڵ�
	   , hInstance		//�ν��Ͻ� �ڵ�
	   , nullptr		//�߰� �Ķ����
	   );

   //������ ������ ������ ��� FALSE�� ��ȯ�Ͽ� ���α׷��� �����ϵ��� �մϴ�.
   if (!hWnd)
   {
      return FALSE;
   }

   if (!myFramework.OnCreate(hWnd, hInstance))
   {
	   return FALSE;
   }
   //�����츦 �����ݴϴ�.
   ::ShowWindow(hWnd, nCmdShow);
   ::UpdateWindow(hWnd);

   //������ ������ ������ ��� TRUE�� ��ȯ�մϴ�.
   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_ERASEBKGND:
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            }
        }
	case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
    case WM_PAINT:
		myFramework.OnProcessingWindowMessae(hWnd, message, wParam, lParam);
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		/*CUnit *unit;
		unit = new CUnit();
		unit->OnDraw(hdc);*/
		EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
