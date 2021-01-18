#pragma once
#include <string>

using std::wstring;

class Engine_TW {
public:
	wstring map;

	int nScreenWidth = 120;
	int nScreenHeight = 40;
	int nMapWidth = 16;
	int nMapHeight = 16;

	float fPlayerX = 14.7f;
	float fPlayerY = 14.09f;
	float fPlayerA = 3.0f;
	float fFOV = 3.14159f / 3.6f;
	float fDepth = 20.0f;
	float fSpeed = 1.5f;

	float fElapsedTime;


	void engine_start();

	void counterSprint();
private:
};
