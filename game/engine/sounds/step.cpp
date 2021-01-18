#include "windows.h"
#include "iostream"
#include <thread>


void step(int timeSleep)
{
	PlaySound(TEXT("game\\sound\\player\\step.wav"), NULL, SND_ASYNC);
	Sleep(timeSleep);
}

bool stepW = true;

void step_normal()
{
	while (1) {
		if (GetConsoleWindow() == GetForegroundWindow()) {
			if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
				if (stepW)
					step(600);
				if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
					stepW = false;
					step(300);
				}
				else {
					stepW = true;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
						step(1000);
						stepW = false;
					}
					else {
						stepW = true;
					}

				}
			}

			if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
				step(600);
		}
	}
}

void step_sprint()
{
	step(100);
}

void step_shift()
{
	step(800);
}
