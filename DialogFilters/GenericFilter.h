#ifndef _GENERIC_FILTER_H__
#define _GENERIC_FILTER_H__

#include <Windows.h>
#include "Image.h"

class GenericFilter {
protected:
	myImage* Img;
public:
	GenericFilter() {};//


	virtual Bitmap* Filter(HWND hDlg) = 0;
};

#endif //_GENERIC_FILTER_H__
