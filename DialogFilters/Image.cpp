#include "Image.h"

//Pix
char Pix::get_B() const {
	return m_arrChannels[1]; 
}
char Pix::get_G() const {
	return m_arrChannels[2];
}
char Pix::get_R() const {
	return m_arrChannels[3]; 
}
char Pix::get_A() const {
	return m_arrChannels[0];
}

void Pix::set_BGR(char value) {
	m_arrChannels[1] = m_arrChannels[2] = m_arrChannels[3] = value;
}
void Pix::set_BGR(char value1, char value2, char value3) {
	//m_arrChannels[1] = value1;
	//m_arrChannels[2] = value2;
	//m_arrChannels[3] = value3;
}
void Pix::set_BGRA(char value1, char value2, char value3, char value4) {
	m_arrChannels[0] = value1;
	m_arrChannels[1] = value2;
	m_arrChannels[2] = value3;
	m_arrChannels[3] = value4;
}
void Pix::set_BGRA(char value2, char value3, char value4) {
	m_arrChannels[1] = value2;
	m_arrChannels[2] = value3;
	m_arrChannels[3] = value4;
}

//myImage
myImage::myImage()
	: m_width(0)
	, m_height(0)
	, m_imgSize(0)
	, m_stride(0)
	, m_arrResult(nullptr) 
	, m_imgBmp(nullptr)
{
}
myImage::~myImage() {
	delete m_arrResult; 
	delete m_imgBmp;
}

void myImage::set_kerSize(int value) {
	m_kerSize = value;
}
int myImage::get_kerSize() const {
	return m_kerSize;
}
int myImage::get_width() const {
	return m_width;
}
int myImage::get_height() const {
	return m_height;
}
int myImage::get_imgSize() const {
	return m_imgSize;
}
INT myImage::get_stride() const {
	return m_stride;
}
Pix* myImage::get_arrResult() const {
	return m_arrResult;
}
Bitmap* myImage::get_imgBmp() const {
	return m_imgBmp;
}

void myImage::SetImage() {
	m_imgBmp = new Bitmap(wstr_file_name.c_str());

	m_width = m_imgBmp->GetWidth();
	m_height = m_imgBmp->GetHeight();
	m_imgSize = m_width * m_height;

	Rect rect(0, 0, m_width, m_height);
	BitmapData bmpData;
	m_imgBmp->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &bmpData);
	UINT* pixels = (UINT*)bmpData.Scan0;
	m_stride = abs(bmpData.Stride);

	m_arrResult = new Pix[m_imgSize];
	for (UINT i = 0; i < m_width; ++i) {
		for (UINT j = 0; j < m_height; ++j)
		{
			unsigned int curColor = pixels[j * m_stride / 4 + i]; 
			int b = curColor & 0xff;
			int g = (curColor & 0xff00) >> 8;
			int r = (curColor & 0xff0000) >> 16;
			int a = (curColor & 0xff000000) >> 24;

			m_arrResult[j * m_stride / 4 + i].set_BGRA(a, b, g, r);
		}
	}

	m_imgBmp->UnlockBits(&bmpData);
}

void myImage::CopyImage(myImage* Img) { 
	m_width = Img->get_width();
	m_height = Img->get_height();
	m_imgSize = Img->get_imgSize();
	m_stride = Img->get_stride();

	m_arrResult = new Pix[Img->get_height() * Img->get_width()];
}