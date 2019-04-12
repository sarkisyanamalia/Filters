#ifndef _IMAGE_H__
#define _IMAGE_H__

#include "GenericImage.h"

class Pix {
private:
	const static int arr_size = 4;
	char arr_RGBA[arr_size];
public:
	Pix() {
		for (int i = 0; i < arr_size; ++i) {
			arr_RGBA[i] = 0;
		}
	}

	void set_RGB(char value) {
		arr_RGBA[1] = arr_RGBA[2] = arr_RGBA[3] = value;
	}
	void set_RGB(char value1, char value2, char value3) {
		arr_RGBA[1] = value1;
		arr_RGBA[2] = value2;
		arr_RGBA[3] = value3;
	}
	void set_RGBA(char value1, char value2, char value3, char value4 = 255) {
		arr_RGBA[0] = value1;
		arr_RGBA[1] = value2;
		arr_RGBA[2] = value3;
		arr_RGBA[3] = value4;
	}
	void set_RGBA(char value) {
		arr_RGBA[0] = arr_RGBA[1] = arr_RGBA[2] = value;
		arr_RGBA[3] = 255; //
	}
};

/*struct PixType { //enum
	int B = 0,
		G = 1,
		R = 2,
		A = 3;
};*/


class myImage : public GenericImage {
public://
	int scrPos;

	int Width;
	int Height;
	INT stride;
	UINT*  pixels;
	Bitmap* orig_img;
	Pix* arr_result;
public:
	myImage() {
	}
	~myImage() {
	}

	void SetImage() {
		orig_img = new Bitmap(wstr_file_name.c_str()); 

		Width = orig_img->GetWidth();
		Height = orig_img->GetHeight();

		Rect rect(0, 0, Width, Height);
		BitmapData* bitmapData = new BitmapData;
		orig_img->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, bitmapData);
		pixels = (UINT*)bitmapData->Scan0;
		stride = abs(bitmapData->Stride);

		arr_result = new Pix[Width * Height];
		for (int i = 0; i < Width * Height; ++i) {
			arr_result[i].set_RGBA(0);
		}

		orig_img->UnlockBits(bitmapData);
		delete bitmapData; //
	}
};

#endif //_IMAGE_H__
