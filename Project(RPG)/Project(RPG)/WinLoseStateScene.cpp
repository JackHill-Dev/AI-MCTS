#include "WinLoseStateScene.h"

WinLoseStateScene::WinLoseStateScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pBackground = AddObject("scrollBgObj", 640, 360, Map);

	Victory_Music = Mix_LoadMUS("Assets/Music/VictoryWindlessSlopes.mp3");
	Defeat_Music = Mix_LoadMUS("Assets/Music/Game-over-silence.mp3");

	Victory_Sfx = Mix_LoadWAV("Assets/SFX/VictorySfx.wav");
	Button_Sfx = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	Error_Sfx = Mix_LoadWAV("Assets/SFX/ErrorSound.wav");
}

void WinLoseStateScene::SetUpButtons()
{
	pMenuButton = AddObject("menuButtonObj", 800, 510, UI);
	pMenuButton->SetVisible(false);

	pQuitButton = AddObject("exitButtonObj", 480, 510, UI);
	pQuitButton->SetVisible(false);

	pContinueButton = AddObject("ContinueButtonObj", 640, 510, UI);
	pContinueButton->SetVisible(false);

	pConfirmButton = AddObject("ConfirmButtonObj", 800, 510, UI);
	pConfirmButton->SetVisible(false);

	pRejectButton = AddObject("resetButtonObj", 480, 510, UI);
	pRejectButton->SetVisible(false);

	pStrengthButton = AddObject("upButtonObj", 840, 400, UI);

	pAgilityButton = AddObject("upButtonObj", 840, 430, UI);

	pIntelligenceButton = AddObject("upButtonObj", 840, 460, UI);

	pStatButtons.push_back(pStrengthButton);
	pStatButtons.push_back(pAgilityButton);
	pStatButtons.push_back(pIntelligenceButton);

	pAllButtons.push_back(pMenuButton);
	pAllButtons.push_back(pQuitButton);
	pAllButtons.push_back(pContinueButton);
	pAllButtons.push_back(pConfirmButton);
	pAllButtons.push_back(pRejectButton);
	pAllButtons.push_back(pStrengthButton);
	pAllButtons.push_back(pAgilityButton);
	pAllButtons.push_back(pIntelligenceButton);

	for (auto button : pAllButtons)
	{
		button->SetVisible(false);
	}
}

// Checks if any are alive(You win) or if the party is all dead(Game over) and then calls the relevant starting view,
// Win state or lose state - EH
void WinLoseStateScene::PickState()
{
	std::vector<Character*> party = mgr->GetPlayer()->GetParty();

	pFirstCharacter = new PlayerCharacter;
	pSecondCharacter = new PlayerCharacter;
	pThirdCharacter = new PlayerCharacter;
	pTargetCharacter = new PlayerCharacter;

	for (auto member : party)
	{
		mNames.push_back(member->GetClassName(member->GetClass()));
	}

	pCharacters.clear();

	pLeftSprite = AddObject(party[0]->GetObjName(), 320, 360, UI);
	pLeftSprite->SetScale(std::make_pair(2, 2));
	pLeftSprite->SetVisible(false);
	pFirstCharacter->pCharacter = mgr->GetPlayer()->GetParty().at(0);
	pFirstCharacter->rObj = pLeftSprite;
	pLeftSprite = nullptr;
	pCharacters.push_back(pFirstCharacter);

	pCentreSprite = AddObject(party[1]->GetObjName(), 640, 360, UI);
	pCentreSprite->SetScale(std::make_pair(2, 2));
	pCentreSprite->SetVisible(false);
	pSecondCharacter->pCharacter = party[1];
	pSecondCharacter->rObj = pCentreSprite;
	pCentreSprite = nullptr;
	pCharacters.push_back(pSecondCharacter);

	pRightSprite = AddObject(party[2]->GetObjName(), 960, 360, UI);
	pRightSprite->SetScale(std::make_pair(2, 2));
	pRightSprite->SetVisible(false);
	pThirdCharacter->pCharacter = party[2];
	pThirdCharacter->rObj = pRightSprite;
	pRightSprite = nullptr;
	pCharacters.push_back(pThirdCharacter);

	if (std::any_of(party.begin(), party.end(), [party](Character* pCharacter)
		{
			return pCharacter->GetDeadStatus() == false;
		}))
	{
		mgr->PlaySFX(Victory_Sfx, 0, 1);
		mgr->FadeInMusic(Victory_Music, -1, mgr->fadeTime);
		mgr->GetPlayer()->SetGold(mgr->GetPlayer()->GetGoldLoot());
		mDividedXp = mgr->GetPlayer()->GetXpPool() / pCharacters.size();
		for (auto character : pCharacters)
		{
			character->pCharacter->modStat(character->pCharacter->GetStats().experience, { mDividedXp, 0 });
		}
		if (mgr->GetPlayer()->GetGameCleared() == false)
		{
			SetUpWinState();
		}
		else
		{
			SetUpGameClearState();
		}
	}
	else
	{
		mgr->FadeInMusic(Defeat_Music, 1, mgr->fadeTime); // This one doesn't loop - EH
		SetUpLoseState();
	}

	party.clear();
}

