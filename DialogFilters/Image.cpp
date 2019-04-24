#include "Image.h"

//Pix
unsigned char Pix::get_R() const {
	return R; 
}
unsigned char Pix::get_G() const {
	return G;
}
unsigned char Pix::get_B() const {
	return B; 
}
unsigned char Pix::get_A() const {
	return A;
}

void Pix::set_RGB(unsigned char val) { 
	R = G = B = val;
}
void Pix::set_RGB(unsigned char val1, unsigned char val2, unsigned char val3) {
	R = val1;
	G = val2;
	B = val3;
}
void Pix::set_RGBA(unsigned char val1, unsigned char val2, unsigned char val3, unsigned char val4) { 
	R = val1;
	G = val2;
	B = val3;
	A = val4;
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
	delete m_imgBmp; // 
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

	m_arrResult = new Pix[m_height * m_width];
	for (UINT i = 0; i < m_width; ++i) {
		for (UINT j = 0; j < m_height; ++j) {

			unsigned int curColor = pixels[j * m_stride / 4 + i];
			unsigned char b = curColor & 0xff;
			unsigned char g = (curColor & 0xff00) >> 8;
			unsigned char r = (curColor & 0xff0000) >> 16;
			unsigned char a = (curColor & 0xff000000) >> 24;

			m_arrResult[j * m_stride / 4 + i].set_RGBA(r, g, b, a);
		}
	}

	m_imgBmp->UnlockBits(&bmpData);
}

void myImage::CopyImage(myImage* Img) { 
	m_width = Img->get_width();
	m_height = Img->get_height();
	m_imgSize = Img->get_imgSize();
	m_stride = Img->get_stride();

	m_imgBmp = nullptr;
	m_arrResult = new Pix[Img->get_imgSize()]; 
}

void myImage::PositionImg(HWND hDlg, Rect& posRect, RECT rectPCtrl) {

	if (rectPCtrl.right - rectPCtrl.left > m_width) {
		posRect.X = (rectPCtrl.right - rectPCtrl.left - m_width) / 2;
	}
	if (rectPCtrl.bottom - rectPCtrl.top < m_height) {
		posRect.Height = rectPCtrl.bottom - rectPCtrl.top;
	}
	if (rectPCtrl.right - rectPCtrl.left < m_width) {
		posRect.Width = rectPCtrl.right - rectPCtrl.left;
	}
}