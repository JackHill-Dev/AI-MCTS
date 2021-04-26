#include "Scene.h"
#include "GameManager.h"
Scene::Scene(Interface* objmg)
{
	mgr = objmg;
	std::vector<RenderObject*> rObjects;

	for (int i = 0; i < layerNum; ++i)
	{
		mLayers.push_back(rObjects);
	}

	mFont = TTF_OpenFont("Assets/Fonts/ThaleahFat.ttf", 32);
	
}

Scene::~Scene()
{
	for (UIText* t : mSceneText)
	{
		t = nullptr;
	}

	mgr = nullptr;
}


void Scene::SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos)
{
	Update(dTime, act, mousePos);
	float rTime = dTime / 1000;
	std::for_each(mLayers.begin(), mLayers.end(), [dTime, rTime, act, mousePos](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [dTime, rTime, act, mousePos](RenderObject* obj) {obj->Update(dTime, act, mousePos); obj->GetAnim()->Advance(dTime); });
		});
	
	
}

void Scene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	
};

void Scene::Draw(SDL_Renderer* rnd)
{
	SDL_Rect rect;
	SDL_Rect crop;
	int w, h;

	SDL_GetRendererOutputSize(rnd, &w, &h);
	float resolutionScaleX = 1 + ((float)w - 1280) / 1280; 
	float resolutionScaleY = 1 + ((float)h - 720) / 720;
	
	std::for_each(mLayers.begin(), mLayers.end(), [rnd, &rect, &crop, resolutionScaleX, resolutionScaleY](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [rnd, &rect, &crop, resolutionScaleX, resolutionScaleY](RenderObject* obj) {if (obj->IsVisible())


		{
			obj->sceneScale = std::make_pair(resolutionScaleX, resolutionScaleY);

			crop.x = obj->GetAnim()->GetCurrentFrame().first * obj->GetSheet()->GetCellSize().first;
			crop.y = obj->GetAnim()->GetCurrentFrame().second * obj->GetSheet()->GetCellSize().second;
			crop.w = obj->GetSheet()->GetCellSize().first;
			crop.h = obj->GetSheet()->GetCellSize().second;


			rect.w = obj->GetSheet()->GetCellSize().first * (obj->scale.first);// *resolutionScaleX); //scaling currentky buggy with inbounds, need to fix -T
			rect.h = obj->GetSheet()->GetCellSize().second * (obj->scale.second);// *resolutionScaleY);

			rect.x = obj->GetPos().first  - rect.w/2;
			rect.y = obj->GetPos().second  - rect.h/2;

		/*	if (obj->GetSheet()->GetTexture() == NULL)
				std::cout << " Cant load texture:";*/

			SDL_SetTextureColorMod(obj->GetSheet()->GetTexture(), obj->tint.r, obj->tint.g, obj->tint.b);

			if (obj->IsVisible())
				SDL_RenderCopy(rnd, obj->GetSheet()->GetTexture(), &crop, &rect);
		}
		});


		});
	// TODO - Surface from UIText isn't being freed.
	for (auto& t : mSceneText)
	{
		rect.w = t->scale.first;
		rect.h = t->scale.second;
				  
		rect.x = t->pos.first - rect.w/2;
		rect.y = t->pos.second - rect.h/2;
		
		t->mFontTexture = nullptr;
		t->mTempTextSurface = nullptr;

		if (!t->bWrapped)
		{
			t->mTempTextSurface = TTF_RenderText_Blended(mFont, t->text.c_str(), t->textColor);
			t->mFontTexture = SDL_CreateTextureFromSurface(rnd, t->mTempTextSurface);
			SDL_FreeSurface(t->mTempTextSurface);
		}
		else
		{
			t->mTempTextSurface = TTF_RenderText_Blended_Wrapped(mFont, t->text.c_str(), t->textColor, 300);
			t->mFontTexture = SDL_CreateTextureFromSurface(rnd, t->mTempTextSurface);
			SDL_FreeSurface(t->mTempTextSurface);
		}

	    if(t->isVisible)
			SDL_RenderCopy(rnd, t->mFontTexture, nullptr, &rect);
		SDL_DestroyTexture(t->mFontTexture);
		t->mFontTexture = nullptr;
	}

	

	
	++counter;
	
}
// When mouse is inside bounds of a render object in current scene

void Scene::Clear(SDL_Renderer* rnd)
{
	SDL_RenderClear(rnd);
	SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);
	SDL_RenderPresent(rnd);
}


RenderObject* Scene::AddObject(std::string obj, double x, double y, Layer layerNum)
{
	RenderObject* obje = mgr->RequestObject(obj);

	mLayers[layerNum].push_back(obje);

	obje->SetAnim("default");
	obje->SetPos(std::make_pair(x, y));
	return obje;

	return &*mLayers[layerNum].back();

}
