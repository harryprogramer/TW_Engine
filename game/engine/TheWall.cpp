#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <ctime>
using namespace std;

#include <stdio.h>
#include <Windows.h>

#include "TheWall.h"

#include <thread>
#include <string>
#include "Events.h"
#include "core/MsgBox.h"

bool map = false;
bool sounds = true;

int timeRem = 0;

void counter()
{
	while (1)
	{
		Sleep(1000);
		timeRem++;
	}
}

auto tp1 = std::chrono::system_clock::now();
auto tp2 = std::chrono::system_clock::now();



void Engine_TW::counterSprint() {
	int counter = 5;
	while (counter <= 0)
		counter--;
	fSpeed = 2.0f;
	while (counter >= 5)
		counter++;
}

void Engine_TW::engine_start()
{
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	map += L"################"; //1
	map += L"#..............#"; //2
	map += L"#..............#"; //3 
	map += L"#..............#"; //4 
	map += L"#..............#"; //5 
	map += L"#..............#"; //6 
	map += L"#..............#"; //7 
	map += L"#..............#"; //8
	map += L"#..............#"; //9
	map += L"#..............#"; //10
	map += L"#..............#"; //11
	map += L"#..............#"; //12
	map += L"#..............#"; //12
	map += L"#..............#"; //13
	map += L"#..............#"; //14
	map += L"################"; //15 
	/*map += L"#...........................#"; //17
	map += L"#...........................#"; //18 
	map += L"#...........................#"; //19
	map += L"#...........................#"; //20
	map += L"#...........................#"; //21
	map += L"#...........................#"; //22 
	map += L"#...........................#"; //23
	map += L"#...........................#"; //24
	map += L"#...........................#"; //25
	map += L"#...........................#"; //26
	map += L"#...........................#"; //27
	map += L"#...........................#"; //28
	map += L"#...........................#"; //29
	map += L"#############################"; //30
	*/
		
	bool timeStart = true;
	bool debug = true;



	while (1)
	{
		while (1) {
			auto endTime = std::chrono::system_clock::now();
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			fElapsedTime = elapsedTime.count();
			if (GetConsoleWindow() == GetForegroundWindow()) {
				if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
					fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;
				}
				if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
					fPlayerA += (fSpeed * 0.75f) * fElapsedTime;

				if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
				{
					fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
					fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
					if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
					{
						fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
						fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
					}
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
						if (timeStart) {
							timeStart = false;
						}
						fSpeed = 3.5f;
					}
					else {
						fSpeed = 2.0f;
						timeStart = true;
						if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
							fSpeed = 1.0f;
					}
				}
				if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
				{
					fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
					fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
					if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
					{
						fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
						fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
					}
				}
			}
			for (int x = 0; x < nScreenWidth; x++)
			{
				float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
				float fStepSize = 0.1f;		  // Increment size for ray casting, decrease to increase										
				float fDistanceToWall = 1.0f; //                                      resolution

				bool bHitWall = false;		
				bool bBoundary = false;		

				float fEyeX = sinf(fRayAngle); 
				float fEyeY = cosf(fRayAngle);

				
				while (!bHitWall && fDistanceToWall < fDepth)
				{
					fDistanceToWall += fStepSize;
					int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
					int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

					if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
					{
						bHitWall = true;			
						fDistanceToWall = fDepth;
					}
					else
					{
					
						if (map.c_str()[nTestX * nMapWidth + nTestY] == '#')
						{
							// Ray has hit wall
							bHitWall = true;

							vector<pair<float, float>> p;

							// Test each corner of hit tile, storing the distance from
							// the player, and the calculated dot product of the two rays
							for (int tx = 0; tx < 2; tx++)
								for (int ty = 0; ty < 2; ty++)
								{
									// Angle of corner to eye
									float vy = (float)nTestY + ty - fPlayerY;
									float vx = (float)nTestX + tx - fPlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}

							sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

							float fBound = 0.01;
							if (acos(p.at(0).second) < fBound) bBoundary = true;
							if (acos(p.at(1).second) < fBound) bBoundary = true;
							if (acos(p.at(2).second) < fBound) bBoundary = true;
						}
					}
				}

				int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
				int nFloor = nScreenHeight - nCeiling;

				short nShade = ' ';
				if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588;		
				else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
				else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
				else if (fDistanceToWall < fDepth)				nShade = 0x2591;
				else											nShade = ' ';		

				if (bBoundary)		nShade = ' '; // Black it out

				for (int y = 0; y < nScreenHeight; y++)
				{
					if (y <= nCeiling)
						screen[y * nScreenWidth + x] = ' ';
					else if (y > nCeiling && y <= nFloor)
						screen[y * nScreenWidth + x] = nShade;
					else 
					{
						float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
						if (b < 0.25)		nShade = '#';
						else if (b < 0.5)	nShade = 'x';
						else if (b < 0.75)	nShade = '.';
						else if (b < 0.9)	nShade = '-';
						else				nShade = ' ';
						screen[y * nScreenWidth + x] = nShade;
					}
				}
			}
			auto end = std::chrono::system_clock::now();
			if(debug)
				try {
					swprintf_s(screen, 50, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f TIME=%3.2f", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
				}
				catch (exception& e) {
					MsgBox::MsgBox_TW("Debug buffor max size, turning off debug stats", L"Debug Stats Error - The Wall.exe", MB_ICONERROR | MB_OK);
					debug = false;
				}
			/*
			for (int nx = 0; nx < nMapWidth; nx++)2
				for (int ny = 0; ny < nMapWidth; ny++)
				{
					screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
				}
			screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';
			*/


			screen[nScreenWidth * nScreenHeight - 1] = '\0';
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		}
	}

}

