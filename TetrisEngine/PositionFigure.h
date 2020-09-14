#pragma once

#include "Figure.h"

namespace TetrisEngine {

  class PositionFigure {
  protected:
	Figure *m_figure;
	int m_x; //
	int m_y;  
  public:
    PositionFigure(int, int, Figure*);
	int getX() { 
	  return m_x; 
	}
	int getY() { 
	  return m_y; 
	}
	Figure *getFigure() { 
	  return m_figure; 
	}
	PositionFigure *setX(int x) {
	  m_x = x;
	}
	PositionFigure *setY(int y) {
	  m_y = y;
	}





  };
}