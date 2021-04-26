#include "Card.h"

Card::Card(int damage, std::string name, int range, std::string objectName, std::string effect, double effectLength, int stamcost, int intcost, int agilcost) : name(name), cardValues(range, damage, stamcost, intcost, agilcost), effect(std::make_pair(effect, effectLength)), objectName(objectName)
{

}
void Card::Cast(Character* caster, Character* target)
{
	target->ModHealth(cardValues.damage);
}

RenderObject* Card::getObj()
{
	return obj;
}

void Card::Assign(RenderObject* object)
{
	this->obj = object;
	object->SetAnim("default");
}