#ifndef _IMAGE_H__
#define _IMAGE_H__

#include "GenericImage.h"

/*struct PixType { //enum
	int B = 0,
		G = 1,
		R = 2,
		A = 3;
};*/

class Pix {
private:
	unsigned char R, G, B, A;
public:
	unsigned char get_R() const;
	unsigned char get_G() const;
	unsigned char get_B() const;
	unsigned char get_A() const;

	void set_RGB(unsigned char);
	void set_RGB(unsigned char, unsigned char, unsigned char);
	void set_RGBA(unsigned char, unsigned char, unsigned char, unsigned char);
};


class myImage : public GenericImage {
private:
	int m_width; 
	int m_height; 
	int m_imgSize; 
	INT m_stride;
 
	Pix* m_arrResult;
	Bitmap* m_imgBmp;
public:
	myImage();
	~myImage();

	int get_width() const;
	int get_height() const;
	int get_imgSize() const;
	INT get_stride() const;
	Pix* get_arrResult() const;
	Bitmap* get_imgBmp() const;

	void SetImage();
	void CopyImage(myImage*);
	void PositionImg(HWND, Rect&, RECT);
};

#endif //_IMAGE_H__
