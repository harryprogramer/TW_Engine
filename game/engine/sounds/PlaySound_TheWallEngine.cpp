#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

#include "PlaySound_TheWallEngine.h"

using namespace std;

void ReadWavFileIntoMemory(string fname, BYTE** pb, DWORD* fsize) {
    ifstream f(fname, ios::binary);

    f.seekg(0, ios::end);
    int lim = f.tellg();
    *fsize = lim;

    *pb = new BYTE[lim];
    f.seekg(0, ios::beg);

    f.read((char*)*pb, lim);

    f.close();
}

void EngineSoundApi::PlaySound_TWE()
{
    DWORD dwFileSize;
    BYTE* pFileBytes;
    ReadWavFileIntoMemory("D:\\OpenAL 1.1 SDK\\samples\\media\\fiveptone.wav", &pFileBytes, &dwFileSize);

    BYTE* pDataOffset = (pFileBytes + 40);

    cout << "Length: " << dwFileSize << endl;

    float fVolume = 0.02;

    __int16* p = (__int16*)(pDataOffset + 8);
    cout << sizeof(*p) << endl;
    for (int i = 80 / sizeof(*p); i < dwFileSize / sizeof(*p); i++) {
        p[i] = (float)p[i] * fVolume;
    }

    cout << "PlaySound" << endl;
    //PlaySound((LPCSTR)pFileBytes, NULL, SND_MEMORY);
}

