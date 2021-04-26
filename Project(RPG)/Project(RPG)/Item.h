#pragma once
//#include <string>
#include "RenderObject.h"
#include <string>
#include <sstream>
struct InvPos
{
	std::pair<int, int> pos = std::make_pair(0,0);
	bool gridPosFilled = false;
};

enum ItemType
{
	UNDEFINED = 0,
	ARMOUR,
	WEAPON,
	CONSUMABLE
};
class Item
{
public:
	Item() {}
	Item(std::string name, int lvlReq, int cost);
	~Item();
	virtual Item* Clone() = 0; 
	virtual std::string GetDescription(const bool& sell) = 0;
	std::string GetName() const;
	std::string GetObjName() const;
	int GetCost() const;
	int GetLvlRequirement() const { return mLevelRequirement; }
	ItemType GetType() { return mType; }
	
	InvPos inventoryPos;
protected:
	std::string mName;
	std::string mObjName;
	
	ItemType mType = UNDEFINED;
	int mCost;
	int mLevelRequirement;

	
	
	
	
	
};

