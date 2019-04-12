#include <Windows.h>
#include <gdiplus.h>
#include "Image.h"
#include "resource.h"
#include "BW_Filter.h"
#include "BoxBlur_Filter.h"

using namespace Gdiplus;

LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

myImage* Img = new myImage();
Bitmap* result_img = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	//Start GDI+
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(ID_DIALOG), NULL, DialogProc);
	ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//End 
	GdiplusShutdown(gdiplusToken);
	delete Img->pixels;
	delete Img->orig_img;
	delete Img->arr_result;
	delete Img;
	delete result_img;

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

			BW bw(Img);
			result_img = bw.Filter(hDlg);
			return TRUE;
		}

		case RUN_BUTTON:
		{
			/*HBITMAP img;
			result_img->GetHBITMAP(0, &img);
			SendDlgItemMessage(hDlg, PICTURE_CONTROL, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);*/

			InvalidateRect(hDlg, NULL, TRUE);

			return TRUE;
		}

		case BLUR_RADIO:
		{
			BoxBlur box_blur(Img);
			result_img = box_blur.Filter(hDlg);
			return TRUE;
		}

		case OPEN_BUTTON:
		{
			Img->ButtonClick(hDlg);
			Img->SetImage();

			InvalidateRect(hDlg, NULL, TRUE);
			return TRUE;
		}
		}
	case WM_HSCROLL:
	{
		//int scrlPos = SendMessage(hDlg, TBM_GETPOS, 0, 0);
		return TRUE;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		RECT rect;
		HDC PChdc = GetDC(GetDlgItem(hDlg, PICTURE_CONTROL));
		GetWindowRect(GetDlgItem(hDlg, PICTURE_CONTROL), &rect);
		Graphics* graphics = new Graphics(PChdc);

		int img_x = 0;
		if (result_img != nullptr) {
			if (rect.right - rect.left > result_img->GetWidth()) {
				img_x = (rect.right - rect.left - result_img->GetWidth()) / 2;
			}
			graphics->DrawImage(result_img, img_x, 0);
			result_img = nullptr;
		}
		else { //
			Bitmap* org_img = new Bitmap(Img->get_wstr().c_str());
			if (rect.right - rect.left > org_img->GetWidth()) {
				img_x = (rect.right - rect.left - org_img->GetWidth()) / 2;
			}
			graphics->DrawImage(org_img, img_x, 0);
			delete org_img;
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



