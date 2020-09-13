#include "TetrisApp.h"
#include "BaseApp.h"
#include "TetrisEngine/Field.cpp"
#include "TetrisEngine/PositionedFigure.cpp"
#include "TetrisEngine/Figure.cpp"

#include <string>
//#include <sstream>

using namespace TetrisEngine;
using namespace std;

TetrisApp::TetrisApp():BaseApp(60, 80) {
  m_started = false;
  this->startGame();
}

TetrisApp::~TetrisApp(void) {
  delete m_field;
}

void TetrisApp::startGame() {
  m_field = new Field(10, 30);
  m_timer = 0.0;
  m_stepTime = 0.5;
}

void TetrisApp::KeyPressed(int btnCode) {
	if (!m_started) {
		m_field->nexStep();
		m_started = true;
		//remove "Press any key" message
		drawText(1, 1, "      ");
	}
	if (m_field->isFinished()) {
		if (btnCode == 113) {
			exit(0);
		}
		else if (btnCode == 114) {
			startGame();
		}
		return;
	}
	switch (btnCode) {
	  case 75: {//left
	    m_field->moveFigureLeft();
		break;
	  }
	  case 77: {//right
		m_field->moveFigureRight();
		break;
	  }
	  case 80: {//d
		m_field->moveFigureDown();
		m_timer = 0;
		break;
	  }
	  case 113: {//q
		exit(0);
		break;
	  }
	  case 72: //up
	  case 32: {//space
		m_field->rotateFigure();
		break;
	  }
	  case 0: {//specials
		break;
	  }
	  default: {
		char message[135];
		sprintf_s(message, "Button code: %d  ", btnCode);
		drawText(20, 1, message);
	  }

	}
}

void TetrisApp::UpdateF(float deltaTime) {
  if (!m_started) {
	drawField();
	drawText(1, 1, "Press any key to start game!");

	return;
  }
  if (m_field->isFinished()) {
	drawText(1, 1, "GAME OVER");

	return;
  }

  m_timer += deltaTime;
  while (m_timer > m_stepTime) {
	  m_field->nextStep();
	  m_timer -= m_stepTime;
  }
  drawField();
  char message[135];
  sprintf_s(message, "Delta time: %f", deltaTime);
  drawText(40, 0, message);
}

void TetrisApp::drawText(int x, int y, const char *ch) {
  int len = strlen(ch);
  for (int i = 0; i < len; i++) {
	SetChar(x + i, y, *(ch + i));
	
  }
}

void TetrisApp::drawField() {
  SetChar(0, 0, L'*');
  SetChar(m_field->getWidth() + 1, 0, L'>');
  SetChar(0, m_field->getHeight() + 1, L'<');
  SetChar(m_field->getWidth() + 1, m_field->getHeight() + 1, L'=');
  for (int y = 0; y < m_field->getHeight(); y++) {
	SetChar(0, y + 1, L'|');
	SetChar(m_field->getWidth() + 1, y + 1, L'|');
  }
  for (int x = 0; x < m_field->getWidth(); x++) {
	SetChar(x + 1, 0, L'-');
	SetChar(x + 1, m_field ->getHeight() + 1, L'-');
	for (int y = 0; y < m_field->getHeight(); y++) {
	  SetChar(x + 1, y + 1, L'');
	}
  }

  drawFigure(m_field->getWidth() + 5, 2, new Figure(5, 5), false);
  drawFigure(m_field->getWidth() + 5, 2, m_field->getNextFigure());
  drawFigure(1, 1, m_field->getMainFigure());

  PositionedFigure *figure = m_field->getCurrentFigure();

  if (figure == NULL) {
		return;
  }
  //plus borders
  drawFigure(figure->getX() + 1, figure->getY() + 1, figure->getFigure());
}

void TetrisApp::drawFigure(int x, int y, Figure *figure) {
  drawFigure(x, y, figure, true);
}

void TetrisApp::drawFigure(int x, int y, Figure *figure, bool transparent) {
  for (int i = 0; i < figure->getWidth(); i++) {
	for (int j = 0; j < figure->getHeight(); j++) {
	  wchar_t symbol = L'@';
	    if (!figure->hasPointAt(i, j)) {
		  if (transparent) {
			continue;
		}
		symbol = L' ';
	  }
	  SetChar(x + i, y + j, symbol);
	}
  }
}


