#pragma once
#include "Item.h"
class Consumable :
    public Item
{
public:
    Consumable() {}
    Consumable(std::string name,std::string spriteName, int lvlReq, int cost, int healAmount);
    void OnConsume();

    std::string GetDescription(const bool& sell) override;
    Item* Clone() override { return new Consumable(*this); }
    int mHealAmount = 20;
private:
   

};

