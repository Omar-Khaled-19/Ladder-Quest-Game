#pragma once
#include"Card.h"
class Card_9 : public Card
{



public:
	Card_9(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);


	virtual void Apply(Grid* pGrid, Player* pPlayer);


	virtual ~Card_9();

};

