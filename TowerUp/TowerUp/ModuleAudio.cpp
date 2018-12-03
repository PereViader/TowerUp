#include "stdafx.h"
#include "ModuleAudio.h"


ModuleAudio::ModuleAudio()
{
}


ModuleAudio::~ModuleAudio()
{
}

UpdateStatus ModuleAudio::Update()
{
	auto it = _playingSounds.begin();
	while (it != _playingSounds.end())
	{
		if ((*it).sound->getStatus() == sf::SoundSource::Status::Stopped)
		{
			it = _playingSounds.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	return UpdateStatus::Continue;
}

void ModuleAudio::PlayMusic(const std::shared_ptr<sf::Music>& music)
{
	if (_playingMusic)
	{
		_playingMusic->stop();
	}

	_playingMusic = music;

	music->setLoop(true);
	music->play();
}

void ModuleAudio::PlaySoundBuffer(const std::shared_ptr<sf::SoundBuffer>& buffer, float pitch)
{
	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>(*buffer);
	sound->setPitch(pitch);
	sound->play();

	_playingSounds.push_back(SoundInstance(std::move(sound), buffer));
}

SoundInstance::SoundInstance(std::unique_ptr<sf::Sound> sound, const std::shared_ptr<sf::SoundBuffer>& buffer) :
	sound(std::move(sound)),
	buffer(buffer)
{
}
