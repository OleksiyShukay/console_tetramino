#pragma once

#include "Figure.h";
#include "PositionFigure.h"
namespace TetrisEngine {
  class Field {
  private:
    PositionFigure *m_currentFigure;
	Figure *m_nextFigure;
	Figure *m_mainFigure;
	int m_width;
	int m_heigth;
	int m_fihished;
  public:
	Field(int w, int h);
	Field();
	void nextStep();
	PositionFigure *getCurrentFigure();
	Figure *getNextFigure() {
	  return m_nextFigure;
	}
	Figure *getMainFigure() {
	  return m_mainFigure;
	}
	void moveFigureLeft();
	void moveFigureRight();
	void moveFigureDown();
	void rotateFigure();
	int getWidth() {
	  return m_width;
	}
	int getHeight() {
	  return m_heigth;
	}
	bool outOfBounds(int, int,  Figure* );
	bool isFinished() {
			return m_fihished;
	}
  protected:
	Figure *generateRandomFigure();
	void init();
	void takeNextFigure();

  };
}