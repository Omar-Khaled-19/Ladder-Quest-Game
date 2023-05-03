#include "Card_6.h"

Card_6::Card_6(const CellPosition& pos) : Card(pos)
{
	cardNumber = 6;
}

void Card_6::ReadCardParameters(Grid* pGrid)
{
	pGrid->PrintErrorMessage("Cell to move to: ");
	
	cellNum = pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	pGrid->GetOutput()->ClearStatusBar();
}

void Card_6::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("Card 6 : Move the player to the cell with cell number: " + to_string(cellNum) );

	pGrid->UpdatePlayerCell(pPlayer, cellNum);
}
