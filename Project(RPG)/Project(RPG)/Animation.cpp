#include "Animation.h"
void Animation::Advance(double dTime)
{
	
	
	time += dTime * 0.1f;
	if (time >= speed)
	{
		current++;
		if (current >= frames.size())
			current = 0;
		time = 0;
	}
}
Animation::Animation(std::string name, std::vector<std::pair<int,int>> anims)
{
	this->frames = anims;
	this->name = name; 
	current = 0;
}

Animation::Animation()
{
	this->name = "UNSET";
}

std::pair<int,int> Animation::GetCurrentFrame()
{
	return frames[current];
}

std::string Animation::GetName()
{
	return name;
}