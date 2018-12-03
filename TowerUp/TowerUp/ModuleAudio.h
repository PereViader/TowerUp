#pragma once
#include "Module.h"

#include <memory>
#include <list>
#include <SFML/Audio.hpp>

struct SoundInstance
{
	SoundInstance(std::unique_ptr<sf::Sound> sound, const std::shared_ptr<sf::SoundBuffer>& buffer);

	std::unique_ptr<sf::Sound> sound;
	const std::shared_ptr<sf::SoundBuffer> buffer;
};

class ModuleAudio :
	public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	virtual UpdateStatus Update() override;

	void PlayMusic(const std::shared_ptr<sf::Music>& music);
	void PlaySoundBuffer(const std::shared_ptr<sf::SoundBuffer>& buffer, float pitch = 1.0f);

private:
	std::shared_ptr<sf::Music> _playingMusic;
	std::list<SoundInstance> _playingSounds;
};

