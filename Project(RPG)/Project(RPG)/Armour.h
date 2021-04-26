#pragma once
#include "Item.h"
class Armour :
    public Item
{
public:
    Armour() {}
    Armour(std::string name, std::string spriteName, int lvlReq, int def, int cost);
    int defence = 10;

    std::string GetDescription(const bool& sell) override;


    Item* Clone() override { return new Armour(*this); }

private:
 
};

