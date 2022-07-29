#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Source/Engine.h"
#include "Framework/Actor.h"
#include <Renderer/Text.h>
#include "Player.h"
#include "Enemy.h"
#include "SpaceShooter.h"

#include <iostream>
#include <vector>	
#include <array>
#include <algorithm>


using namespace std;
using namespace neu;

int main() {

	neu::InitializeMemory();
	neu::SetFilePath("../Assets");
	
	
	//initialize engine
	neu::g_inputSystem.Initialize();
	neu::g_renderer.Initialize();
	neu::g_audioSystem.Initialize();
	

	//create window
	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	neu::g_renderer.SetClearColor(neu::Color{ 10, 10, 10, 255 });

	{
		SpaceShooter game;
		game.Initialize();
		
		bool quit = false;
		while (!quit)
		{
			neu::g_time.Tick();
			neu::g_inputSystem.Update();
			neu::g_audioSystem.Update();
			
			if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) quit = true;
			
			game.Update();
			
			// render
			neu::g_renderer.BeginFrame();
			
			game.Draw(neu::g_renderer);
			
			neu::g_renderer.EndFrame();
		}
	}

	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}







