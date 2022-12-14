#pragma once 
#include <iostream>
#include <map>
// !! include the necessary includes (do not include fmod here) !! 


// forward declaration to classes in the FMOD namespace 
namespace FMOD
{
	class System;
	class Sound;
}

namespace neu
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		~AudioSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayAudio(const std::string& name, bool loop = false);

	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;

	};
}