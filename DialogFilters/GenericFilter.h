#ifndef _GENERIC_FILTER_H__
#define _GENERIC_FILTER_H__

#include <Windows.h>
#include "Image.h"

class GenericFilter {
protected:
	myImage* m_Img;
public:
	GenericFilter();
	~GenericFilter();

	virtual Pix* Filter() = 0;
	//void SetNewBmp();
};

#endif //_GENERIC_FILTER_H__
