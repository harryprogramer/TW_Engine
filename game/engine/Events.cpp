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
				exit(EXIT_FAILURE);
			}

		if (fPlayerX < 12.00f) {
			//simple event
		}	
	}
}
