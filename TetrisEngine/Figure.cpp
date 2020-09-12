#include "Figure.h"
#include <vector>

using namespace std;

namespace TetrisEngine {
	Figure::Figure(int width, int height, std::vector<bool> *coords) {
		init(m_width = width, m_height = height, m_coords = coords);
	}


	Figure::Figure(int width, int height, bool *coord) {
		init(m_width = width, m_height = height,
			new std::vector<bool>(m_coords, m_coords + (m_width*m_height))//sizeof coords[]
		);
	}

	Figure::Figure(int width, int height) {
		init(m_width = width, m_height = height,
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

	//Vertical move
	Figure *Figure::flipVertically() {
		vector<bool>flippedV(m_width*m_height);

		for (int i = 0; i < m_width; i++) {
			for (int j = 0; j < m_height; j++) {
				flippedV[i + j * m_width] = m_coords->at(i + (m_height - j - 1) * m_width);
			}
		}
		return new Figure(m_width, m_height, &flippedV);
	}

	//Horizontal move(<-- -->)
	Figure *Figure::flipHorizontally() {
		vector<bool>flippedH(m_width*m_height);

		for (int i = 0; i < m_width; i++) {
			for (int j = 0; j < m_height; j++) {
				flippedH[i + j * m_width] = m_coords->at((m_width - i - 1) + j * m_width);
			}
		}
		return new Figure(m_width, m_height, &flippedH);
	}

	//Rotate left
	Figure *Figure::rotateLeft() {
		//height and width are switched
		int width = m_height; //= 2
		int height = m_width;// = 1
		vector<bool>rotated(width*height);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				rotated[i + j * width] = m_coords->at((m_width - j - 1) + i * m_width);//m_width = height = 2, 
			}
		}
		return new Figure(width, height, &rotated);
	}

	//Rotate Right
	Figure *Figure::rotateRight() {
		//height and width are switched
		//m_height = 2
		//m_width = 1
		int width = m_height;//= 2
		int height = m_width;//= 1
		vector<bool>rotated(width*height);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				rotated[i + j * width] = m_coords->at((m_height - i - 1) * m_width + j);
			}
		}
		return new Figure(width, height, &rotated);

	}

	bool Figure::isIntercept(int x, int y, Figure *figure) {
		int width = min(this->getWidth(), x + figure->getWidth());
		int height = min(this->getHeight(), y + figure->getHeight());
		for (int i = x; i < width; i++) {
			for (int j = y; j < height; j++) {
				if (this->hasPointAt(i, j) && figure->hasPointAt(i - x, j - y)) {
					return true;
				}
			}
		}
		return false;
	}

	Figure *Figure::merge(int x, int y, Figure *figure) {
		int width = this->getWidth();
		int height = this->getHeight();
		int fWidth = figure->getWidth();
		int fHeight = figure->getHeight();
		vector <bool>newCoords(width * height, false);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				newCoords[i + j * width] = (i >= x && j >= y && (i - x) < fWidth && (j - y) < fHeight
					&& figure->hasPointAt(i - x, j - y)) || (i < width && j < height && this->hasPointAt(i, j));
			}
		}
		return new Figure(width, height, &newCoords);
	}

	Figure *Figure::deleteFullLine() {
	  vector<bool>newCoords;
	  for (int j = 0; j < this->getHeight(); j++) {
		bool f = true;
		vector<bool>line;
		for (int i = 0; i < this->getWidth(); i++) {
		  if (!this->hasPointAt(i, j)) {
			f = false;
		  }
		  line.push_back(this->hasPointAt(i, j));
		}
		if (f) {
		  newCoords.insert(newCoords.begin(), this->getWidth(), false);
		  continue;
		}
		newCoords.insert(newCoords.end(), line.begin(), line.end());
	  }

	  return new Figure(this->getWidth(), newCoords.size() / this->getWidth(), &newCoords);
	}
}


