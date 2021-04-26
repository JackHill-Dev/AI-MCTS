#include "Weapon.h"

Weapon::Weapon(std::string name, std::string spriteName, int lvlReq, int atk, int cost) : Item(name, lvlReq, cost)
{
	mType = WEAPON;
	mName = name;
	mAttackPower = atk;
	mObjName = spriteName;
	
}

int Weapon::GetAtkPower()
{
	return mAttackPower;
}



std::string Weapon::GetDescription(const bool& sell)
{
	std::ostringstream desc; 
	desc << "Name: " << mName << std::endl;

	if (mName.find("Bow") != std::string::npos)
	{
		desc << "Agility + " << mAttackPower << std::endl;
	}

	else if (mName.find("Staff") != std::string::npos)
	{
		desc << "Intelligence + " << mAttackPower << std::endl;
	}

	else
	{
		desc << "Strength + " << mAttackPower << std::endl;
	}

	desc << "Lvl req. " << mLevelRequirement << std::endl; 
	if (sell)
		desc << "Cost: " << mCost * 0.8;
	else 
		desc << "Cost: " << mCost;
	return desc.str();
}
