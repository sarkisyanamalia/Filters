#ifndef _BOX_BLUR_H__
#define _BOX_BLUR_H__

#include "GenericFilter.h"
#include "Image.h"

class BoxBlur : public GenericFilter {
public:
	BoxBlur(myImage* _Img)
	{
		Img = _Img;
	}
	~BoxBlur() {
		delete Img;
	}

	Bitmap* Filter(HWND hDlg) override;
};

#endif //_BOX_BLUR_H__