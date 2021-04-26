#include "GameManager.h"


using Json = nlohmann::json;
void GameManager::Run()
{

	
	//scale texture later
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	Act act;

	mInterface.SetMasterVolume(-1, 16, 16);
	float overlayOpacity = 0;

	SDL_Texture* texture = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mSettings.w, mSettings.h);
	SDL_Event ev;
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;
	double deltaTime = 0;
	int lastSceneIndex = mCScene;
	while ( bRunning )
	{
		a = SDL_GetTicks();
		delta = a - b;
		if (delta > 130)
			delta = 130;
		srand(delta);
		if (mCScene != lastSceneIndex)
		{
			
			if (overlayOpacity < 255 && mCScene != InventoryScreen && mCScene != Party && (mCScene == Combat ||lastSceneIndex == Combat || lastSceneIndex == Boss || lastSceneIndex == Overworld || lastSceneIndex == MainMenu))
			{

				overlayOpacity += delta*0.0001;
			}
			else
			{
				lastSceneIndex = mCScene;
				LoadScene();
				
			}
		}
		else
			if (overlayOpacity > 0)
			{
				overlayOpacity -= delta * 0.00001;
			}
		
		

			if (delta > 1000 / 60.0 ) // 60 fps cap
			{
				//std::cout << "fps: " << 1000 / delta << std::endl;

				b = a;

				int x, y;
				act = Act::Blank;
				if (SDL_PollEvent(&ev) && overlayOpacity <= 0)
					switch (ev.type)
					{



					case SDL_KEYUP:
						if (ev.button.button == SDL_BUTTON_LEFT)
							act = Act::MouseUp;


						break;
					case SDL_MOUSEBUTTONDOWN:
						//auto e = ev.button.button;
						if (ev.button.button == SDL_BUTTON_LEFT)
							act = Act::Click;
						else
							act = Act::RClick;
						SDL_GetMouseState(&x, &y);

						break;
					case SDL_MOUSEMOTION:
						SDL_GetMouseState(&x, &y);
						act = Act::MouseUpdate;
						break;

					}


				SDL_RenderClear(mRnd);

				SDL_SetRenderTarget(mRnd, texture);
				SDL_SetRenderDrawColor(mRnd, 0x64, 0x00, 0x00, 0x00);

				SDL_SetRenderTarget(mRnd, NULL);
				if (overlayOpacity <= 0)
					scenes[mCScene]->SceneUpdate(delta, act, std::make_pair(x, y));
					scenes[mCScene]->Draw(mRnd);
				


				SDL_Texture* obj = objects["OverlayObj"]->GetSheet()->GetTexture();

			

				SDL_SetTextureBlendMode(obj, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(obj, overlayOpacity);
				int w, h;

				SDL_GetRendererOutputSize(mRnd, &w, &h);
				float resolutionScaleX = 1 + ((float)w - 1280) / 1280;
				float resolutionScaleY = 1 + ((float)h - 720) / 720;
				SDL_RenderCopy(mRnd, obj, NULL, NULL);
				SDL_RenderSetScale(mRnd,
					resolutionScaleX,
					resolutionScaleY);
				SDL_RenderPresent(mRnd);
			}
			
		

		//SDL_Delay(16);
	}
	
	Mix_CloseAudio(); // Shuts down and cleans up the whole mixer API. Ensures all music and sfx are disposed of. Mix_Quit doesn't necessarily handle everything. - EH
	SDL_DestroyRenderer(mRnd);
	SDL_DestroyWindow(mWnd);
	//TTF_CloseFont(font);
	SDL_Quit();
}
void GameManager::Quit()
{
	bRunning = false;
}
void GameManager::LoadScene()
{
	for (int i = 0; i < 7; i++)
		Mix_UnregisterAllEffects(i);
	switch (mCScene)
	{
		case Scenes::MainMenu:
		{
			LoadSettings(); 
			mMainMenuSceneInstance->Load(); break;
		}
		case Scenes::ClassPicker: 			
		{
			std::ofstream("Savedata.Json").clear();
			loadedSeed = std::rand() % 100; mClassPickerInstance->Load(); break;
		}

		case Scenes::Overworld: std::ofstream("Savedata.Json").clear(); mOverworldInstance->Load(); break;
		case Scenes::Combat: 
		{
			combatInstance.first->Load(combatInstance.second.first, combatInstance.second.second);

			rootState = MCTS_State(*combatInstance.first);
			monteCarlo = MCTS(rootState);
			monteCarlo.Select();
			break;
		}
		case Scenes::Shops: mShopSceneInstance->Load(); break;
		case Scenes::Party:  partyViewerInstance->Load(); break;
		case Scenes::SettingsPage: mSettingsSceneInstance->Load(); break;
		case Scenes::InventoryScreen : mInventorySceneInstance->Load(); break;
		case Scenes::Boss: mBossSceneInstance->Load(); break;
		case Scenes::WinLoseStateScreen: mWinLoseStateSceneInstance->Load(); break;
		default: std::cout << "Error loading scene!" << std::endl;

	}


}
bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(mSettings.w, mSettings.h, 0, &mWnd, &mRnd);
	SDL_SetWindowResizable(mWnd,SDL_TRUE);
	SDL_ShowWindow(mWnd);
	return true;
}
GameManager::~GameManager()
{
	for (auto& obj : objects)
		obj.second = nullptr;

	for (auto& sheet : sheets)
		sheet.second = nullptr;

	for (auto& item : mItems)
		item.second = nullptr;

	for (auto& i : definedSheets)
		delete i.second;
	for (auto& i : definedObjects)
		delete i.second;
	for (auto& i : definedItems)
	{
		delete i.second;
	}


	for (auto& character : combatInstance.second.first)
	{
		delete character;
		character = nullptr;
	}

	delete partyViewerInstance;
	partyViewerInstance = nullptr;

	delete mInventorySceneInstance;
	mInventorySceneInstance = nullptr;

	delete mShopSceneInstance;
	mShopSceneInstance = nullptr;

	delete mMainMenuSceneInstance;
	mMainMenuSceneInstance = nullptr;

	delete mOverworldInstance;
	mOverworldInstance = nullptr;

	delete mSettingsSceneInstance;
	mSettingsSceneInstance = nullptr;

	delete mClassPickerInstance;
	mClassPickerInstance = nullptr;

	delete mBossSceneInstance;
	mBossSceneInstance = nullptr;

	delete mWinLoseStateSceneInstance;
	mWinLoseStateSceneInstance = nullptr;

	currentScene = nullptr;

}
bool GameManager::Init()
{
	std::ifstream ifs("Settings.json");
	if (ifs.is_open())
	{
		Json jf = Json::parse(ifs);
		mSettings.mMasterVolume = jf["Audio"]["master-volume"].get<int>();
		mSettings.w = jf["Display"]["Width"].get<int>();
		mSettings.h = jf["Display"]["Height"].get<int>();
		mSettings.bIsFullScreen = jf["Display"]["fullscreen"].get<bool>();

	}
	ifs.close();
	srand(time(NULL));	
	CreateWindow();
	mInterface.StoreWindow(mWnd);
	SetUp();
	mPlayer.GeneratePositions(); // Not the best solution but this makes sure the grid positions in the shop are generated before save data comes in - JP
	LoadSettings();
	
	mPlayer.SetDeck({new Card(*cards["Slash"]), new Card(*cards["Magic"]), new Card(*cards["Slash"]), new Card(*cards["Heal"]),new Card(*cards["Magic"]), new Card(*cards["Magic"]), new Card(*cards["Shoot"]), new Card(*cards["Shoot"]) });

	mMainMenuSceneInstance = new MainMenuScene(&mInterface);
	scenes.push_back(mMainMenuSceneInstance); // 0

	mOverworldInstance = new OverworldMapScene(&mInterface);
	scenes.push_back(mOverworldInstance); // 1

	combatInstance.first = new CombatScene(&mInterface);
	scenes.push_back(combatInstance.first); // 2

	mShopSceneInstance = new ShopScene(&mInterface);
	scenes.push_back(mShopSceneInstance); // 3

	partyViewerInstance = new PartyViewerScene(&mInterface);
	scenes.push_back(partyViewerInstance); // 4

	mSettingsSceneInstance = new SettingsScene(&mInterface);
	scenes.push_back(mSettingsSceneInstance); // 5

	mClassPickerInstance = new ClassPickerScene(&mInterface);
	scenes.push_back(mClassPickerInstance); // 6

	mInventorySceneInstance = new InventoryScene(&mInterface);
	scenes.push_back(mInventorySceneInstance); // 7

	mBossSceneInstance = new BossScene(&mInterface);
	scenes.push_back(mBossSceneInstance); // 8

	mWinLoseStateSceneInstance = new WinLoseStateScene(&mInterface);
	scenes.push_back(mWinLoseStateSceneInstance); // 9

	currentScene->Clear(mRnd);
	mInterface.LoadScene(Scenes::MainMenu);
	//currentScene = scenes[0];

	return true;
}
void GameManager::LoadSettings()
{
	

	mPlayer.GetParty().clear();
	mPlayer.GetInventory().clear();
	mPlayer.ClearGold();
	std::ifstream is("Savedata.json");

	nlohmann::json loaded = nlohmann::json::parse(is, nullptr, false, false);

	if (loaded.find("Saves") != loaded.end())
	{
		if (loaded["Saves"].find("Save") != loaded["Saves"].end())
		{

			loadedSeed = loaded["Saves"]["Save"]["Seed"].get<int>();
			mPlayer.SetGold(loaded["Saves"]["Save"]["Gold"].get<int>());
			mPlayer.currentNode = loaded["Saves"]["Save"]["CurrentNode"].get<int>();

			for (auto i : loaded["Saves"]["Save"]["Inventory"])
			{
				std::string tempItem = i[0].get<std::string>();
				auto invItem = mItems[tempItem]->Clone();

				if (dynamic_cast<Armour*>(invItem))
				{
					mPlayer.AddItem(static_cast<Armour*>(invItem));
				}
				else if (dynamic_cast<Weapon*>(invItem))
				{
					mPlayer.AddItem(static_cast<Weapon*>(invItem));
				}
				else if (dynamic_cast<Consumable*>(invItem))
				{
					mPlayer.AddItem(static_cast<Consumable*>(invItem));
				}
				else
				{
					mPlayer.AddItem(invItem);
				}
			}

			for (auto i : loaded["Saves"]["Save"]["Characters"])
			{
				Weapon* weapon = nullptr;
				Armour* armour = nullptr;
				std::string temp = i["Weapon"].get<std::string>();
				if (!(temp == "NONE"))
				{
					auto test = mItems[temp]->Clone();
					Weapon* testWeapon = static_cast<Weapon*>(test);
					weapon = testWeapon;
				}
				temp = i["Armour"].get<std::string>();
				if (!(temp == "NONE"))
				{
					armour = static_cast<Armour*>(mItems[i["Armour"].get<std::string>()]->Clone());
				}
				Character* character = new Character(i["Portrait"].get<std::string>(), i["Object"].get<std::string>(), i["Name"].get<std::string>(), i["Class"].get<UnitClass>(), i["Level"].get<int>(), i["Experience"].get<std::pair<int,int>>(), i["Dead"].get<bool>(),
														i["Health"].get<std::pair<int, int>>(), i["Strength"].get<std::pair<int, int>>(), i["Intelligence"].get<std::pair<int, int>>(), i["Agility"].get<std::pair<int, int>>());
				character->mWeaponEquipSlot = weapon;
				character->ArmourEquipSlot = armour;
				mPlayer.AddToParty(character);
			}
		}
	}
	else
		loadedSeed = 0;
}



