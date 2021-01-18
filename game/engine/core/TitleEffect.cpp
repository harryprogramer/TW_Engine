#include "TitleEffect.h"
#include <string>
#include <windows.h>

void TitleEffect::threadTitle()
{
	const char* words[8] = {"died", "kill", "wall", "behind you", "", "llaw", "are you alone??", "œêêææ¿æê€€Ÿæ¹¹œææ¿æ¿"};
	while (1) {
		SetConsoleTitleA(words[rand() % 7 + 1]);
		Sleep(rand() % 2000 + 500);
	}
}
