#pragma once
#include <fmod/core/inc/fmod.hpp>
#include "fmod/core/inc/fmod.h"
#include <string>
#include <map>

namespace kiko
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		~AudioSystem() = default;
		bool Initialize();
		void Shutdown();
		void Update();
		void AddAudio(const std::string& name, const std::string& filename);
		void PlayOneShot(const std::string& name, bool lopp = false);
	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

	extern AudioSystem g_AudioSystem;
}
