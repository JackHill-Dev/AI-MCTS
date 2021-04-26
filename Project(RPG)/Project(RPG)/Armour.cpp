#include "Armour.h"
Armour::Armour(std::string name, std::string spriteName, int lvlReq, int def,int cost) : Item(name, lvlReq, cost)
{
	mType = ARMOUR;
	mName = name;
	defence = def;
	mObjName = spriteName;
}

std::string Armour::GetDescription(const bool& sell)
{
	std::ostringstream desc;
	desc << "Name: " << mName << std::endl;
	desc << "Health + " << defence << std::endl;
	desc << "Lvl Req. " << mLevelRequirement << std::endl;
	if(sell)
		desc << "Cost: " << mCost * 0.8;
	else
		desc << "Cost: " << mCost;

	return desc.str();
}

