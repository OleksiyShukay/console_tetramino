#include "Figure.h"
#include <vector>

using namespace std;

namespace TetrisEngine {
  Figure::Figure(int width, int height, std::vector<bool> *coords) {
	init (m_width = width, m_height = height,  m_coords =  coords);
  }


  Figure::Figure(int width, int height, bool *coord) {
    init(m_width = width, m_height = height,
	  new std::vector<bool> (m_coords, m_coords + (m_width*m_height))//sizeof coords[]
	);
  }

  Figure::Figure(int width, int height) {
    init (m_width = width, m_height = height, 
	  new std::vector<bool>(m_width*m_height, false)
	);
  }

  void Figure::init(int width, int height, std::vector<bool>*coords) {
	m_width = width;
	m_height = height;
	new std::vector<bool>(m_width*m_height);
	
	//copy full vector
	for (int i = 0; i < width; i++) {
	  for (int j = 0; j < height; j++) {
		(*this->m_coords)[i + j * width] = coords->at(i + j * width);
	  }
	}
  }

  bool Figure::hasPointAt(int x, int y) {
	return m_coords->at(x + y * m_width);
  }

  //вертикальный переворот(вдол вертикальной оси)
  Figure *Figure::flipVertically() {
	vector<bool>flippedV(m_width*m_height);
	
	for (int i = 0; i < m_width; i++) {
	  for (int j = 0; j < m_height; j++) {
		flippedV[i + j * m_width] = m_coords->at(i + (m_height - j - 1) * m_width);//отображается вертикально симетри
	  }
	}
	return new Figure(m_width, m_height, &flippedV);
  }
  
  //Горизонтальный переворот
  Figure *Figure::flipHorizontally() {
	vector<bool>flippedH(m_width*m_height);

	for (int i = 0; i < m_width; i++) {
	  for (int j = 0; j < m_height; j++) {
		flippedH[i + j * m_width] = m_coords->at((m_width - i - 1) + j * m_width);
	  }
	}
	return new Figure(m_width, m_height, &flippedH);
  
  }




}

