#include "MsgBox.h"

#include <windows.h>
#include <string>
#include <stdio.h>

using std::string;

void MsgBox::MsgBox_TW(string msg, LPCTSTR title, UINT utype)
{
	int width = 1024;
	msg += std::to_string(width);

	LPWSTR ws = new wchar_t[msg.size() + 1];
	copy(msg.begin(), msg.end(), ws);
	ws[msg.size()] = 0;

	MessageBox(NULL, ws, title, utype);
}
