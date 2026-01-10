#include "Engine.h"
#include <functional>
#include <iostream>
#include <utility>

namespace aengine
{
	ASound::ASound() {

	}

	ASound::ASound(sf::Sound _sound, sf::SoundBuffer _buffer) : sound(_sound), buffer(_buffer) {

	}

	ASound::ASound(ASound& other) {
		this->buffer = other.buffer;
		this->sound = other.sound;
		std::cout << "Copying\n";
	}

	ASound::~ASound() {

	}

	ASound Audio::Load(const std::string& path) {
		ASound result;
		if (!result.buffer.loadFromFile(path)) {
			std::cerr << "Failed to load sound from path " << path << "\n";
			return result;
		}
		result.sound.setBuffer(result.buffer);
		return result;
	}

	std::unique_ptr<ASound> Audio::LoadPtr(const std::string& path) {
		sf::Sound sound;
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(path)) {
			std::cerr << "Failed to load sound from path " << path << "\n";
			return nullptr;
		}
		sound.setBuffer(buffer);
		return std::make_unique<ASound>(sound, buffer);
	}
}
