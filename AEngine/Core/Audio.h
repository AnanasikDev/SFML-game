#pragma once

#include "SFML/Audio.hpp"
#include <memory>

namespace aengine
{
	class ASound;

	class Audio {
	public:
		static ASound Load(const std::string& path);
		static std::unique_ptr<ASound> LoadPtr(const std::string& path);
	};

	class ASound {
	public:
		sf::Sound sound;
		sf::SoundBuffer buffer;

		ASound();
		ASound(sf::Sound _sound, sf::SoundBuffer _buffer);
		ASound(ASound& other);
		~ASound();
	};
}
