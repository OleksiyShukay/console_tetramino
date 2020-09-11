#pragma once

#include <vector>

namespace TetrisEngine {
  class Figure {
  private:
	std::vector<bool> *m_coords;
	int m_width;
	int m_height;

  protected:
	  void init(int, int, std::vector<bool>*coord);

  public:
	  Figure(int width, int height, std::vector<bool> *coords);
	  Figure(int width, int height, bool *coords);
	  Figure(int width, int height);
	  int getWidth() {
		  return m_width;
	  }

	  int getHeight() {
		  return m_height;
	  }

	  bool hasPointAt(int, int);

	  Figure *rotateLeft();
	  Figure *rotateRight();
	  Figure *flipHorizontally();
	  Figure *flipVertically();

	  bool isIntercept(int x, int y, Figure *figure);
	  Figure *merge(int x, int y, Figure *figure);
	  Figure *deleteFullLine();
  };
 


}