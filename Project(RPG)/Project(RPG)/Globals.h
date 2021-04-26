#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
#include <time.h>

const int layerNum = 5;

enum Layer
{
	Background = 0,
	Map = 1,
	Game = 2,
	UI = 3,
	Effects = 4
};

enum class Act 
{ 
	Blank, 
	Jump, 
	Click,
	RClick,
	MouseUp,
	MouseUpdate
};

enum Scenes
{
	MainMenu = 0,
	Overworld = 1,
	Combat = 2,
	Shops = 3,
	Party = 4,
	SettingsPage = 5,
	ClassPicker = 6,
	InventoryScreen = 7,
	Boss = 8,
	WinLoseStateScreen = 9,
	NoSceneYet = 10 
};

struct Settings
{
	bool bIsFullScreen = false;
	int mMasterVolume;
	int w, h;
};

struct DefinedCard
{
public:
	DefinedCard(double range, int damage, int staminaCost, int intelligenceCost,  int agilityCost, std::string name, std::string description, std::string picture,std::string animation, double animationLength)
				: range(range), damage(damage), intelligenceCost(intelligenceCost), staminaCost(staminaCost), agilityCost(agilityCost), name(name), description(description), picture(picture), animation(animation), animationLength(animationLength) {};

	int range, damage, intelligenceCost, staminaCost, agilityCost;
	double animationLength;
	std::string name, description, picture, animation;
};
