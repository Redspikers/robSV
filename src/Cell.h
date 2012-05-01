/*
 * Cell.h
 *
 *  Created on: 29 avr. 2012
 *      Author: Koudja
 */

#ifndef CELL_H_
#define CELL_H_

class Cell {
	public:
		Cell(int x, int y, bool m_blocked);
		~Cell();

		void setX(int x);
		int getX();

		void setY(int y);
		int getY();

		void setBlocked(bool blocked);
		bool isBlocked();

	private:
		int x;
		int y;
		bool blocked;
		//What is inside this node ?
		bool cd;
		bool robot; //other robot !
};

#endif /* CELL_H_ */
