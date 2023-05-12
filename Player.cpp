#include "Player.h"

#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

void Player::DecrementWallet(int decrementAmount)
{
	SetWallet(GetWallet() - decrementAmount);
}

void Player::ResetWallet()
{
	wallet = 100;
}

void Player::ResetPlayerPosition()
{
	pCell = new Cell(8, 0);
}

void Player::ResetPlayerParameters()
{
	ResetWallet();
	ResetPlayerPosition();
	turnCount = 0;
}

int Player::GetTurnCount() const
{
	return turnCount;
}


int Player::GetDiceNum() const
{
	return justRolledDiceNum;
}

int Player::GetStepCount() const
{
	return stepCount;
}

void Player::SetPrison(bool p)
{
	Prison = p;
}

bool Player::GetPrison()
{
	return Prison;
}

void Player::SetCard_3(bool c)
{
	Card_3 = c;
}

void Player::SetCard_4(bool c)
{
	Card_4 = c;
}

bool Player::GetCard_3()
{
	return Card_3;
}

bool Player::GetCard_4()
{
	return Card_4;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);   // By Amr

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once

	turnCount++;

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	if (turnCount == 3)
	{
		SetWallet(wallet + (diceNumber * 10));
		turnCount = 0;
		return;
	}

	if (GetWallet() <= 1)
		return;

	// 3- Set the justRolledDiceNum with the passed diceNumber

	CellPosition newCellPos = pCell->GetCellPosition();

	justRolledDiceNum = ((newCellPos.GetCellNum() + diceNumber) <= 99) ? diceNumber : (99 - newCellPos.GetCellNum());

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"



	newCellPos.AddCellNum(justRolledDiceNum); // Get the updated cellposition (vCell and hCell)
	// Set the updated cellposition (vCell and hCell)


// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

	pGrid->UpdatePlayerCell(pGrid->GetCurrentPlayer(), newCellPos);

	// 6- Apply() the game object of the reached cell (if any)
	GameObject* pGobject = pCell->GetGameObject();
	if (pGobject)
		pGobject->Apply(pGrid, pGrid->GetCurrentPlayer());

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (newCellPos.GetCellNum() == 99)
	{
		pGrid->PrintErrorMessage("You Won! Click to end game.. ");
		pGrid->SetEndGame(true);
	}
}



void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}