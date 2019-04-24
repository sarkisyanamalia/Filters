#include "BW_Filter.h"

BW::BW(myImage* Img) {
	m_Img = Img;
}

BW::~BW() 
{}

Pix* BW::Filter() { 
	INT str4 = m_Img->get_stride() / 4;
	Pix* arrResult = new Pix[m_Img->get_imgSize()]; 

	for (int i = 0; i < m_Img->get_height(); ++i) {
		for (int j = 0; j < m_Img->get_width(); ++j) {

			int avg = ((int)m_Img->get_arrResult()[i * str4 + j].get_B() +
				(int)m_Img->get_arrResult()[i * str4 + j].get_G() +
				(int)m_Img->get_arrResult()[i * str4 + j].get_R()) / 3;

			arrResult[i * str4 + j].set_BGR(avg);
		}
	}

	return arrResult;
}



