#pragma once
#include "Card.h"

class Card_4 : public Card
{

public:

	Card_4(const CellPosition& pos);

	virtual void Apply(Grid* pGrid, Player* pPlayer);
};

