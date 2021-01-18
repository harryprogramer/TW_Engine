#include <Windows.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>

#include <chrono>

#include "Events.h"

#include "TheWall.h"

#include "core/MsgBox.h"

bool timeStart = false;



void Events::events_onUpdate()
{
	while (1) {

		// Handle CCW Rotation
		if (GetAsyncKeyState(VK_F6))
			if (GetAsyncKeyState(VK_CONTROL)) {
				//MsgBox::MsgBox_TW("Instrukcja spod 0x0a62282 odwo³uje siê do pamiêci pod adresem 0xfffffff. Pamiêæ nie mo¿e byæ read.", L"The Wall.exe - B³¹d aplikacji", MB_ICONERROR | MB_OK);
				break;
			}

		if (fPlayerX < 12.00f) {
			//wMsgBox::MsgBox_TW("Instrukcja spod 0x0a62282 odwo³uje siê do pamiêci pod adresem 0xfffffff. Pamiêæ nie mo¿e byæ read.", L"The Wall.exe - B³¹d aplikacji", MB_ICONERROR | MB_OK);
		}	
	}
}
