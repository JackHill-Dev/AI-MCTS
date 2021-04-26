#pragma once
#include <map>
#include "Globals.h"
#include "RenderObject.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Item.h"
#include "Armour.h"
#include "Weapon.h"
#include "Consumable.h"
// Define objects with an identifier and a render object that refers to a specific spritesheet.
const std::map<std::string,RenderObject*> definedObjects
{
	{
		// Character Sprite objects
		{"femaleObj",new RenderObject("female")},
		{"mageObj",new RenderObject("mage")},
		{"mageSprObj",new RenderObject("magSpr")},
		{"maleObj", new RenderObject("male")},
		{"nobleSpriteObj", new RenderObject("nobleSprite")},
		{"rogSprObj",new RenderObject("rogSpr")},
		{"scholarSpriteObj", new RenderObject("scholarSprite")},
		{"villagerSpriteObj", new RenderObject("villagerSprite")},
		{"warSprObj",new RenderObject("warSpr")},
		{"daemonBoss", new RenderObject("daemonSpr")},
		
		// Portrait Objects 

		{"bossPortraitObj", new RenderObject("bossPortrait")},
		{"ClericObj",new RenderObject("cleric")},
		{"merchantPortraitObj",new RenderObject("merchantPortrait")},
		{"playerPortraitObj",new RenderObject("playerPortrait")},
		{"portrait", new RenderObject("malePortrait")},
		{"RogueObj",new RenderObject("rogue")},
		{"WarriorObj",new RenderObject("warrior")},
		{"WizardObj",new RenderObject("wizard")},

		// Item Objects

		{"armourObj",new RenderObject("armour")},
		{"defaultItemObj", new RenderObject("defaultItem")},
		{"clothArmourObj",new RenderObject("clothArmour")},
		{"leatherArmourObj",new RenderObject("leatherArmour")},
		{"chainArmourObj",new RenderObject("chainArmour")},
		{"plateArmourObj",new RenderObject("plateArmour")},
		{"potionObj",new RenderObject("potion")},
		{"daggerObj",new RenderObject("dagger")},
		{"shortSwordObj",new RenderObject("shortSword")},
		{"longSwordObj",new RenderObject("longSword")},
		{"compoundBowObj", new RenderObject("compoundBow")},
		{"enchantersStaffObj", new RenderObject("enchantersStaff")},
		{"holyBowObj", new RenderObject("holyBow")},
		{"seraphStaffObj", new RenderObject("seraphStaff")},
		{"simpleBowObj", new RenderObject("simpleBow")},
		{"simpleStaffObj", new RenderObject("simpleStaff")},

		// Background Objects

		{"castleBackgroundObj", new RenderObject("castleBackground")},
		{"characterFrameObj",new RenderObject("characterFrame")},
		{"forestBGObj",new RenderObject("forestBG")},
		{"forestFightSceneBg", new RenderObject("fightSceneForest")},
		{"gameClearObj", new RenderObject("gameClear")},
		{"gameLogoMenuObj", new RenderObject("gameLogoMenu")},
		{"itemFrameObj",new RenderObject("itemFrame")},
		{"legendObj", new RenderObject("legend")},
		{"mainMenuBGObj",new RenderObject("mainMenuBG")},
		{"OptionsBackgroundObj", new RenderObject("OptionsBackground")},
		{"OverlayObj", new RenderObject("overlay")},
		{"overworldObj", new RenderObject("overworld")},
		{"scrollBgObj", new RenderObject("scrollBg")},
		{"settingsBgObj", new RenderObject("settingsBg")},
		{"ShopBGObj",new RenderObject("shopBg")},
		{"tileObj", new RenderObject("tile")},	
		{"stoneTileObj", new RenderObject("stone-tile")},
		{"TreeObj", new RenderObject("tree")},
		{"toolTipBgObj", new RenderObject("toolTipBg")},
		{"statBackgroundObj", new RenderObject("statBackground")},
			
		// Button Objects

		{"ApplyBtnObj", new RenderObject("ApplyBtn")},
		{"armyViewerButtonObj", new RenderObject("armyViewerButton")},
		{"backBtnObj", new RenderObject("backBtn")},
		{"backTxtBtnObj", new RenderObject("backTxtBtn")},
		{"CloseBtnObj", new RenderObject("closeBtn")},
		{"ConfirmButtonObj", new RenderObject("confirmButton")},
		{"ContinueButtonObj", new RenderObject("continueButton")},
		{"EndTurnButtonObj", new RenderObject("endTurnButton")},
		{"exitButtonObj", new RenderObject("exitButton")},
		{"inventoryButtonObj", new RenderObject("inventoryButton")},
		{"legendButtonObj", new RenderObject("legendButton")},
		{"menuButtonObj", new RenderObject("menuButton")},
		{"newGameButtonObj", new RenderObject("newGameButton")},
		{"quitBtnObj", new RenderObject("quitBtn")},
		{"resetButtonObj", new RenderObject("resetButton")},
		{"settingsBtnObj", new RenderObject("settingsBtn")},
		{"StartBtnObj", new RenderObject("startBtn")},
		{"upButtonObj", new RenderObject("upButton")},
		{"yesTxtBtnObj", new RenderObject("yesTxtBtn")},

		// Node Objects

		{"battleNodeObj", new RenderObject("battleNode")},
		{"bossNodeObj", new RenderObject("bossNode")},
		{"shopNodeObj", new RenderObject("shopNode")},
		{"nodeObj", new RenderObject("startNode")},

		// Card Objects

		{"cardObj", new RenderObject("card")},
				
		// More Traditional UI Objects

		{"barBgObj", new RenderObject("barBg")},
		{"barFillObj", new RenderObject("barFill")},	
		{"checkBoxObj", new RenderObject("checkBox")},
		{"resCollapsedObj", new RenderObject("resCollapsed")},

		// Effects Objects 

		{"MagicObj", new RenderObject("Magic")},
		{"swordSlashEffectObj", new RenderObject("swordSlashEffect")},
		{"healImageObject", new RenderObject("health")},
		{"ArrowShotObj", new RenderObject("ArrowShot")},
		{"BossAttackObj", new RenderObject("BossAttack")},

	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		// Character Spritesheets

		{"female", new SpriteSheet("Assets/Sprites/Female 01-1.png", 96, 128, 32, 32, false)},
		{"mage", new SpriteSheet("Assets/Sprites/Male/Male 12-1.png",96, 128, 32, 32, false)},
		{"magSpr", new SpriteSheet("Assets/Sprites/MageSprite.png", 96, 128, 32, 32, false)},
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, false)},	
		{"nobleSprite", new SpriteSheet("Assets/Sprites/Male/Male 06-4.png", 96, 128, 32, 32, false)},
		{"rogSpr", new SpriteSheet("Assets/Sprites/ArcherSprite.png", 96, 128, 32, 32, false)},
		{"scholarSprite", new SpriteSheet("Assets/Sprites/Male/Male 08-1.png", 96, 128, 32, 32, false)},
		{"villagerSprite", new SpriteSheet("Assets/Sprites/Male/Male 10-2.png", 96, 128, 32, 32, false)},		
		{"warSpr", new SpriteSheet("Assets/Sprites/WarriorSprite.png", 96, 128, 32, 32, false)},
		{"daemonSpr", new SpriteSheet("Assets/Sprites/Daemon.png",385, 875, 75, 75, false)},

		// Portrait Spritesheets

		{"bossPortrait", new SpriteSheet("Assets/Sprites/Portraits/BalzathorCropped.png", 357, 364, 357, 364, false)},
		{"cleric", new SpriteSheet("Assets/Sprites/Portraits/Cleric.png",177, 243, 177, 243, false)},
		{"malePortrait", new SpriteSheet("Assets/Portrait.png",	357, 364, 357, 364, false)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, false)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, false)},		
		{"rogue", new SpriteSheet("Assets/Sprites/Portraits/Rogue.png",177, 243, 177, 243, false)},
		{"warrior", new SpriteSheet("Assets/Sprites/Portraits/Warrior.png",177, 243, 177, 243,false)},
		{"wizard", new SpriteSheet("Assets/Sprites/Portraits/Wizard.png",177, 243, 177, 243, false)},

		// Item Spritesheets

		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, false)},
		{"defaultItem", new SpriteSheet("Assets/Sprites/helmet.png", 32, 32, 32, 32, false)},
		{"leatherArmour", new SpriteSheet("Assets/Sprites/Items/leatherArmour.png",64, 64, 64, 64, false)},
		{"chainArmour", new SpriteSheet("Assets/Sprites/Items/chainmail.png",64, 64, 64, 64, false)},
		{"plateArmour", new SpriteSheet("Assets/Sprites/Items/Plate_Armour.png",64, 64, 64, 64, false)},
		{"clothArmour", new SpriteSheet("Assets/Sprites/Items/clothArmour.png",64, 64, 64, 64, false)},
		{"potion", new SpriteSheet("Assets/Sprites/Items/healthPotion.png",48, 48, 48, 48, false)},
		{"dagger", new SpriteSheet("Assets/Sprites/Items/dagger.png",64, 64, 64, 64, false)},
		{"shortSword", new SpriteSheet("Assets/Sprites/Items/shortSword.png",64, 64, 64, 64, false)},
		{"longSword", new SpriteSheet("Assets/Sprites/Items/longSword.png",64, 64, 64, 64, false)},
		{"compoundBow", new SpriteSheet("Assets/Sprites/Items/CompoundBow.png", 64, 64, 64, 64, false)},
		{"enchantersStaff", new SpriteSheet("Assets/Sprites/Items/EnchantersStaff.png", 64, 64, 64, 64, false)},
		{"holyBow", new SpriteSheet("Assets/Sprites/Items/HolyBow.png", 64, 64, 64, 64, false)},
		{"seraphStaff", new SpriteSheet("Assets/Sprites/Items/SeraphStaff.png", 64, 64, 64, 64, false)},
		{"simpleBow", new SpriteSheet("Assets/Sprites/Items/SimpleBow.png", 64, 64, 64, 64, false)},
		{"simpleStaff", new SpriteSheet("Assets/Sprites/Items/SimpleStaff.png", 64, 64, 64, 64, false)},

		

		// Background Spritesheets

		{"castleBackground", new SpriteSheet("Assets/Backgrounds/CastleInterior1.png", 1920, 1080, 1920, 1080, false)},
		{"characterFrame", new SpriteSheet("Assets/Backgrounds/CharacterFrame.png",228, 624, 228, 624, false)},
		{"fightSceneForest", new SpriteSheet("Assets/ForestFight.png",700, 400, 700, 400, false)},
		{"forestBG", new SpriteSheet("Assets/forestbackground.png",1280, 720, 1280, 720, false)},
		{"gameClear", new SpriteSheet("Assets/Backgrounds/GameClear.png", 650, 345, 650, 345, false)},
		{"gameLogoMenu", new SpriteSheet("Assets/Backgrounds/GameLogoMenu_1920_1080.png", 1920, 1080, 1920, 1080, false)},
		{"itemFrame", new SpriteSheet("Assets/Backgrounds/ItemFrame.png",85, 105, 85, 105, false)},
		{"legend", new SpriteSheet("Assets/Backgrounds/Legend.png", 303, 500, 303, 500, false)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, false)},
		{"OptionsBackground", new SpriteSheet("Assets/Sprites/Buttons/OptionsBackground.png",	240, 32, 240, 32, false)},
		{"settingsBg", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720_Blurred.png", 1280, 720, 1280, 720, false)},
		{"overlay", new SpriteSheet("Assets/Backgrounds/Overlay.png", 1280, 720, 1280, 720, false)},
		{"overworld", new SpriteSheet("Assets/Backgrounds/map.png", 2048, 1536, 2048, 1536, true)},
		{"scrollBg", new SpriteSheet("Assets/Backgrounds/ResizedScroll.png", 1280, 720, 1280, 720, false)},
		{"shopBg", new SpriteSheet("Assets/Backgrounds/ShopBg.png",1280, 720, 1280, 720, false)},		
		{"tile", new SpriteSheet("Assets/grass-tile.png", 32, 32, 32, 32, false)},	
		{"toolTipBg", new SpriteSheet("Assets/Backgrounds/TooltipBackground.png", 48, 48, 48, 48, false)},
		{"tile", new SpriteSheet("Assets/grass-tile.png", 32, 32, 32, 32, false)},		
		{"stone-tile", new SpriteSheet("Assets/Backgrounds/stone-tile.png", 32, 32, 32, 32, false)},
		{"tree", new SpriteSheet("Assets/Sprites/baum.png", 128,128,128,128,false)},
		{"statBackground", new SpriteSheet("Assets/Backgrounds/CombatStatsBackground.png", 350, 121, 350, 121, false)},

		
		// Button Spritesheets		
		
		{"ApplyBtn", new SpriteSheet("Assets/Sprites/Buttons/Apply_Button.png",	200, 55, 200, 55, false)},
		{"armyViewerButton", new SpriteSheet("Assets/Sprites/Buttons/Army_viewer_btn1.png", 200, 34, 200, 34, false)},
		{"backBtn", new SpriteSheet("Assets/Sprites/Buttons/back_symbol_buttonCropped.png", 81, 67, 81, 67, false)},
		{"backTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Back_Button.png", 200, 55, 200, 55, false)},
		{"confirmButton", new SpriteSheet("Assets/Sprites/Buttons/Confirm.png", 200, 55, 200,55, false)},
		{"continueButton", new SpriteSheet("Assets/Sprites/Buttons/Continue_Button.png", 200, 55, 200, 55, false)},
		{"closeBtn", new SpriteSheet("Assets/Sprites/Buttons/CloseButton.png",100, 100, 100, 100, false)},
		{"endTurnButton", new SpriteSheet("Assets/Sprites/Buttons/EndTurnButton.png", 200,55,200,55, false)},
		{"exitButton", new SpriteSheet("Assets/Sprites/Buttons/exitButton.png", 200, 55, 200, 55, false)},
		{"inventoryButton", new SpriteSheet("Assets/Sprites/Buttons/inventoryBtn1.png", 200, 34, 200, 34, false)},
		{"legendButton", new SpriteSheet("Assets/Sprites/Buttons/LegendButton.png", 200, 55, 200, 55, false)},
		{"menuButton", new SpriteSheet("Assets/Sprites/Buttons/MenuBtn1.png", 200, 34, 200, 34, false)},
		{"newGameButton", new SpriteSheet("Assets/Sprites/Buttons/New_Game.png", 200, 55, 200, 55, false)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/quit_resized.png",200, 55, 200, 55, false)},
		{"resetButton", new SpriteSheet("Assets/Sprites/Buttons/Reset.png", 200, 55, 200, 55, false)},
		{"settingsBtn", new SpriteSheet("Assets/Sprites/Buttons/SettingsButton.png",200, 55, 200, 55, false)},
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartButton.png",200, 55, 200, 55, false)},
		{"upButton", new SpriteSheet("Assets/Sprites/Buttons/UpButton.png", 16, 15, 16, 15, false)},
		{"yesTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Yes_Button.png", 200, 55, 200, 55, false)},


		// Node Spritesheets

		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, false)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, false)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, false)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, false)},

		// Card Spritesheets

		{"card", new SpriteSheet("Assets/Sprites/Card/CardTemplateNew.png",230, 322, 230, 322, false)},
		{"SlashCard", new SpriteSheet("Assets/Sprites/Card/SlashCard.png", 600, 951, 600, 951,false)},
		{"BowAndArrow", new SpriteSheet("Assets/Sprites/Card/ShootCard.png", 600, 951, 600, 951, false )},
		{"healCard", new SpriteSheet("Assets/Sprites/Card/HealCard.png", 600, 951, 600, 951, false)},
		{"magicCard", new SpriteSheet("Assets/Sprites/Card/Magic_Card.png", 600, 951, 600, 951, false)},

		// More Traditional UI Spritesheets

		{"barBg", new SpriteSheet("Assets/Sprites/Bar_Bg.png",	176, 32, 176, 32, false)},
		{"barFill", new SpriteSheet("Assets/Sprites/Bar_fill.png",	176, 32, 176, 32, false)},		
		{"checkBox", new SpriteSheet("Assets/Sprites/Buttons/CheckBox.png",	128, 64, 64, 64, false)},		
		{"resCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-01.png",	240, 32, 240, 32, false)},
		
		// Effects Spritesheets
		{"swordSlashEffect", new SpriteSheet("Assets/Sprites/Effects/SwordSlash.png", 3248, 190, 406, 190,true)},
		{"Magic", new SpriteSheet("Assets/Sprites/Effects/MagicAttack.png", 3530, 390, 353, 390,true)},
		{"health", new SpriteSheet("Assets/Sprites/Effects/heal.png", 4032, 92, 192, 92,true)},
		{"ArrowShot", new SpriteSheet("Assets/Sprites/Effects/ArrowShot.png", 2420, 246, 220, 246, true)},
		{"BossAttack", new SpriteSheet("Assets/Sprites/Effects/BossAttack.png", 10231, 397, 787, 397, true)},
						
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		// Unit Animations

		{"mage", {// a defined vector of animations, make sure the name matches the sheet
		Animation("LookUp", {std::make_pair(0,0)}),
		Animation("LookLeft", {std::make_pair(0,1)}),
		Animation("LookRight", {std::make_pair(0,2)}),
		Animation("LookDown", {std::make_pair(0,3)}),

		Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
		Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
		Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
		Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),

		}},

		{"magSpr",
				{
					Animation("LookUp", {std::make_pair(0,0)}),
					Animation("LookLeft", {std::make_pair(0,1)}),
					Animation("LookRight", {std::make_pair(0,2)}),
					Animation("LookDown", {std::make_pair(0,3)}),

					Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
					Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
					Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
					Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
				}
		},

		{"male", {// a defined vector of animations, make sure the name matches the sheet
		Animation("LookUp", {std::make_pair(0,0)}),
		Animation("LookLeft", {std::make_pair(0,1)}),
		Animation("LookRight", {std::make_pair(0,2)}),
		Animation("LookDown", {std::make_pair(0,3)}),

		Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
		Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
		Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
		Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),

		}},

		{"rogSpr",
				{
					Animation("LookUp", {std::make_pair(0,0)}),
					Animation("LookLeft", {std::make_pair(0,1)}),
					Animation("LookRight", {std::make_pair(0,2)}),
					Animation("LookDown", {std::make_pair(0,3)}),

					Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
					Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
					Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
					Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
				}
		},

		{"warSpr",
			{
				Animation("LookUp", {std::make_pair(0,0)}),
				Animation("LookLeft", {std::make_pair(0,1)}),
				Animation("LookRight", {std::make_pair(0,2)}),
				Animation("LookDown", {std::make_pair(0,3)}),

				Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
				Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
				Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
				Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
			}
		},

		{"daemonSpr",
			{
				Animation("LookDown", {std::make_pair(0,0)}),
				Animation("LookLeft", {std::make_pair(1,0)}),
				Animation("LookRight", {std::make_pair(2,0)}),
				Animation("LookUp", {std::make_pair(4,0)}),

				Animation("WalkDown", {std::make_pair(0,0), std::make_pair(0,1),std::make_pair(0,2),std::make_pair(0,3), std::make_pair(0,4)}),
				Animation("WalkLeft", {std::make_pair(1,0),std::make_pair(1,1),std::make_pair(1,2), std::make_pair(1,3), std::make_pair(1,4)}),
				Animation("WalkRight", {std::make_pair(2,0),std::make_pair(2,1),std::make_pair(2,2),std::make_pair(2,3),std::make_pair(2,4)}),
				Animation("WalkUp", {std::make_pair(4,0),std::make_pair(4,1),std::make_pair(4,2),std::make_pair(4,3),std::make_pair(4,4)}),
			}
		},

		// UI Animations

		{"checkBox", {Animation("Checked", {std::make_pair(1,0)})}},
		{"startBtn", {Animation("Hover", {std::make_pair(1,0)})}},

		// Background Animations

		{"tile",
			{
				Animation("Grass", {std::make_pair(0,0)})
			}
		},

		// Effects Animations

		{"Magic", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
		{"swordSlashEffect", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
		{"ArrowShot", {Animation("default", {std::make_pair(3,0), std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0),std::make_pair(7,0)})}},
		{"health", {Animation("default", {std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0),std::make_pair(7,0),std::make_pair(8,0), std::make_pair(9,0)})}},
		{"BossAttack", {Animation("default", {std::make_pair(0,0),std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0), std::make_pair(6,0)})}},
	}
};

