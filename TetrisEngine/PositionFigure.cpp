#include "PositionFigure.h"

namespace TetrisEngine {

  PositionFigure::PositionFigure(int x, int y, Figure *figure) {
	m_x = x;
	m_y = y;
	m_figure = figure;
  }
}