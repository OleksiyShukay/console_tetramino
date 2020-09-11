#include "TestApp.h"
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>

#define MY_PERFOMANCE_COUNTER

#include "PerformanceCounter.h"

BaseApp::BaseApp(int xSize, int ySize) : X_SIZE(xSize), Y_SIZE(ySize) {
	SMALL_RECT windowSize = { 0, 0, X_SIZE, Y_SIZE };
	COORD windowBufSize = { X_SIZE, Y_SIZE };

	mConsole = GetStdHandle(STD_INPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	if (!SetConsoleScreenBufferSize(mConsole, windowBufSize)) {
		cout << "SetConsoleScreenBufferSize failed with error" << GetLastError() << endl;
	}

	if (!SetConsoleWindowInfo(mConsole, TRUE, &windowSize)) {
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;

	mChiBuffer = (CHAR_INFO*)malloc((X_SIZE + 1)*(Y_SIZE + 1) * sizeof(CHAR_INFO));

	mDwBufferSize.X = X_SIZE + 1;
	mDwBufferSize.Y = Y_SIZE + 1;//размер буфера данных

	mLpWriteRegion.Left = 0;
	mLpWriteRegion.Top = 0; //координаты верхнего левого угла прямоугольника
	mLpWriteRegion.Right = X_SIZE + 1;
	mLpWriteRegion.Bottom = Y_SIZE + 1;//координаты нижнего правого угла прямоугольника

	for (int x = 0; x < X_SIZE + 1; x++) {
	  for (int y = 0; y < Y_SIZE + 1; y++) {
		SetChar(x, y, L'');
	  }
	}
}

BaseApp::~BaseApp() {
	free(mChiBuffer);
}

void BaseApp::SetChar(int x, int y, wchar_t c) {
	mChiBuffer[x + (X_SIZE + 1)*y].Char.UnicodeChar = c;
	mChiBuffer[x + (X_SIZE + 1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
}

wchar_t BaseApp::GetChar(int x, int y) {
  return mChiBuffer[x + (X_SIZE + 1)].Char.AsciiChar;
}

void BaseApp::Render() {
  if (!WriteConsoleOutput(mConsole, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion) 
	printf("WriteConsoleOutput faield - (%d) \n", GetLastError());
  
}

void BaseApp::Run() {
  CStopwatch timer;
  int sum = 0;
  int counter = 0;
  int deltaTime = 0;
  while (1) {
	timer.Start();
	  if (kbhit()) {
		  KeyPressed(getch());
		  if (!FlushConsoleInputBuffer(mConsoleIn))
			  cout << "FlushConsoleInputBuffer with error" << GetLastError();
	  }

	  UpdateF((float)deltaTime / 1000.0f);
	  Render();
	  Sleep(1);

	  while (1) {
	    deltaTime = timer.Now();
		if (deltaTime > 20)
		  break;
	  }

	  sum += deltaTime;
	  counter ++;
	  if (sum >= 1000) {
		  TCHAR szbuff[255];
		  StringCchPrintf(szbuff, 255, TEXT("FPS: %d"), counter);
		  SetConsoleTitle(szbuff);
		  counter = 0;
		  sum = 0;
	  }
  }
}





