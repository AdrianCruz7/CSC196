#pragma once
#include "../Math/MathUtils.h"
#include "../Math/Random.h"

#include "../Input/InputSystems.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/Font.h"
#include "../Renderer/Text.h"

#include "../Core/Time.h"
#include "../Core/Memory.h"
#include "../Core/File.h"

#include "../Framework/Scene.h"
#include "../Framework/Game.h"


#include "../Audio/AudioSystem.h"

#include <memory>
#include <vector>
#include <list>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern Renderer g_renderer;
	extern AudioSystem g_audioSystem;
}