void WinLoseStateScene::Load()
{
	mLayers[UI].clear();
	SetUpButtons();
	//PickState();
}

void WinLoseStateScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	for (auto character : pCharacters)
	{
		if (character->pCharacter->hasLevelled == false && character->pCharacter->GetDeadStatus() == false)
		{
			character->rObj->Untint();
		}
	}

	if (act == Act::MouseUpdate)
	{
		for (auto button : pAllButtons)
		{
			if (button->InBounds(mousePos.first, mousePos.second))
			{
				OnHover(button);
			}
			else
			{
				OnLeave(button);
			}
		}
	}

	if (act == Act::Click)
	{
		for (auto& character : pCharacters)
		{
			if (character->rObj->InBounds(mousePos.first, mousePos.second) && character->pCharacter->hasLevelled == true)
			{
				if (character->rObj->IsVisible() == true)
				{
					mgr->PlaySFX(Button_Sfx, 0, 1);
					SetUpLevelUpState(character);
				}
			}
		}

		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			if (pMenuButton->IsVisible() == true)
			{
				if(mgr->GetPlayer()->GetGameCleared())
					std::ofstream("Savedata.Json").clear();
				mgr->PlaySFX(Button_Sfx, 0, 1);
				mgr->LoadScene(Scenes::MainMenu);
				mgr->GetPlayer()->GetParty().clear();
			}
		}

		else if (pQuitButton->InBounds(mousePos.first, mousePos.second))
		{
			if (pQuitButton->IsVisible() == true)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				mgr->Quit();
			}
		}

		else if (pContinueButton->InBounds(mousePos.first, mousePos.second) && pContinueButton->IsVisible() == true &&
			std::all_of(pCharacters.begin(), pCharacters.end(), [](PlayerCharacter* pc)
				{
					return pc->pCharacter->hasLevelled == false;
				}))
		{
			mgr->PlaySFX(Button_Sfx, 0, 1);
			mgr->GetPlayer()->ClearXpPool();
			mgr->GetPlayer()->ClearGoldLoot();
			for (auto character : pCharacters)
			{
				delete character;
			}
			mgr->LoadScene(Scenes::Overworld);

			pCharacters.clear();
			mNames.clear();
			

			for (auto button : pAllButtons)
			{
				button->Untint();
			}
		}
		else
		{
			if (pContinueButton->InBounds(mousePos.first, mousePos.second) && pContinueButton->IsVisible() == true && std::any_of(pCharacters.begin(), pCharacters.end(), [](PlayerCharacter* pc)
				{
					return pc->pCharacter->hasLevelled == true;
				}))
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
				mSceneText[8]->text = "PLEASE LEVEL UP ALL CHARACTERS";
				
			}
		}

		

		if (pStrengthButton->InBounds(mousePos.first, mousePos.second) && pStrengthButton->IsVisible() == true)
		{
			if (mStatPoints != 0)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				--mStatPoints;
				++mStrPoints;
				mSceneText[2]->text = "STAT POINTS: " + std::to_string(mStatPoints);
				mSceneText[3]->text = "STRENGTH:" + mSceneText[3]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().strength.second + mStrPoints);
			}
			else
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
				mSceneText[6]->text = "INSUFFICIENT STAT POINTS. PLEASE RESET FOR REALLOCATION";
			}
		}

		else if (pAgilityButton->InBounds(mousePos.first, mousePos.second) && pAgilityButton->IsVisible() == true)
		{
			if (mStatPoints != 0)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				--mStatPoints;
				++mAgiPoints;
				mSceneText[2]->text = "STAT POINTS: " + std::to_string(mStatPoints);
				mSceneText[4]->text = "AGILITY:" + mSceneText[4]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().agility.second + mAgiPoints);
			}
			else
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
				mSceneText[6]->text = "INSUFFICIENT STAT POINTS. PLEASE RESET FOR REALLOCATION";
			}
		}

		else if (pIntelligenceButton->InBounds(mousePos.first, mousePos.second) && pIntelligenceButton->IsVisible() == true)
		{
			if (mStatPoints != 0)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				--mStatPoints;
				++mIntPoints;
				mSceneText[2]->text = "STAT POINTS: " + std::to_string(mStatPoints);
				mSceneText[5]->text = "INTELLIGENCE:" + mSceneText[5]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().intelligence.second + mIntPoints);
			}
			else
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
				mSceneText[6]->text = "INSUFFICIENT STAT POINTS. PLEASE RESET FOR REALLOCATION";
			}
		}

		else if (pRejectButton->InBounds(mousePos.first, mousePos.second) && pRejectButton->IsVisible() == true)
		{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				mStatPoints = 2;
				mStrPoints = 0;
				mAgiPoints = 0;
				mIntPoints = 0;
				mSceneText[2]->text = "STAT POINTS: " + std::to_string(mStatPoints);
				mSceneText[3]->text = "STRENGTH:" + mSceneText[3]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().strength.second + mStrPoints);
				mSceneText[4]->text = "AGILITY:" + mSceneText[4]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().agility.second + mAgiPoints);
				mSceneText[5]->text = "INTELLIGENCE:" + mSceneText[5]->AddTab() + std::to_string(pTargetCharacter->pCharacter->GetStats().intelligence.second + mIntPoints);
		}

		else if (pConfirmButton->InBounds(mousePos.first, mousePos.second) && pConfirmButton->IsVisible() == true)
		{
			if (mStatPoints == 0)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				pTargetCharacter->pCharacter->modStat(pTargetCharacter->pCharacter->GetStats().strength, { mStrPoints, mStrPoints });
				pTargetCharacter->pCharacter->modStat(pTargetCharacter->pCharacter->GetStats().agility, { mAgiPoints, mAgiPoints });
				pTargetCharacter->pCharacter->modStat(pTargetCharacter->pCharacter->GetStats().intelligence, { mIntPoints, mIntPoints });
				pTargetCharacter->pCharacter->LevelUp(pTargetCharacter->pCharacter->GetStats().level, pTargetCharacter->pCharacter->GetStats().health);
				mStrPoints = 0;
				mAgiPoints = 0;
				mIntPoints = 0;
				SetUpWinState();
			}
			else
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
				mSceneText[6]->text = "PLEASE ASSIGN ALL STAT POINTS";
			}
		}
	}
}

