#ifndef _BLACK_WHITE_H__
#define _BLACK_WHITE_H__

#include "GenericFilter.h"
#include "Image.h"

class BW : public GenericFilter {
public:
	BW(myImage*, myImage*);
	~BW();

	void Filter() override;
};

#endif //_BLACK_WHITE_H__
