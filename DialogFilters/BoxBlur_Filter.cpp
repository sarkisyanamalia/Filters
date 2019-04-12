#include "BoxBlur_Filter.h"

Bitmap* BoxBlur::Filter(HWND hDlg) {
	int k = 5;

	//vertical
	for (UINT col = 0; col < Img->Width; ++col) {
		int sum_b = 0,
			sum_g = 0,
			sum_r = 0;

		int a;
		for (int i = 0; i < k ; ++i) { //
			unsigned int curColor = Img->pixels[i * Img->stride / 4 + col];
			int b = curColor & 0xff;
			int g = (curColor & 0xff00) >> 8;
			int r = (curColor & 0xff0000) >> 16;
			a = (curColor & 0xff000000) >> 24;

			sum_b += b;
			sum_g += g;
			sum_r += r;
		}
		//

		for (UINT row = 0; row < Img->Height; ++row)
		{
			int prev_index = row - k / 2;
			int next_index = row + (k / 2) + 1;

			if (prev_index >= 0 && next_index < Img->Height) {
				unsigned int prevColor = Img->pixels[prev_index * Img->stride / 4 + col];
				int b = prevColor & 0xff;
				int g = (prevColor & 0xff00) >> 8;
				int r = (prevColor & 0xff0000) >> 16;

				sum_b -= b;
				sum_g -= g;
				sum_r -= r;

				unsigned int nextColor = Img->pixels[next_index * Img->stride / 4 + col];
				b = nextColor & 0xff;
				g = (nextColor & 0xff00) >> 8;
				r = (nextColor & 0xff0000) >> 16;

				sum_b += b;
				sum_g += g;
				sum_r += r;

				Img->arr_result[row * Img->stride / 4 + col].set_RGBA(sum_r / k, sum_g / k, sum_b / k, a);
			}
		}
	}
	//horizontal
	for (UINT row = 0; row < Img->Height; ++row) {
		int sum_b = 0,
			sum_g = 0,
			sum_r = 0;

		for (int i = 0; i < k; ++i) {
			unsigned int curColor = Img->pixels[row * Img->stride / 4 + i];
			int b = curColor & 0xff;
			int g = (curColor & 0xff00) >> 8;
			int r = (curColor & 0xff0000) >> 16;

			sum_b += b;
			sum_g += g;
			sum_r += r;
		}

		for (UINT col = 0; col < Img->Width; ++col)
		{
			int prev_index = col - k / 2;
			int next_index = col + (k / 2) + 1;

			if (prev_index >= 0 && next_index < Img->Width) {
				unsigned int prevColor = Img->pixels[row * Img->stride / 4 + prev_index];
				int b = prevColor & 0xff;
				int g = (prevColor & 0xff00) >> 8;
				int r = (prevColor & 0xff0000) >> 16;

				sum_b -= b;
				sum_g -= g;
				sum_r -= r;

				unsigned int nextColor = Img->pixels[row * Img->stride / 4 + next_index];
				b = nextColor & 0xff;
				g = (nextColor & 0xff00) >> 8;
				r = (nextColor & 0xff0000) >> 16;

				sum_b += b;
				sum_g += g;
				sum_r += r;
			}
			Img->arr_result[row * Img->stride / 4 + col].set_RGBA(sum_r / k, sum_g / k, sum_b / k);
		}
	}

	Bitmap* newBitmap = new Bitmap(Img->Width, Img->Height, Img->stride, PixelFormat32bppARGB,
		(BYTE*)Img->arr_result);
	return newBitmap;
}