void WinLoseStateScene::OnHover(RenderObject* rObj)
{
	rObj->Tint(Lime);
}

void WinLoseStateScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void WinLoseStateScene::SetUpWinState()
{
	pContinueButton->SetVisible(true);
	pConfirmButton->SetVisible(false);
	pRejectButton->SetVisible(false);

	for (auto button : pStatButtons)	
	{
		button->SetVisible(false);
	}

	pCharacters[0]->rObj->SetPos({320, 360});
	pCharacters[1]->rObj->SetPos({640, 360});
	pCharacters[2]->rObj->SetPos({960, 360});

	for (auto character : pCharacters)
	{
		character->rObj->SetVisible(true);

		if (character->pCharacter->GetStats().experience.second <= character->pCharacter->GetStats().experience.first)
		{
			character->rObj->tint = Gold;
			character->pCharacter->hasLevelled = true;
		}
		else if (character->pCharacter->GetDeadStatus() == true && character->pCharacter->hasLevelled == false)
		{
			character->rObj->tint = DimGray;
		}
		else
		{
			character->rObj->Untint();
		}

		

	}

	mSceneText.clear();

	pMenuButton->SetVisible(false);
	pQuitButton->SetVisible(false);

	mHeader.text = "YOU WIN";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "SPOILS OF WAR";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = mNames[0];
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText4.text = "XP + " + std::to_string(mDividedXp);
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(320, 440);
	mFlavourText4.SetTextScale(100, 30);

	mFlavourText2.text = mNames[1];
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText5.text = "XP + " + std::to_string(mDividedXp);
	mFlavourText5.textColor = SDL_Color{ 0,0,0 };
	mFlavourText5.pos = std::make_pair<int>(640, 440);
	mFlavourText5.SetTextScale(100, 30);

	mFlavourText3.text = mNames[2];
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFlavourText6.text = "XP + " + std::to_string(mDividedXp);
	mFlavourText6.textColor = SDL_Color{ 0,0,0 };
	mFlavourText6.pos = std::make_pair<int>(960, 440);
	mFlavourText6.SetTextScale(100, 30);

	mGoldLootText.text = "GOLD FOUND: " + std::to_string(mgr->GetPlayer()->GetGoldLoot());
	mGoldLootText.textColor = SDL_Color{ 0,0,0 };
	mGoldLootText.pos = std::make_pair<int>(640, 470);
	mGoldLootText.SetTextScale(200, 40);

	mLevelUpText1.text = "LEVEL UP!";
	mLevelUpText1.textColor = SDL_Color{ 0,0,0 };
	mLevelUpText1.pos = std::make_pair<int>(320, 320);
	mLevelUpText1.SetTextScale(100, 30);

	if (pCharacters[0]->pCharacter->hasLevelled == true)
	{
		mLevelUpText1.isVisible = true;
	}
	else
	{
		mLevelUpText1.isVisible = false;
	}
	mLevelUpText2.text = "LEVEL UP!";
	mLevelUpText2.textColor = SDL_Color{ 0,0,0 };
	mLevelUpText2.pos = std::make_pair<int>(640, 320);
	mLevelUpText2.SetTextScale(100, 30);

	if (pCharacters[1]->pCharacter->hasLevelled == true)
	{
		mLevelUpText2.isVisible = true;
	}
	else
	{
		mLevelUpText2.isVisible = false;
	}
	mLevelUpText3.text = "LEVEL UP!";
	mLevelUpText3.textColor = SDL_Color{ 0,0,0 };
	mLevelUpText3.pos = std::make_pair<int>(960, 320);
	mLevelUpText3.SetTextScale(100, 30);

	if (pCharacters[2]->pCharacter->hasLevelled == true)
	{
		mLevelUpText3.isVisible = true;
	}
	else
	{
		mLevelUpText3.isVisible = false;
	}


	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFlavourText4);
	mSceneText.push_back(&mFlavourText5);
	mSceneText.push_back(&mFlavourText6);
	mSceneText.push_back(&mLevelUpText1);
	mSceneText.push_back(&mLevelUpText2);
	mSceneText.push_back(&mLevelUpText3);
	mSceneText.push_back(&mGoldLootText);
	mSceneText.push_back(&mFooterInstruction);
}

