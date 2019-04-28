#include "BW_Filter.h"

BW::BW(myImage* origImg, myImage* resImg) {
	m_origImg = origImg;
	m_resImg = resImg;
}

BW::~BW() 
{}

void BW::Filter() {
	int w = m_origImg->get_width();
	Pix* arrResult = new Pix[m_origImg->get_imgSize()]; 

	for (int i = 0; i < m_origImg->get_height(); ++i) {
		for (int j = 0; j < m_origImg->get_width(); ++j) {

			int avg = ((int)m_origImg->get_arrResult()[i * w + j].get('B') +
				(int)m_origImg->get_arrResult()[i * w + j].get('G') +
				(int)m_origImg->get_arrResult()[i * w + j].get('R')) / 3;

			arrResult[i * w + j].set_BGR(avg);
		}
	}
	memcpy(m_resImg->get_arrResult(), arrResult, m_resImg->get_height() * m_resImg->get_stride());
}



