#ifndef BOARD_INCLUDE
#define BOARD_INCLUDE

#include "Side.h"

class Board 
{
public:
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& RHS); // not in specs but allowed
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
	~Board();

	//void print() const;// gid rid of 
	//void d();
private:
	int m_holes = 0;

	struct Hole {
		int id;
		int beans;
		Side side;

		Hole* across;
		Hole* next;
		Hole* pot;
	};

	Hole* head_N = nullptr;
	Hole* head_S = nullptr;

	Hole* tail_N = nullptr;
	Hole* tail_S = nullptr;

	//Board(const Board& RHS); // not in specs
};	



#endif