bool GameManager::SetUp()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0)
	{
		std::cout << "Mixer load failed, error: " << Mix_GetError() << std::endl;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n\n", IMG_GetError());

	}

	if(TTF_Init() < 0) {
		std::cout << "TTF lib not initialised" << TTF_GetError << std::endl;
	}
	//Converts definitions found in GameObjects.h to fully initlised and stored objects

	//Load sheets
	for (auto i : definedSheets)
	{
		sheets[i.first] = i.second;
		sheets[i.first]->SetTexture(LoadTexture(i.second->mFilePath));
	}
	
	//Add animations to sheets
	for (auto i : definedAnimations)
	{
		for (auto anim : i.second)
		{
			sheets[i.first]->AddAnim(anim.GetName(), anim);
		}
	}
	//Create Object types
	for (auto i : definedObjects)
	{
		objects[i.first] = i.second;
		objects[i.first]->SetTexture(sheets[(objects[i.first]->path)]);
		if (objects[i.first]->GetSheet()->fillScreen)
		{

			float xDif = 1+ (1280 - objects[i.first]->GetSheet()->GetCellSize().first)/ objects[i.first]->GetSheet()->GetCellSize().first;
			float yDif = 1 + (720 - objects[i.first]->GetSheet()->GetCellSize().second) / objects[i.first]->GetSheet()->GetCellSize().second;
			objects[i.first]->SetScale(std::make_pair(xDif,yDif));
		}
		//objects[i.first]->Init(mgrs);
	}
	
	for (auto i : definedCards)
	{
		CreateCard(&i.second);
	}
	for (auto i : definedItems)
	{
		mItems[i.first] = i.second;
	}

	return true;
}

