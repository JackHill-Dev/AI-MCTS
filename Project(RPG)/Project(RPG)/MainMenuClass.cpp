#include "MainMenuClass.h"
#include "Character.h"
#include "GameManager.h"
RenderObject* start;
RenderObject* quit;
MainMenuClass::MainMenuClass(Interface* rng) : Scene(rng)
{
	// Get all button objects
	//pMenuButton = AddObject("StartBtnObj", 5, 90, UI);
	quit = AddObject("quitBtnObj", 70, 400, UI);
	// Get Background object
	start = AddObject("startBtnObj", 70, 90, UI);
	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)
	AddObject("mainMenuBGObj", 640, 360, Background);
}

void MainMenuClass::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	//Its better to do button checks here, as this way you can iterate through specific layer, but current functionality in buttons is fine - T
	if (act == Act::Click)
	{
		if (start->InBounds(mouse.first, mouse.second))

			mgr->LoadScene(Scenes::Overworld);

		else
			if (quit->InBounds(mouse.first, mouse.second))
				mgr->Quit();
	}
	

}

