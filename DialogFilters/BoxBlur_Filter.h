#ifndef _BOX_BLUR_H__
#define _BOX_BLUR_H__

#include "GenericFilter.h"
#include "Image.h"

class BoxBlur : public GenericFilter {
private:
	int m_kerSize;
public:
	BoxBlur(myImage*, myImage*, int);
	~BoxBlur();

	void VertLineBlur(Pix* arrResult, char channel, int i, int lineSize);
	void HorizLineBlur(Pix* arrResult, char channel, int i, int lineSize);
	void vertical(Pix*);
	void horizontal(Pix*);
	void Filter() override;
};

#endif //_BOX_BLUR_H__