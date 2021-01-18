#include <iostream>
#include <string>
#include <windows.h>

#define _WIN32_WINNT 0x0500
#define SCREENWIDTH getmaxx()

using namespace std;

void show_menu(const char* s)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSBSize;
	NewSBSize = GetLargestConsoleWindowSize(hOut);
	int l = strlen(s);
	int pos = (int)((NewSBSize.X - l) / 2);
	for (int i = 0; i < pos; i++)
		cout << " ";

	cout << s;
}