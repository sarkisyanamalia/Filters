#ifndef _BOX_BLUR_H__
#define _BOX_BLUR_H__

#include "GenericFilter.h"
#include "Image.h"

class BoxBlur : public GenericFilter {
private:
	int m_kerSize;
public:
	BoxBlur(myImage*, int);
	~BoxBlur();

	void vertical(INT, Pix*);
	void horizontal(INT, Pix*);
	Pix* Filter() override;
};

#endif //_BOX_BLUR_H__