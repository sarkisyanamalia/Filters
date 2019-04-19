#ifndef _BOX_BLUR_H__
#define _BOX_BLUR_H__

#include "GenericFilter.h"
#include "Image.h"

class BoxBlur : public GenericFilter {
public:
	BoxBlur(myImage* Img)
	{
		m_Img = Img;
	}
	~BoxBlur() {
		delete m_Img;
	}

	Pix* Filter() override;
};

#endif //_BOX_BLUR_H__