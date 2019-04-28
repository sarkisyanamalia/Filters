#include "BoxBlur_Filter.h"
#include <thread> 
#include <iostream>

BoxBlur::BoxBlur(myImage* origImg, myImage* resImg, int kerSize)
	: m_kerSize(kerSize)
{
	m_origImg = origImg;
	m_resImg = resImg;
}

BoxBlur::~BoxBlur()
{}

void BoxBlur::VertLineBlur(Pix* arrResult, char channel, int i, int lineSize) {
	int w = m_origImg->get_width();
	int sum = 0;

	for (int k = 0; k < m_kerSize; ++k) {
		sum += (int)m_origImg->get_arrResult()[k * w + i].get(channel);
	}
	for (int j = 0; j < lineSize; ++j) {

		int prev_index = j - m_kerSize / 2;
		int next_index = j + (m_kerSize / 2) + 1;

		if (prev_index >= 0 && next_index < lineSize) {
			sum -= (int)m_origImg->get_arrResult()[prev_index * w + i].get(channel);
			sum += (int)m_origImg->get_arrResult()[next_index * w + i].get(channel);
		}
		arrResult[j * w + i].setChannel(sum / m_kerSize, channel);
	}
}

void BoxBlur::vertical(Pix* arrResult) {
	int lineSize = m_origImg->get_height();
	bool isVert = true;
	for (int i = 0; i < m_origImg->get_width(); ++i) {

		std::thread bTrd(&BoxBlur::VertLineBlur, this, arrResult, 'B', i, lineSize);
		std::thread gTrd(&BoxBlur::VertLineBlur, this, arrResult, 'G', i, lineSize);
		std::thread rTrd(&BoxBlur::VertLineBlur, this, arrResult, 'R', i, lineSize);

		bTrd.join();
		gTrd.join();
		rTrd.join();
	}
}

void BoxBlur::HorizLineBlur(Pix* arrResult, char channel, int i, int lineSize) {
	int w = m_origImg->get_width();
	int sum = 0;

	for (int k = 0; k < m_kerSize; ++k) {
		sum += (int)m_origImg->get_arrResult()[i * w + k].get(channel);
	}
	for (int j = 0; j < lineSize; ++j) {

		int prev_index = j - m_kerSize / 2;
		int next_index = j + (m_kerSize / 2) + 1;

		if (prev_index >= 0 && next_index < lineSize) {
			sum -= (int)m_origImg->get_arrResult()[i * w + prev_index].get(channel);
			sum += (int)m_origImg->get_arrResult()[i * w + next_index].get(channel);
		}
		arrResult[i * w + j].setChannel(sum / m_kerSize, channel);
	}
}

void BoxBlur::horizontal(Pix* arrResult) {
	int lineSize = m_origImg->get_width();
	bool isVert = false;
	for (int i = 0; i < m_origImg->get_height(); ++i) {

		std::thread bTrd(&BoxBlur::HorizLineBlur, this, arrResult, 'B', i, lineSize);
		std::thread gTrd(&BoxBlur::HorizLineBlur, this, arrResult, 'G', i, lineSize);
		std::thread rTrd(&BoxBlur::HorizLineBlur, this, arrResult, 'R', i, lineSize);

		bTrd.join();
		gTrd.join();
		rTrd.join();
	}
}

void BoxBlur::Filter() {
	Pix* arrResult = new Pix[m_origImg->get_imgSize()];
	
	vertical(arrResult);
	horizontal(arrResult);
	memcpy(m_resImg->get_arrResult(), arrResult, m_resImg->get_height() * m_resImg->get_stride());
}