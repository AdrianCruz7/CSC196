#include "AudioSystem.h" 
#include <fmod.hpp> 

namespace neu
{
	void AudioSystem::Initialize()
	{
		FMOD::System_Create(&m_fmodSystem);

		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		// !! use range based for-loop to iterate through m_sounds, call release on each element 
		for (auto elements : m_sounds)
		{
			elements.second->release();
		}

		// !! call clear() on m_sounds to remove all elements 
		// !! call close() on the fmod system 
		// !! call release() on the fmod system 
		
		m_sounds.clear();
		m_fmodSystem->close();
		m_fmodSystem->release();
	}

	void AudioSystem::Update()
	{
		// !! call update() on the fmod system 
		m_fmodSystem->update();  
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end()) // !! use find() on m_sounds to see if element exists, only set sound if it does not 
		{
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}

	void AudioSystem::PlayAudio(const std::string& name, bool loop)
	{
		auto iter = m_sounds.find(name); // !! use find() on m_sounds and return the iterator 
			if (iter != m_sounds.end()) // !! if iterator is not m_sounds.end() 
			{
				FMOD::Sound* sound = iter->second;

				if(loop) sound->setMode(FMOD_LOOP_NORMAL);
				else sound->setMode(FMOD_LOOP_OFF);

				FMOD::Channel* channel;
				m_fmodSystem->playSound(sound, 0, false, &channel);
			}
	}
}
