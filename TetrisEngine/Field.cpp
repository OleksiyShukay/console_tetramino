#include "Field.h"
#include "Figure.h"
#include "PositionFigure.h"

namespace TetrisEngine {
  Figure *Field::generateRandomFigure() {
	Figure *figure;
	switch (rand() % 5) {
	  case 0: {
		bool coords[6] = {
		  1,1,1,
		  0,1,0
		};
		figure = new Figure(3, 2, coords);
		break;
	  }
	  case 1: {
		bool coords[6] = {
		  1,1,1,
		  0,0,1
		};
		figure = new Figure(3, 2, coords);
		break;
	  }
	  case 2: {
		bool coords[6] = {
		  1,1,0,
		  0,1,1
		};
		figure = new Figure(3, 2, coords);
		break;
	  }
	  case 3: {
		bool coords[4] = {
		  1,1,
		  1,1
		};
		figure = new Figure(2, 2, coords);
		break;
	  }
	  case 4: {
		bool coords[4] = {
		  1,1,1,1
		};
		figure = new Figure(4, 1, coords);
		break;
	  }
    }

	for (int i = 0; i < (rand() % 5); i++) {
	  switch (rand() % 4) {
		case 0: {
			figure = figure->flipHorizontally();
			break;
		}
		case 1: {
			figure = figure->flipVertically();
			break;
		}
		case 2: {
			figure = figure->rotateLeft();
			break;
		}
		case 3: {
			figure = figure->rotateRight();
			break;
		}
	  }
	}
	return figure;
  }

  void Field::init() {
	m_nextFigure = this->generateRandomFigure();
	m_currentFigure = NULL;

	m_mainFigure = new Figure(m_width, m_heigth);
	m_fihished = false;
  }

  Field::Field(int w, int h) {
	m_width = w;
	m_heigth = h;
	init();
  };

  Field::Field() {
	m_width = 5;
	m_heigth = 5;
	init();
  };

  void Field::nextStep() {
	if (m_currentFigure == NULL) {
	  takeNextFigure();
	  return;
	}

	moveFigureDown();
	m_mainFigure = m_mainFigure->deleteFullLine();
  }

  void Field::takeNextFigure() {
	m_currentFigure = new PositionFigure((int)(m_width / 2), 0, m_nextFigure);
	m_nextFigure = generateRandomFigure();
	m_mainFigure = m_mainFigure->deleteFullLine();
	
	if (outOfBounds(m_currentFigure->getX(), m_currentFigure->getY, m_currentFigure->getFigure())) {
	  m_fihished = true;
	}
  }

  void Field::moveFigureLeft() {
	int newX = m_currentFigure->getX() - 1;
	if (outOfBounds(newX, m_currentFigure->getY(), m_currentFigure->getFigure())) {
	  return;
	}
	this->m_currentFigure->setX(newX);
  }

  void Field::moveFigureRight() {
    int newX = m_currentFigure->getX() + 1;
	if (outOfBounds(newX, m_currentFigure->getY(), m_currentFigure->getFigure())) {
	  return;
	}
	this->m_currentFigure->setX(newX);
  }

  void Field::moveFigureDown() {
    int newY = m_currentFigure->getY() + 1;
	if (outOfBounds(m_currentFigure->getX(), newY, m_currentFigure->getFigure())) {
	  m_mainFigure = m_mainFigure->merge( m_currentFigure->getX(), m_currentFigure->getY(), m_currentFigure->getFigure());
	  takeNextFigure();
	  return;
	}
	m_currentFigure->setY(newY);
  }

  void Field::rotateFigure() {
	Figure *newFigure = m_currentFigure->getFigure()->rotateLeft();

	if (outOfBounds(m_currentFigure->getX(), m_currentFigure->getY(), newFigure)) {
	  return;
	}

	m_currentFigure = new PositionFigure(m_currentFigure->getX(), m_currentFigure->getY(), newFigure);
  }

  bool Field::outOfBounds(int x, int y, Figure *figure) {
    return x + figure->getWidth() > m_width || x < 0 || y < 0 || y + figure->isIntercept(x, y, figure);
  }
}