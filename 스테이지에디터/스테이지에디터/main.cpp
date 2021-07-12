#include "base.h"
#include "tile.h"
using namespace std;
#define WIDTH 64
#define HEIGHT 32
HINSTANCE g_hInst;
LPCTSTR lpszClass = "스테이지 에디터";

BOOL DiamondCrashCheck(float, float, Tile*);
BOOL RectangleCrashCheck(float MX, float MY, float X, float Y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
void WM_PAINTDRAW(HDC memdc, HDC bitdc);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(
		lpszClass, lpszClass, (WS_SYSMENU | WS_THICKFRAME),
		0, 0, 1200, 720, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

HPEN hPen, oldPen;
HBRUSH hBrush, oldBrush;
HDC hdc;
HBITMAP hBitmap;
static RECT rect;
PAINTSTRUCT ps;
HBITMAP hBit, oldBit;
CImage tile;
Tile Ground[30][20];
int CamX[2], CamY[2], Savex, Savey;
int StartX, StartY, MouseX, MouseY, TypeNum, ImageNum;
BOOL ClickL, Check, ClickR, Unfold, Hill;
OPENFILENAME OFN;
char str10[100], lpstrFile[100] = "";
TCHAR str[100];
TCHAR CamGuide[10], TileDraw[10], HillGuide[10];
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		Savex = Savey = -1;
		for (int i = 0; i < 30; ++i)
			for (int j = 0; j < 20; ++j)
				Ground[i][j].Init(i,j);
		tile.Load("resource/통합.bmp");
		GetClientRect(hWnd, &rect);
		TypeNum = -1;
		wsprintf(CamGuide, "Cam X");
		wsprintf(HillGuide, "Hill X");
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		HBITMAP mem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		HDC memdc = CreateCompatibleDC(hdc);
		HDC bitdc = CreateCompatibleDC(memdc);
		SelectObject(memdc, mem);

		WM_PAINTDRAW(memdc, bitdc);

		DeleteDC(bitdc);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(mem);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		Check = TRUE;		//마우스 클릭 확인
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		/*MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		for (int i = 0; i < 30; ++i)
			for (int j = 0; j < 20; ++j)
				if (DiamondCrashCheck(MouseX, MouseY, &Ground[i][j]))
				{
					Ground[i][j].SetTop(Ground[i][j].GetTop() - HEIGHT / 2);
					Ground[i][j].SetHeight(Ground[i][j].GetHeight() + 1);
				}
		InvalidateRect(hWnd, NULL, FALSE);
		break;*/
		if (!ClickL)	//타일 변경 모드
		{
			int tempx = -1, tempy = -1;
			for (int i = 0; i < 30; ++i)
			{
				for (int j = 0; j < 20; ++j)
				{
					if (DiamondCrashCheck(MouseX - CamX[0] - CamX[1], MouseY - CamY[0] - CamY[1], &Ground[i][j]))	//클릭 체크
					{
						if (tempx == -1)
						{
							tempx = i;
							tempy = j;
						}
						else if (tempx >= 0 && tempx <= 29)		//중복 체크
						{
							if (Ground[tempx][tempy].GetHeight() < Ground[i][j].GetHeight())		//높이가 높은 부분 우선
							{
								tempx = i;
								tempy = j;
							}
						}
					}
				}
			}
			if (tempx != -1)				//클릭을 확인받고 이미지 변경 부분
			{
				Ground[tempx][tempy].SetType(TypeNum);
				Ground[tempx][tempy].SetImage(ImageNum);
				//Ground[tempx][tempy].SetTop(Ground[tempx][tempy].GetTop() - HEIGHT / 2);
				//Ground[tempx][tempy].SetHeight(Ground[tempx][tempy].GetHeight() + 1);
			}
		}
		else if (ClickL)
		{
			Check = TRUE;
			StartX = MouseX = LOWORD(lParam);
			StartY = MouseY = HIWORD(lParam);
		}
#pragma region 타일 변경부분
		for (int i = 0; i < 7; ++i)
		{
			if (RectangleCrashCheck(MouseX, MouseY, rect.right - WIDTH, rect.bottom - HEIGHT * (i+1)))
			{
				TypeNum = i;
				ImageNum = 0;
				Unfold = TRUE;
			}
		}
		if (Unfold)
		{
			for (int i = 0; i < 12; ++i)
			{
				if (RectangleCrashCheck(MouseX, MouseY, rect.right - WIDTH * 2, rect.bottom - HEIGHT * (i + 1)))
				{
					ImageNum = i;
				}
			}
		}
#pragma endregion
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_LBUTTONUP:
	{
		Check = FALSE;
		if (ClickL)
		{
			StartX += CamX[0];
			StartY += CamY[0];
			CamX[1] += CamX[0];
			CamY[1] += CamY[0];
			CamY[0] = CamX[0] = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if (!ClickR)
		{
			ClickR = TRUE;
			int tempx = -1, tempy = -1;
			MouseX = LOWORD(lParam);
			MouseY = HIWORD(lParam);
			for (int i = 0; i < 30; ++i)
			{
				for (int j = 0; j < 20; ++j)
				{
					if (DiamondCrashCheck(MouseX - CamX[0] - CamX[1], MouseY - CamY[0] - CamY[1], &Ground[i][j]))
					{
						if (tempx == -1)
						{
							tempx = i;
							tempy = j;
						}
						else if (tempx >= 0 && tempx <= 29)
						{
							if (Ground[tempx][tempy].GetHeight() < Ground[i][j].GetHeight())
							{
								tempx = i;
								tempy = j;
							}
						}

					}
				}
			}
			if (Hill && tempx != -1 && (Savex != tempx && Savex != tempy))
			{
				Ground[tempx][tempy].SetTop(Ground[tempx][tempy].GetTop() - HEIGHT / 2);
				Ground[tempx][tempy].SetHeight(Ground[tempx][tempy].GetHeight() + 1);
				Savex = tempx;
				Savey = tempy;
			}
			else if (Hill == FALSE && (Savex != tempx && Savex != tempy))
			{
				if (Ground[tempx][tempy].GetHeight() != 0)
				{
					Ground[tempx][tempy].SetTop(Ground[tempx][tempy].GetTop() + HEIGHT / 2);
					Ground[tempx][tempy].SetHeight(Ground[tempx][tempy].GetHeight() - 1);
					Savex = tempx;
					Savey = tempy;
				}
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	}
	case WM_RBUTTONUP:
	{
		ClickR = FALSE;
		Savex = -1;
		Savey = -1;
	}
	case WM_MOUSEMOVE:
	{
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		 if (Check && !ClickL)
		{
			for (int i = 0; i < 30; ++i)
			{
				for (int j = 0; j < 20; ++j)
				{
					if (DiamondCrashCheck(MouseX - CamX[0] - CamX[1], MouseY - CamY[0] - CamY[1], &Ground[i][j]))
					{
						Ground[i][j].SetType(TypeNum);
						Ground[i][j].SetImage(ImageNum);
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		 if (ClickR && !Check)
		 {
			 int tempx = -1, tempy = -1;
			 MouseX = LOWORD(lParam);
			 MouseY = HIWORD(lParam);
			 for (int i = 0; i < 30; ++i)
			 {
				 for (int j = 0; j < 20; ++j)
				 {
					 if (DiamondCrashCheck(MouseX - CamX[0] - CamX[1], MouseY - CamY[0] - CamY[1], &Ground[i][j]))
					 {
						 if (tempx == -1)
						 {
							 tempx = i;
							 tempy = j;
						 }
						 else if (tempx >= 0 && tempx <= 29)
						 {
							 if (Ground[tempx][tempy].GetHeight() < Ground[i][j].GetHeight())
							 {
								 tempx = i;
								 tempy = j;
							 }
						 }

					 }
				 }
			 }
			 if (Hill && tempx != -1 && (Savex != tempx && Savex != tempy))
			 {
				 Ground[tempx][tempy].SetTop(Ground[tempx][tempy].GetTop() - HEIGHT / 2);
				 Ground[tempx][tempy].SetHeight(Ground[tempx][tempy].GetHeight() + 1);
				 Savex = tempx;
				 Savey = tempy;
			 }
			 else if (Hill == FALSE && (Savex != tempx && Savex != tempy))
			 {
				 if (Ground[tempx][tempy].GetHeight() != 0)
				 {
					 Ground[tempx][tempy].SetTop(Ground[tempx][tempy].GetTop() + HEIGHT / 2);
					 Ground[tempx][tempy].SetHeight(Ground[tempx][tempy].GetHeight() - 1);
					 Savex = tempx;
					 Savey = tempy;
				 }
			 }
			 InvalidateRect(hWnd, NULL, FALSE);
		 }
		 else if (ClickL && Check)
		 {
			 MouseX = LOWORD(lParam);
			 MouseY = HIWORD(lParam);
			 CamX[0] = MouseX - StartX;
			 CamY[0] = MouseY - StartY;

			 GetClientRect(hWnd, &rect);
			 InvalidateRect(hWnd, NULL, FALSE);
		 }
		break;
	}
	case WM_KEYDOWN:
	{
		if(wParam == VK_F1)
		{
			BOOL save = FALSE;
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter =
				"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = ".";
			if (GetSaveFileName(&OFN) != 0)
			{
				wsprintf(str, "%s 파일에 저장하시겠습니까 ?",
					OFN.lpstrFile);
				MessageBox(hWnd, str10, "저장하기 선택", MB_OK);
				save = TRUE;
			}

			if (save)
			{
				ofstream fout; // 클래스 객체
				fout.open(lpstrFile); // 파일경로를 지정할 수도 있다

				for (int i = 0; i < 30; ++i)
				{
					for (int j = 0; j < 20; ++j)
					{
						fout << Ground[i][j].GetHeight() << " " << Ground[i][j].GetType();
						fout << " " << Ground[i][j].GetImage() << endl;

					}
				}

				fout.close();
			}
		}
		else if (wParam == VK_F2)
		{
			BOOL load = FALSE;
			memset(&OFN, 0, sizeof(OPENFILENAME));  // 초기화 
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter =
				"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = ".";  // 초기 디렉토리 
			if (GetOpenFileName(&OFN) != 0)
			{
				wsprintf(str, "%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
				MessageBox(hWnd, str10, "열기 선택", MB_OK);
				load = TRUE;
			}
			if (load)
			{
				ifstream fin;
				char line[20];
				int num[3];
				int i = 0, j = 0;
				fin.open(lpstrFile);
				for (int i = 0; i < 30; ++i)
				{
					for (int j = 0; j < 20; ++j)
					{
						if (i % 2 == 0)
						{
							Ground[i][j].SetTop(j * HEIGHT);
							Ground[i][j].SetLeft(i / 2 * WIDTH);
						}
						else if (i % 2 == 1)
						{
							Ground[i][j].SetTop(j * HEIGHT + HEIGHT / 2);
							Ground[i][j].SetLeft((i - 1) / 2 * WIDTH + WIDTH / 2);
						}
					}
				}
				while (fin.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
				{
					int space = 0;
					num[0] = atoi(&line[0]);
					if (num[0] >= 10)
						space++;
					num[1] = atoi(&line[space + 1]);
					if (num[1] >= 10)
						space++;
					if (num[1] >= 100)
						space++;
					if (num[1] >= 1000)
						space++;
					num[2] = atoi(&line[space + 3]);
					
					Ground[i][j].SetHeight(num[0]);
					Ground[i][j].SetTop(Ground[i][j].GetTop() - num[0] * HEIGHT / 2);
					Ground[i][j].SetType(num[1]);
					Ground[i][j].SetImage(num[2]);

					j++;
					if (j == 20)
					{
						i++;
						j = 0;
					}
					if (i == 30)
						break;
				}


				fin.close(); // 파일 닫기
			}
		}
		else if (wParam == VK_F5)
		{
			if (ClickL)
			{
				wsprintf(CamGuide, "Cam X");
				ClickL = FALSE;
			}
			else
			{
				wsprintf(CamGuide, "Cam O");
				ClickL = TRUE;
			}
		}
		else if (wParam == VK_F6)
		{
			if (Hill)
			{
				wsprintf(HillGuide, "Hill X");
				Hill = FALSE;
			}
			else
			{
				wsprintf(HillGuide, "Hill O");
				Hill = TRUE;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_TIMER:
	{

		break;
	}
	case WM_COMMAND:
	{
		break;
	}
	case WM_CHAR:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void WM_PAINTDRAW(HDC memdc, HDC bitdc)
{
	Rectangle(memdc, 0, 0, rect.right, rect.bottom);
	for (int j = 0; j < 20; ++j)
		for (int i = 0; i < 30; ++i)
		{
			if (i < 15)
				Ground[i * 2][j].Draw(memdc, &tile, i, j, CamX, CamY);
			else
				Ground[(i - 15) * 2 + 1][j].Draw(memdc, &tile, i, j, CamX, CamY);
		}
	for (int i = 0; i < 7; ++i)
	{
			Rectangle(memdc, rect.right - WIDTH, rect.bottom - HEIGHT * (i + 1),
				rect.right, rect.bottom - HEIGHT * i);
		tile.TransparentBlt(memdc, rect.right - WIDTH, rect.bottom - HEIGHT * (i + 1),
			WIDTH, HEIGHT,
			WIDTH * i, 0, WIDTH, HEIGHT,RGB(255,0,255));
	}
	if (Unfold)
	{
		for (int i = 0; i < 12; ++i)
		{
			if (ImageNum == i)
			{
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
				Rectangle(memdc, rect.right - WIDTH * 2, rect.bottom - HEIGHT * (i + 1),
					rect.right - WIDTH, rect.bottom - HEIGHT * i);
				SelectObject(memdc, oldBrush);
				DeleteObject(hBrush);
			}
			else
				Rectangle(memdc, rect.right - WIDTH * 2, rect.bottom - HEIGHT * (i + 1),
					rect.right - WIDTH, rect.bottom - HEIGHT * i);
			tile.TransparentBlt(memdc, rect.right - WIDTH * 2, rect.bottom - HEIGHT * (i + 1),
				WIDTH, HEIGHT,
				WIDTH * TypeNum, HEIGHT * i, WIDTH, HEIGHT, RGB(255, 0, 255));
			
		}	
	}
	TextOut(memdc, rect.right - 50, rect.top +5, CamGuide, _tcslen(CamGuide));
	TextOut(memdc, rect.right - 50, rect.top + 25, HillGuide, _tcslen(HillGuide));
}
BOOL DiamondCrashCheck(float MX, float MY, Tile *Ground)
{
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			if (!(-0.5*(MX - Ground->GetLeft()) + Ground->GetTop() + HEIGHT / 2 < MY))
				return FALSE;
		}
		else if (i == 1)
		{
			if (!(0.5*(MX - Ground->GetLeft()) + Ground->GetTop() - HEIGHT / 2 < MY))
				return FALSE;
		}
		else if (i == 2)
		{
			if (!(0.5*(MX - Ground->GetLeft()) + Ground->GetTop() + HEIGHT / 2 > MY))
				return FALSE;
		}
		else if (i == 3)
		{
			if (!(-0.5*(MX - Ground->GetLeft()) + Ground->GetTop() + HEIGHT / 2 * 3 > MY))
				return FALSE;
		}
	}
	return TRUE;
}
BOOL RectangleCrashCheck(float MX, float MY, float X, float Y)
{
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			if (MX > X + WIDTH)
				return FALSE;
		}
		else if (i == 1)
		{
			if (MX < X)
				return FALSE;
		}
		else if (i == 2)
		{
			if (MY < Y)
				return FALSE;
		}
		else if (i == 3)
		{
			if (MY > Y + HEIGHT)
				return FALSE;
		}
	}
	return TRUE;
}