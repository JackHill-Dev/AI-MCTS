#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include "Armour.h"
#include "Weapon.h"

enum class UnitBackground
{
	NoBackground,
	Villager,
	Scholar, 
	Noble,
};

enum class UnitClass
{
	NoClass,
	Warrior,
	Rogue,
	Mage,
};

struct Statistics
{
	int level = 1;
	UnitBackground bg;
	UnitClass cClass;
	std::pair<int, int> health = { 15,15 }; // current, max
	std::pair<int, int> intelligence = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> strength = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
	std::pair<int, int> experience = { 0, 100 }; // current, next level - EH
};

class Character
{
public:

	Character() {}
	Character(std::string portraitName, std::string objectName, std::string name, UnitClass unitClass, int level, std::pair<int,int> experience, bool dead, std::pair<int, int> health, std::pair<int, int> strength, std::pair<int, int> intelligence, std::pair<int, int> agility);
	~Character();

	int GetLevel();
	int GetHealth();
	Statistics& GetStats() { return mStats; }
	UnitBackground& GetBackground(){ return mStats.bg; }
	UnitClass& GetClass() { return mStats.cClass; }
	std::string GetClassName(UnitClass uClass);
	std::string GetPortraitName() { return mPortraitName; }
	std::string GetObjName() { return objectName; }
	bool GetDeadStatus() { return isDead; }
	bool SetDeadStatus(bool dead);

	void modStat(std::pair<int, int>& statToMod, std::pair<int,int> statMod);
	void LevelUp(int &level, std::pair<int, int> &characterHealth);
	void SetBackground(UnitBackground background);
	void SetClass(UnitClass uClass);
	void SetClassName(UnitClass uClass);
	void SetArmour(Armour* armour);
	void SetWeapon(Weapon* weapon);

	bool ModHealth(int mod);
	void Heal(std::pair<int,int>& health, int healValue);
	void Die();
	
	bool hasLevelled = false;
	bool moving = false;
	Armour* ArmourEquipSlot;
	Weapon* mWeaponEquipSlot;

protected:

	Statistics mStats;
	std::string mClassName;
	std::string mPortraitName;
	std::string objectName;
	std::pair<double, double> target;

private:

	const int levelHealth = 10;
	bool isDead = false;
};

