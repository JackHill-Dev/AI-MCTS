#include "ProgressBar.h"

ProgressBar::ProgressBar(float value, float maxValue) : mValue(value), mMaxValue(maxValue)
{
}

ProgressBar::~ProgressBar()
{
	/*mBarBg = nullptr;
	delete mBarBg;
	mBarFill = nullptr;
	delete mBarFill;*/
}



void ProgressBar::OnChange(float val)
{
	mValue = val;
	mPercent = mValue / mMaxValue;
	int x = mBarBg->GetPos().first;
	float w = mBarFill->GetSheet()->GetCellSize().first;

	
	float px = x - (w * ( 1 - mPercent)) / 2; // Update fill bar position and recenter it

	mBarFill->SetScale(std::make_pair(mPercent, 1));
	mBarFill->SetPos(std::make_pair(px, mBarBg->GetPos().second));

}

void ProgressBar::SetObjects(RenderObject* fill, RenderObject* bg)
{
	mBarBg = bg;
	mBarFill = fill;
}

void ProgressBar::SetBarBgObj(RenderObject* bg)
{
	mBarBg = bg;
}

void ProgressBar::SetBarFillObj(RenderObject* fill)
{
	mBarFill = fill;
}
