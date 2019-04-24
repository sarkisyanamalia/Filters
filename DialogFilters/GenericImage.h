#ifndef _GENERIC_IMAGE_H__
#define _GENERIC_IMAGE_H__

#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "resource.h"

using namespace Gdiplus;

class GenericImage {
protected: 
	std::string str_file_name;
	std::wstring wstr_file_name;
public:
	GenericImage();
	~GenericImage();

	std::wstring get_wstr() const;
	std::string get_str() const;

	//Open a Dialog when clicking on a push button 
	void ButtonClick(HWND);
};

#endif //_GENERIC_IMAGE_H__
