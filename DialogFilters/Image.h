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
	const static int m_arrSize = 4;
	unsigned char m_arrChannels[m_arrSize];
public:
	unsigned char get_B() const;
	unsigned char get_G() const;
	unsigned char get_R() const;
	unsigned char get_A() const;

	void set_BGR(unsigned char);
	void set_BGR(unsigned char, unsigned char, unsigned char);
	void set_BGRA(unsigned char, unsigned char, unsigned char, unsigned char);
	void set_BGRA(unsigned char, unsigned char, unsigned char);
};


class myImage : public GenericImage {
private:
	int m_width; 
	int m_height; 
	int m_imgSize; 
	INT m_stride;
 
	Bitmap* m_imgBmp;
	Pix* m_arrResult;
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
	void PositionImg(HWND, Rect&);
};

#endif //_IMAGE_H__
