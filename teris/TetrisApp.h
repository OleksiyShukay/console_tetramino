#pragma once
#include "BaseApp.h"
#include "TetrisEngine/Field.h"
#include <string.h>

using namespace TetrisEngine;

class TetrisApp :
  public BaseApp {
  protected:
    float m_timer;
    float m_stepTime;
	bool m_started;
	Field *m_field;
	  
	void drawField();
	void drawFigure(int, int, Figure*);
	void drawFigure(int, int, Figure*, bool);
	void drawText(int, int, const char*);
	void startGame();

  public:
	  TetrisApp();
	  ~TetrisApp();
	  virtual void KeyPressed(int btnCode);
	  virtual void UpdateF(float deltaTime);


};
