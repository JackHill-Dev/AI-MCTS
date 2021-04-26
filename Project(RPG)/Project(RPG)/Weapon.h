#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    Weapon() {}
    Weapon(std::string name, std::string spriteName, int lvlReq, int atk, int cost);
    int GetAtkPower();

    std::string GetDescription(const bool& sell) override;
    Item* Clone() override { return new Weapon(*this); }
private:
    int mAttackPower = 10;

};

