#include "BoxBlur_Filter.h"
#include <thread> 
#include <iostream>

BoxBlur::BoxBlur(myImage* Img, int kerSize)
	: m_kerSize(kerSize)
{
	m_Img = Img;
}

BoxBlur::~BoxBlur()
{}

void BoxBlur::vertical(INT str4, Pix* arrResult) {
	for (int i = 0; i < m_Img->get_width(); ++i) {
		int sum_b = 0,
			sum_g = 0,
			sum_r = 0;

		for (int k = 0; k < m_kerSize; ++k) {
			sum_b += (int)m_Img->get_arrResult()[k * str4 + i].get_B();
			sum_g += (int)m_Img->get_arrResult()[k * str4 + i].get_G();
			sum_r += (int)m_Img->get_arrResult()[k * str4 + i].get_R();
		}
		for (int j = 0; j < m_Img->get_height(); ++j) {

			int prev_index = j - m_kerSize / 2;
			int next_index = j + (m_kerSize / 2) + 1;

			if (prev_index >= 0 && next_index < m_Img->get_height()) {
				sum_b -= (int)m_Img->get_arrResult()[prev_index * str4 + i].get_B();
				sum_g -= (int)m_Img->get_arrResult()[prev_index * str4 + i].get_G();
				sum_r -= (int)m_Img->get_arrResult()[prev_index * str4 + i].get_R();

				sum_b += (int)m_Img->get_arrResult()[next_index * str4 + i].get_B();
				sum_g += (int)m_Img->get_arrResult()[next_index * str4 + i].get_G();
				sum_r += (int)m_Img->get_arrResult()[next_index * str4 + i].get_R();

				arrResult[j * str4 + i].set_BGRA(sum_b / m_kerSize, sum_g / m_kerSize, sum_r / m_kerSize);
			}
		}
	}
}

void BoxBlur::horizontal(INT str4, Pix* arrResult) {
	for (int j = 0; j < m_Img->get_height(); ++j) {
		int sum_b = 0,
			sum_g = 0,
			sum_r = 0;

		for (int k = 0; k < m_kerSize; ++k) {
			sum_b += (int)m_Img->get_arrResult()[j * str4 + k].get_B();
			sum_g += (int)m_Img->get_arrResult()[j * str4 + k].get_G();
			sum_r += (int)m_Img->get_arrResult()[j * str4 + k].get_R();
		}

		for (int i = 0; i < m_Img->get_width(); ++i){

			int prev_index = i - m_kerSize / 2;
			int next_index = i + (m_kerSize / 2) + 1;

			if (prev_index >= 0 && next_index < m_Img->get_width()) {
				sum_b -= (int)m_Img->get_arrResult()[j * str4 + prev_index].get_B();
				sum_g -= (int)m_Img->get_arrResult()[j * str4 + prev_index].get_G();
				sum_r -= (int)m_Img->get_arrResult()[j * str4 + prev_index].get_R();

				sum_b += (int)m_Img->get_arrResult()[j * str4 + next_index].get_B();
				sum_g += (int)m_Img->get_arrResult()[j * str4 + next_index].get_G();
				sum_r += (int)m_Img->get_arrResult()[j * str4 + next_index].get_R();
			}
			arrResult[j * str4 + i].set_BGRA(sum_b / m_kerSize, sum_g / m_kerSize, sum_r / m_kerSize);
		}
	}
}

Pix* BoxBlur::Filter() {
	INT str4 = m_Img->get_stride() / 4;
	Pix* arrResult = new Pix[m_Img->get_imgSize()];
	
	vertical(str4, arrResult);
	horizontal(str4, arrResult);
	//std::thread thrdVert(&BoxBlur::vertical, this, str4, arrResult); 
	//std::thread thrdHoriz(&BoxBlur::horizontal, this, str4, arrResult);

	//thrdVert.join();
	//thrdHoriz.join();
	return arrResult;
}