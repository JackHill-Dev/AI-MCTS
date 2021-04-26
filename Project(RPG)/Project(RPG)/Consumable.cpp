#include "Consumable.h"

Consumable::Consumable(std::string name,std::string spriteName, int lvlReq, int cost, int healAmount) : Item(name, lvlReq, cost)
{
	mType = ItemType::CONSUMABLE;
	mObjName = spriteName;
	mHealAmount = healAmount;
}

void Consumable::OnConsume()
{
}

std::string Consumable::GetDescription(const bool& sell)
{
	std::ostringstream desc;
	desc << "Name: " << mName << std::endl;
	desc << "Heals " << mHealAmount << " health" << std::endl;
	desc << "Lvl Req. " << mLevelRequirement << std::endl;
	if (sell)
		desc << "Cost: " << mCost * 0.8;
	else
	{
		desc << "Cost: " << mCost;
	}
	return desc.str();
}
