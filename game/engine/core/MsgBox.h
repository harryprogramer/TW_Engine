#pragma once
#include <string>
#include <windows.h>

using std::string;

class MsgBox
{
public:
	static void MsgBox_TW(std::string msg, LPCTSTR title , UINT utype);
};

