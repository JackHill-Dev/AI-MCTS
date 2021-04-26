#pragma once
#include "Character.h"

class Card
{
	struct values
	{
		values(double range, int damage, int stamCost, int intCost, int agilCost): range(range), damage(damage), stamCost(stamCost), intCost(intCost), agilCost(agilCost)
		{

		}
		double range;
		int damage;
		int stamCost;
		int intCost;
		int agilCost;
	};

	values cardValues;
	enum TargetType { Self, Enemy };
	
	std::string name;
	TargetType targetType;
	RenderObject* obj = nullptr;
	std::string objectName;
	std::pair<std::string, double> effect;
public:
	std::pair<std::string, double> GetEffect() { return effect; }
	values Values() { return cardValues; }
	Card(int damage, std::string name, int range, std::string objectName, std::string effect, double effectLength, int stamcost, int intcost, int agilcost);
	void Cast(Character* caster, Character* target);
	RenderObject* getObj();
	void Assign(RenderObject* object);
	std::string GetObjName() { return objectName; };
	std::string GetCardName() { return name; };

};