const std::map<std::string, DefinedCard> definedCards
{
	// Name,  Range, damage, costs(STR, INT AGI) , card name, flavour, picture, animation object, animation length
	{"magicCard",{4, 7, 0, 5, 0, "Magic", "Magically assail the enemy for 7 damage, costs 5 intelligence", "Magic_Card" ,"MagicObj", 0.75}},
	{"arrowCard", {5, 5, 0, 0, 5, "Shoot", "Pepper your foe with arrows for 5 damage, costs 5 agility", "Shootcard", "ArrowShotObj", 0.75}},
	{"slashCard",{1.5, 10, 5, 0, 0, "Slash", "Slash the enemy for 10 damage, costs 5 strength", "SlashCard" ,"swordSlashEffectObj", 0.5}},	
	{"healCard",{1.5, -15, 0, 10, 0, "Heal", "Heal the target for 15 health, costs 10 intelligence", "HealCard" ,"healImageObject", 1.25}},
	{"bossCard",{ 1.5, 10, 5, 0, 0, "BossAttack", "The Boss cleaves it's foe for 10 damage, costs 5 strength", "SlashCard", "BossAttackObj", 1}},
};

const std::map<std::string, Item*> definedItems
{
	// Weapons
	{"Dagger",new Weapon("Dagger", "daggerObj", 1, 3, 100)}, // name, spriteName, Level requirement, atk power, cost
	{"Short Sword", new Weapon("Short Sword", "shortSwordObj", 2, 7, 150)},
	{"Long Sword", new Weapon("Long Sword", "longSwordObj", 3, 10, 200)}, 
	{"Simple Bow", new Weapon("Simple Bow", "simpleBowObj", 1, 3, 100)},
	{"Compound Bow", new Weapon("Compound Bow", "compoundBowObj", 2, 7, 150)},
	{"Holy Bow", new Weapon("Holy Bow", "holyBowObj", 3, 10, 200)},
	{"Simple Staff", new Weapon("Simple Staff", "simpleStaffObj", 1, 3, 100)},
	{"Enchanters Staff", new Weapon("Enchanters Staff", "enchantersStaffObj", 2, 7, 150)},
	{"Seraph Staff", new Weapon("Seraph Staff", "seraphStaffObj", 3, 10, 200)},

	// Armour
	{"Cloth Armour", new Armour("Cloth Armour", "clothArmourObj", 1, 5, 50 )}, // name, spriteName, def, cost
	{"Leather Armour", new Armour("Leather Armour", "leatherArmourObj", 2, 10, 150 )} ,
	{"Chainmail Armour",  new Armour("Chainmail Armour", "chainArmourObj", 3, 20, 250 )} ,
	{"Plate Armour",  new Armour("Plate Armour", "plateArmourObj", 4, 30, 300 )} ,

	// Consumables
	{"Health Potion",  new Consumable("Health Potion", "potionObj", 1, 100, 20)}
};





		
	