void WinLoseStateScene::SetUpLoseState()
{
	for (auto character : pCharacters)
	{
		character->rObj->SetVisible(true);
		character->rObj->tint = DimGray;
	}

	pCharacters[0]->rObj->SetPos({ 320, 360 });
	pCharacters[1]->rObj->SetPos({ 640, 360 });
	pCharacters[2]->rObj->SetPos({ 960, 360 });
	
	pMenuButton->SetVisible(true);
	pQuitButton->SetVisible(true);
	mSceneText.clear();

	mHeader.text = "YOU LOSE";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "TRY AGAIN?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = mNames[0];
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = mNames[1];
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = mNames[2];
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFooterInstruction);
}

void WinLoseStateScene::SetUpLevelUpState(PlayerCharacter* &pc)
{
	pTargetCharacter = pc;
	mStatPoints = 2;

	for (auto character : pCharacters)
	{
			character->rObj->SetVisible(false);
	}

	pConfirmButton->SetVisible(true);
	pRejectButton->SetVisible(true);
	pContinueButton->SetVisible(false);

	for (auto button : pStatButtons)
	{
		button->SetVisible(true);
	}

	pc->rObj->SetVisible(true);
	pc->rObj->SetPos({ 640,350 });

	mSceneText.clear();

	mHeader.text = "LEVEL UP!";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = pc->pCharacter->GetClassName(pc->pCharacter->GetClass()) + " GAINED A LEVEL" ;
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "STAT POINTS: " + std::to_string(mStatPoints);
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 310);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "STRENGTH:" + mFlavourText2.AddTab() + std::to_string(pc->pCharacter->GetStats().strength.second + mStrPoints);
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 400);
	mFlavourText2.SetTextScale(300, 30);

	mFlavourText3.text = "AGILITY:" + mFlavourText3.AddTab() + std::to_string(pc->pCharacter->GetStats().agility.second + mAgiPoints);
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(300, 30);

	mFlavourText4.text = "INTELLIGENCE:" + mFlavourText4.AddTab() + std::to_string(pc->pCharacter->GetStats().intelligence.second + mIntPoints);
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(640, 460);
	mFlavourText4.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFlavourText4);
	mSceneText.push_back(&mFooterInstruction);
}

void WinLoseStateScene::SetUpGameClearState()
{
	pGameClearBanner = AddObject("gameClearObj", 640, 360, UI);

	pMenuButton->SetPos({ 800, 550 });
	pQuitButton->SetPos({ 480,550 });

	for (auto character : pCharacters)
	{
		character->rObj->SetVisible(false);
	}

	pMenuButton->SetVisible(true);
	pQuitButton->SetVisible(true);
	mSceneText.clear();
}


