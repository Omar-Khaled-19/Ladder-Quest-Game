#pragma once
#include "Card.h"
class Card_5 : public Card
{
private:
	int DiceNum;
public:
	Card_5(const CellPosition& pos);
	
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	
	~Card_5();
};

