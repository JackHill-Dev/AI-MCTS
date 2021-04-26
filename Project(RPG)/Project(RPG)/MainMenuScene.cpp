#include "MainMenuScene.h"
#include "json.hpp"

RenderObject* LoadButton;

nlohmann::json saveFile;
MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{

	// Get all main menu button objects
	pMenuBg = AddObject("gameLogoMenuObj", 640, 380, UI);
	pMenuBg->SetScale({ 0.6, 0.8 });
	start  = AddObject("newGameButtonObj", 640, 370, UI);
	start->SetScale({ 1.5,1.2 });
	LoadButton = AddObject("ContinueButtonObj", 640, 440, UI);
	LoadButton->SetScale({ 1.5,1.2 });
	settings = AddObject("settingsBtnObj", 640, 510, UI);
	settings->SetScale({ 1.5,1.2 });
	quit = AddObject("quitBtnObj", 640, 580, UI);
	quit->SetScale({ 1.5,1.2 });


	buttons.push_back(start);
	buttons.push_back(quit);
	buttons.push_back(settings);
	
	// Get Background object
	AddObject("mainMenuBGObj", 640, 360, Background);

	

	mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");

	mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime); // Cheeky solution as this one starts as current scene without using load scene method - EH

	buttons.push_back(LoadButton);

	if (mgr->GetSeed() != 0)
	{
		LoadButton->SetVisible(true);
	}
	else
	{
		settings->SetPos({ 640,440 });
		quit->SetPos({ 640,510 });
		LoadButton->SetVisible(false);
	}
}

void MainMenuScene::Load()
{
	
	mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");

	if (mgr->GetSeed() != 0)
	{
		LoadButton->SetPos({640,440});
		settings->SetPos({640,510});
		quit->SetPos({640,580});
		LoadButton->SetVisible(true);
	}
	else
	{
		settings->SetPos({ 640,440 });
		quit->SetPos({ 640,510 });
		LoadButton->SetVisible(false);
	}

	
	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime);
	}
}

void MainMenuScene::OnHover(RenderObject* rObj)
{
	rObj->tint = SDL_Color{ 0,255,0 };
}

void MainMenuScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{

	if (act == Act::MouseUpdate)
	{
		for (auto button : buttons)
		{
			if (button->InBounds(mouse.first, mouse.second))
			{
				OnHover(button);
			}
			else
			{
				OnLeave(button);
			}
		}
	}
	mgr->LoadScene(Scenes::Overworld);
	if (act == Act::Click)
	{
		// This also disposes of previous gamestate data - EH
		if (start->InBounds(mouse.first, mouse.second) && start->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);

			for (auto& member : mgr->GetPlayer()->GetParty())
			{
				delete member;
			}

			mgr->GetPlayer()->GetParty().clear();
			mgr->GetPlayer()->ClearGold();

			for (auto& item : mgr->GetPlayer()->GetInventory())
			{
				delete item;
			}
			mgr->GetPlayer()->GetInventory().clear();
			
			mgr->LoadScene(Scenes::ClassPicker);
			OnLeave(start);
		}

		else if (quit->InBounds(mouse.first, mouse.second) && quit->IsVisible() == true)
		{
			
			mgr->Quit();
		}
		
		else if (settings->InBounds(mouse.first, mouse.second) && settings->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::SettingsPage);			
			OnLeave(settings);
		}
		else if (LoadButton->InBounds(mouse.first, mouse.second) && LoadButton->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::Overworld);			
			OnLeave(LoadButton);
		}

	}

}







