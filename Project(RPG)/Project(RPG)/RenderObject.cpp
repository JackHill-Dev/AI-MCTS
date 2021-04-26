#include "RenderObject.h"
#include "ManagerStruct.h"
void RenderObject::Untint()
{
	this->tint = { 255,255,255 };
}

void RenderObject::Tint(SDL_Colour tkint)
{
	this->tint = tkint;
}

RenderObject::RenderObject(std::string sprSheet, std::pair<float, float> scale)
{
	path = sprSheet;
	mCurrentAnim = nullptr;
	mVisible = true;
	this->scale = scale;
}

bool RenderObject::Update(double dTime, Act act, std::pair<int,int> mouse)
{
	return true;
}

bool RenderObject::Init()
{
	mVisible = true;
	return true;
}

std::pair<int, int> RenderObject::GetPos()
{
	return mPos;
}

void RenderObject::SetAnim(std::string id)
{
	mCurrentAnim = mSheet->GetAnim(id);
}

void RenderObject::SetPos(std::pair<float, float> nPos)
{
	mPos = nPos;
}

void RenderObject::SetTexture(SpriteSheet* nSheet)
{
	mSheet = nSheet;
}

void RenderObject::SetVisible(const bool vis)
{
	mVisible = vis;
}

SpriteSheet* RenderObject::GetSheet()
{
	return mSheet;
}

bool RenderObject::IsVisible()
{
	return mVisible;
}

void RenderObject::Select()
{
	//std::cout << "Render object clicked";
}

bool RenderObject::InBounds(int x, int y)
{
	// currenlty this allows render objects to be pressed slightly outside of the sprites bounds - JP

	//return false if cant be selected
	std::pair<float, float> bound = GetSheet()->GetCellSize();

	bound.first = bound.first / 2 * (scale.first * sceneScale.first);
	bound.second = bound.second / 2 * (scale.second * sceneScale.second);
	//float bound = GetSheet()->GetCellSize().first;
	if (x > mPos.first * sceneScale.first - bound.first && x < mPos.first * sceneScale.first + bound.first)
		return (y >= mPos.second * sceneScale.second - bound.second && y <= mPos.second * sceneScale.second + bound.second);
	else
		return false;
}

Animation* RenderObject::GetAnim()
{
	return mCurrentAnim;	
}