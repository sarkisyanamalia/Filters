#ifndef _BLACK_WHITE_H__
#define _BLACK_WHITE_H__

#include "GenericFilter.h"
#include "Image.h"

class BW : public GenericFilter {
public:
	BW() {}
	BW(myImage* _Img)
	{
		Img = _Img;
	}
	~BW() {
		delete Img;
	}

	Bitmap* Filter(HWND hDlg) override;
};

#endif //_BLACK_WHITE_H__