SDL_Texture* GameManager::LoadTexture(std::string path)
{

	SDL_Surface* img = IMG_Load((path.c_str()));
	auto e = SDL_CreateTextureFromSurface(mRnd, img);
	SDL_FreeSurface(img);
	//if (IMG_GetError)
	//	throw std::invalid_argument("could not load image at: " + path);
	//std::cout << IMG_GetError() << std::endl;
	return e;
}


void GameManager::CreateCard(DefinedCard* card)
{
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	auto mFont = TTF_OpenFont("Assets/Fonts/ThaleahFat.ttf", 32);

	int imageWidth = 225;

	int imageHeight = 225;



	SDL_Surface* base_S = SDL_CreateRGBSurface(0, sheets["card"]->GetCellSize().first, sheets["card"]->GetCellSize().second,32, rmask, gmask, bmask, amask);
	SDL_Texture* base = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sheets["card"]->GetCellSize().first, sheets["card"]->GetCellSize().second);
	SDL_Surface* img = IMG_Load(("Assets/Sprites/Card/CardTemplateNew.png"));

	
	
	std::string picture = "Assets/Sprites/Card/" + card->picture + ".png";
	SDL_Surface* pic = IMG_Load(picture.c_str());
	
	SDL_BlitScaled(pic, &pic->clip_rect, base_S, &base_S->clip_rect);

	SDL_BlitSurface(img, &img->clip_rect, base_S, &base_S->clip_rect);

	

	SDL_SetRenderTarget(mRnd, base);

	SDL_Rect rect;

	SpriteSheet* obj = sheets["card"];

	SDL_Rect crop;
	crop.x = 0;
	crop.y = 0;
	crop.w = imageWidth;
	crop.h = imageHeight;

	rect.w = imageWidth;
	rect.h = imageHeight;
	rect.x = 0;
	rect.y = 0;

	/*SDL_RenderCopy(mRnd, sheets[card->picture]->GetTexture(), NULL, &rect);
	SDL_RenderCopy(mRnd, sheets["card"]->GetTexture(), NULL, NULL);*/









	rect.w = 191;
	rect.h = 76;
	rect.x = 20;
	rect.y = 222;
	SDL_Surface* desc = TTF_RenderText_Blended_Wrapped(mFont, card->description.c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(desc, &desc->clip_rect, base_S, &rect);



	rect.x = 24;
	rect.y = 10;
	rect.w = 188;
	rect.h = 22;
	SDL_Surface* name = TTF_RenderText_Blended_Wrapped(mFont, card->name.c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(name, &name->clip_rect, base_S, &rect);

	rect.x = 20;
	rect.y = 184;
	rect.w = 39;
	rect.h = 27;
	SDL_Surface* range = TTF_RenderText_Blended_Wrapped(mFont, std::to_string(card->range).c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(range, &range->clip_rect, base_S, &rect);
	

	rect.x = 73;
	rect.y = 184;
	rect.w = 39;
	rect.h = 27;
	SDL_Surface* staminaCost = TTF_RenderText_Blended_Wrapped(mFont, std::to_string(card->staminaCost).c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(staminaCost, &staminaCost->clip_rect, base_S, &rect);
	

	rect.x = 123;
	rect.y = 184;
	rect.w = 39;
	rect.h = 27;
	SDL_Surface* intelligenceCost = TTF_RenderText_Blended_Wrapped(mFont, std::to_string(card->intelligenceCost).c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(intelligenceCost, &intelligenceCost->clip_rect, base_S, &rect);


	rect.x = 173;
	rect.y = 184;
	rect.w = 39;
	rect.h = 27;
	SDL_Surface* agilityCost = TTF_RenderText_Blended_Wrapped(mFont, std::to_string(card->agilityCost).c_str(), SDL_Color{ 0,0,0 }, rect.w);
	SDL_BlitScaled(agilityCost, &agilityCost->clip_rect, base_S, &rect);

	rect.x = 10;
	rect.y = 2;
	rect.w = 100;
	rect.h = 15;

	obj = new SpriteSheet("", sheets["card"]->GetTextureSize().first, sheets["card"]->GetTextureSize().second, sheets["card"]->GetTextureSize().first, sheets["card"]->GetTextureSize().second, 1);

	

	obj->SetTexture(SDL_CreateTextureFromSurface(mRnd, base_S));
	sheets["cardSheet_"+ std::to_string(cards.size())] = obj;

	objects["cardObj" + std::to_string(cards.size())] = new RenderObject("card1");

	objects["cardObj" + std::to_string(cards.size())]->SetTexture(sheets["cardSheet_" + std::to_string(cards.size())]);

	cards[card->name] = new Card(card->damage, card->name, card->range, "cardObj" + std::to_string(cards.size()), card->animation, card->animationLength, card->staminaCost, card->intelligenceCost, card->agilityCost) ;
	SDL_SetRenderTarget(mRnd, NULL);
	
	
}

