#pragma once
#include "RenderObject.h"

class ProgressBar
{
public:
	ProgressBar() {};
	ProgressBar(float value, float maxValue);
	~ProgressBar();
	void OnChange(float val);
	void SetObjects(RenderObject* fill, RenderObject* bg);
	void SetBarBgObj(RenderObject* bg);
	void SetBarFillObj(RenderObject* fill);
	void Scale(std::pair<float, float> scale) { mBarBg->scale = scale; mBarFill->scale = scale; }
private:
	float mValue, mMaxValue;
	float mPercent;
	RenderObject* mBarBg;
	RenderObject* mBarFill;
};

