#include "BW_Filter.h"

Pix* BW::Filter() {
	INT str4 = m_Img->get_stride() / 4;
	Pix* arrResult = new Pix[m_Img->get_width() * m_Img->get_height()];

	for (int i = 0; i < m_Img->get_width(); ++i) {
		for (int j = 0; j < m_Img->get_height(); ++j) {

			int b = m_Img->get_arrResult()[j * str4 + i].get_B();
			int g = m_Img->get_arrResult()[j * str4 + i].get_G();
			int r = m_Img->get_arrResult()[j * str4 + i].get_R();
			int avg = (b + g + r) / 3;

			arrResult[j * str4 + i].set_BGR(avg);
		}
	}
	return arrResult;
}



