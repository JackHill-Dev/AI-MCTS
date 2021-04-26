#pragma once
#include "Character.h"
#include "Card.h"
#include "Item.h"
#include <deque>
class Player
{
public:
	int currentNode = 0;
	Player();
	~Player();
	std::deque<Card*> deck;
	int GetGold();
	std::vector<Character*>& GetParty() { return mPartyMembers; }
	std::vector<Item*>& GetInventory() { return inventory; }
	void SellItem(Item* item, bool sell);
	void SetGold(int amount);
	void ClearGold() { mGold = 0; }
	void AddToXpPool(const int& xp);
	int& GetXpPool() { return mPartyExperiencePool; }
	void ClearXpPool() { mPartyExperiencePool = 0; }
	void AddGoldLoot(const int& goldLoot);
	int& GetGoldLoot() { return mGoldLoot; }
	void ClearGoldLoot(){ mGoldLoot = 0; }
	void GameCleared() { gameCleared = true; }
	bool GetGameCleared() { return gameCleared; }
	void AddToParty(Character* character);
	void SetupParty(std::vector<Character*> characters);
	void SetDeck(std::deque<Card*> newDeck)
	{
		deck = newDeck;
	}

	// Inventory related functions
	void AddItem(Item* item);
	void RemoveItem(Item* item);

	
	// Shop position grid pos calculation
	void SetInitialGridPos(int pos);
	void GeneratePositions();

	void ClearGridPositions() 
	{
		gridPositions.clear();
		for (auto& item : inventory)
		{
			item->inventoryPos.pos = { 0,0 };
			item->inventoryPos.gridPosFilled = false;
		}
	}
private:

	std::vector<Character*> mPartyMembers;
	std::vector<Item*> inventory;
	int mPartyExperiencePool = 0;
	int mGoldLoot = 0;
	int mGold = 0;

	// Grid pos variables
	std::vector<std::pair<int, int>> gridPositions;
	int mInitialGridPos = 0;
	int mItemCount;
	bool gameCleared = false;

};

