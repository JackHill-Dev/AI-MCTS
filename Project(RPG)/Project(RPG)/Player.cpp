#include "Player.h"

Player::Player()
{
	// Workaround for shop grid positioning until i rework it - JP
	gridPositions.reserve(100);
	SetInitialGridPos(80);
	//GeneratePositions();
}

Player::~Player()
{
	for (Character* c : mPartyMembers)
	{
		delete c;
		c = nullptr;
	}
}

void Player::SetGold(int amount)
{
	mGold += amount;
}

void Player::AddToXpPool(const int& xp)
{
	mPartyExperiencePool += xp;
}

void Player::AddGoldLoot(const int& goldLoot)
{
	mGoldLoot += goldLoot;
}

void Player::AddToParty(Character* character)
{
	GetParty().push_back(character);
}

void Player::SetupParty(std::vector<Character*> characters)
{
	mPartyMembers = characters;
}

void Player::AddItem(Item* item)
{
	// Add item to inventory
	inventory.push_back(item);

	// Assign inventory position 
	for (auto p : gridPositions)
	{
		if (item->inventoryPos.gridPosFilled == false)
		{
			item->inventoryPos.pos = p; // Set the item's inventory position to a free grid slot
			item->inventoryPos.gridPosFilled = true; // Make the grid position unavaliable
			 // Remove it from the current grid positions otherwise it will assgin the first grid pos for every item
			gridPositions.erase(std::remove(gridPositions.begin(), gridPositions.end(), p));
		}
	}


	//Update inventory item count for save data
	mItemCount = inventory.size();
}

void Player::RemoveItem(Item* item)
{
	// Free up grid position and add it back to the grid positions
	gridPositions.insert(gridPositions.begin(), item->inventoryPos.pos);

	item->inventoryPos.gridPosFilled = false;

	inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [item](Item* i) {return i == item; }));

	//Update inventory item count for save data
	mItemCount = inventory.size();
}

void Player::SetInitialGridPos(int pos)
{
	mInitialGridPos = pos;
}

void Player::GeneratePositions()
{

	int offsetX = mInitialGridPos;
	int offsetY = 100;

	for (int i = 0; i < gridPositions.capacity(); ++i)
	{
		gridPositions.push_back(std::make_pair(0, 0));
	}

	for (std::pair<int, int>& p : gridPositions)
	{

		if (offsetX >= 360 + mInitialGridPos)
		{
			offsetX = mInitialGridPos;
			offsetY += 110;
		}

		p.first = offsetX;
		p.second = offsetY;

		offsetX += 90;
	}

}

int Player::GetGold()
{
	return mGold;
}

void Player::SellItem(Item* item, bool sell)
{
	if(sell)
		SetGold(item->GetCost());
	else
	{
		int percentReduce =  (item->GetCost() * 0.8);
		SetGold(percentReduce);
	}
	RemoveItem(item);

}
