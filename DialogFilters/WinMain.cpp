#include <Windows.h>
#include <Windowsx.h>
#include <gdiplus.h>
#include <commctrl.h>
#include "Image.h"
#include "resource.h"
#include "BW_Filter.h"
#include "BoxBlur_Filter.h"

using namespace Gdiplus;

LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

myImage* origImg = new myImage();
myImage* resImg = new myImage(); 
Bitmap* newBmp = nullptr; 
int scrPos = 0;
bool isFilter = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	//Start GDI+
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(ID_DIALOG), NULL, DialogProc);
	ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);

	EnableWindow(GetDlgItem(hDlg, BW_RADIO), FALSE);
	EnableWindow(GetDlgItem(hDlg, BLUR_RADIO), FALSE);
	EnableWindow(GetDlgItem(hDlg, ID_SLIDER), FALSE);
	EnableWindow(GetDlgItem(hDlg, RUN_BUTTON), FALSE);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//End 
	GdiplusShutdown(gdiplusToken);
	delete origImg;
	delete resImg;
	delete newBmp; //

	return 0;
}

LRESULT CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BW_RADIO:
		{
			EnableWindow(GetDlgItem(hDlg, ID_SLIDER), FALSE); 
			EnableWindow(GetDlgItem(hDlg, RUN_BUTTON), TRUE);

			BW bw(origImg);
			//bw.Filter(newBmp);
			memcpy(resImg->get_arrResult(), bw.Filter(), resImg->get_height() * resImg->get_stride());
			newBmp = new Bitmap(resImg->get_width(), resImg->get_height(), resImg->get_stride(),
				PixelFormat32bppARGB, (BYTE*)resImg->get_arrResult());

			isFilter = true;
			
			return TRUE;
		}
		case BLUR_RADIO:
		{
			EnableWindow(GetDlgItem(hDlg, ID_SLIDER), TRUE);
			EnableWindow(GetDlgItem(hDlg, RUN_BUTTON), TRUE);

			if (scrPos != 0) {
				BoxBlur boxBlur(origImg, scrPos);
				memcpy(resImg->get_arrResult(), boxBlur.Filter(), resImg->get_height() * resImg->get_stride());
				newBmp = new Bitmap(resImg->get_width(), resImg->get_height(), resImg->get_stride(),
					PixelFormat32bppARGB, (BYTE*)resImg->get_arrResult());

				isFilter = true;
			}
			else {
				MessageBox(hDlg, "Choose kernel size!", "Error", MB_OK);
			}
			
			return TRUE;
		}
		case RUN_BUTTON:
		{
			InvalidateRect(hDlg, NULL, TRUE);
			return TRUE;
		}
		case OPEN_BUTTON:
		{
			origImg->ButtonClick(hDlg);
			origImg->SetImage();
			resImg->CopyImage(origImg);

			EnableWindow(GetDlgItem(hDlg, BW_RADIO), TRUE);
			EnableWindow(GetDlgItem(hDlg, BLUR_RADIO), TRUE);
			EnableWindow(GetDlgItem(hDlg, ID_SLIDER), TRUE);

			InvalidateRect(hDlg, NULL, TRUE);
			return TRUE;
		}
		}
	case WM_HSCROLL:
	{
		scrPos = SendMessage(GetDlgItem(hDlg, ID_SLIDER), TBM_GETPOS, 0, 0);
		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		RECT rect;
		GetWindowRect(GetDlgItem(hDlg, PICTURE_CONTROL), &rect);

		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		const int magic_num = 165;
		if (xPos >= rect.left && xPos <= rect.right && yPos >= rect.top - magic_num && yPos <= rect.bottom) { //
			isFilter = false;
			InvalidateRect(hDlg, NULL, TRUE);
		}
		return TRUE;
	}
	case WM_LBUTTONUP:
	{
		isFilter = true;
		InvalidateRect(hDlg, NULL, TRUE);
		return TRUE;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hDlg, &ps); 

		HDC PChdc = GetDC(GetDlgItem(hDlg, PICTURE_CONTROL));
		Graphics graphics(PChdc); 
		
		if (isFilter) {
			Rect posRect(0, 0, resImg->get_width(), resImg->get_height());
			resImg->PositionImg(hDlg, posRect);

			graphics.DrawImage(newBmp, posRect);
			EnableWindow(GetDlgItem(hDlg, ID_SLIDER), TRUE);
		}
		else {
			Rect posRect(0, 0, origImg->get_width(), origImg->get_height());
			origImg->PositionImg(hDlg, posRect);

			graphics.DrawImage(origImg->get_imgBmp(), posRect);
		}
		
		EndPaint(hDlg, &ps);
		return TRUE; 
	}

	case WM_CLOSE:
		DestroyWindow(hDlg);
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;

	default:
		return FALSE;
	}
}



