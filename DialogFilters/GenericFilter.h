#ifndef _GENERIC_FILTER_H__
#define _GENERIC_FILTER_H__

#include <Windows.h>
#include "Image.h"

class GenericFilter {
protected:
	myImage* m_origImg;
	myImage* m_resImg;
public:
	GenericFilter();
	~GenericFilter();

	virtual void Filter() = 0;
};

#endif //_GENERIC_FILTER_H__
