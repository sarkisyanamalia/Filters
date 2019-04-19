#include "GenericImage.h"

GenericImage::GenericImage()
	: m_kerSize(0)
{}

GenericImage::~GenericImage() {
}

std::wstring GenericImage::get_wstr() const {
	return wstr_file_name;
}

std::string GenericImage::get_str() const {
	return str_file_name;
}

void GenericImage::ButtonClick(HWND hDlg) {
	OPENFILENAME ofn;
	char file_name[MAX_PATH];

	ZeroMemory(&file_name, sizeof(file_name));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFilter = "All Files\0*.*\0jpeg\0*.jpeg\0jpg\0*.jpg\0png\0*.png\0bmp\0*.bmp\0";
	ofn.lpstrFile = file_name;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select Image";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);

	//File name cast to string
	str_file_name = file_name;
	//File name cast to wstring
	wstr_file_name = std::wstring(str_file_name.begin(), str_file_name.end());
}
