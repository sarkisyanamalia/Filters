#include "BW_Filter.h"

Bitmap* BW::Filter(HWND hDlg) {
	for (UINT col = 0; col < Img->Width; ++col) {
		for (UINT row = 0; row < Img->Height; ++row)
		{
			unsigned int curColor = Img->pixels[row * Img->stride / 4 + col];
			int b = curColor & 0xff;
			int g = (curColor & 0xff00) >> 8;
			int r = (curColor & 0xff0000) >> 16;

			int avg = (b + g + r) / 3;

			Img->arr_result[row * Img->stride / 4 + col].set_RGBA(avg);
		}
	}

	Bitmap* newBitmap = new Bitmap(Img->Width, Img->Height, Img->stride, PixelFormat32bppARGB,
		(BYTE*)Img->arr_result);

	return newBitmap;
}



