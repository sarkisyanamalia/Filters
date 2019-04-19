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
	char m_arrChannels[m_arrSize];
public:
	char get_B() const;
	char get_G() const;
	char get_R() const;
	char get_A() const;

	void set_BGR(char value);
	void set_BGR(char value1, char value2, char value3);
	void set_BGRA(char value1, char value2, char value3, char value4);
	void set_BGRA(char value2, char value3, char value4);
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

	void set_kerSize(int value);
	int get_kerSize() const;
	int get_width() const;
	int get_height() const;
	int get_imgSize() const;
	INT get_stride() const;
	Pix* get_arrResult() const;
	Bitmap* get_imgBmp() const;

	void SetImage();
	void CopyImage(myImage* Img);
};

#endif //_IMAGE_H__
