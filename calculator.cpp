#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define PLUS 1
#define Minu 2
#define Mul 3
#define Div 4
void TextBox(HWND);
HWND num;
HWND num2;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_CREATE:{
			TextBox(hwnd);
			break;
		}
		case WM_COMMAND:{
			char first[30] , second[30];
			GetWindowText(num,first,30);
			GetWindowText(num2,second,30);
			double x = atof(first);
			double y = atof(second);
			double ans;
			char t[50];
			switch(wParam)
			{
				case PLUS:{
					ans = x+y;
					sprintf(t, "%.2f", ans);
					MessageBox(hwnd,t,"Result",MB_OK);
					break;
				}
				case Minu:{
					ans = x-y;
					sprintf(t, "%.2f", ans);
					MessageBox(hwnd,t,"Result",MB_OK);
					break;
				}
				case Mul:{
					ans = x*y;
					sprintf(t, "%.2f", ans);
					MessageBox(hwnd,t,"Result",MB_OK);
					break;
				}
				case Div:{
					if (y == 0) MessageBox(hwnd,"efn","Result",MB_OK);break;
					ans = x/y;
					sprintf(t, "%.2f", ans);
					MessageBox(hwnd,t,"Result",MB_OK);
					break;
				}
			}
			
		}
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(70,240,0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

void TextBox(HWND hWnd){
	CreateWindowW(L"static",L"Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER,25,25,180,25,hWnd,NULL,NULL,NULL);
	num = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER |ES_MULTILINE|ES_AUTOHSCROLL,40,55,150,25,hWnd,NULL,NULL,NULL);
	num2 = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER |ES_MULTILINE|ES_AUTOHSCROLL,40,85,150,25,hWnd,NULL,NULL,NULL);
	CreateWindowW(L"Button",L"+",WS_VISIBLE | WS_CHILD ,45,120,25,25,hWnd,(HMENU)PLUS,NULL,NULL);
	CreateWindowW(L"Button",L"-",WS_VISIBLE | WS_CHILD ,75,120,25,25,hWnd,(HMENU)Minu,NULL,NULL);
	CreateWindowW(L"Button",L"*",WS_VISIBLE | WS_CHILD ,105,120,25,25,hWnd,(HMENU)Mul,NULL,NULL);
	CreateWindowW(L"Button",L"/",WS_VISIBLE | WS_CHILD ,135,120,25,25,hWnd,(HMENU)Div,NULL,NULL);
}