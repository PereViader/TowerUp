#include "stdafx.h"
#include "ModuleResources.h"
#include "easylogging++.h"

ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
}
	
bool ModuleResources::Init()
{	
	//Fonts
	if (!LoadFont(FontType::Sansation, "resources/fonts/sansation.ttf"))
		return false;


	//Textures
	if (!LoadTexture(TextureType::Block, "resources/img/crate.png"))
		return false;

	if(!LoadTexture(TextureType::Ground, "resources/img/ground.png"))
		return false;

	if (!LoadTexture(TextureType::Background, "resources/img/background.jpg"))
		return false;

	//Music
	if (!LoadMusic(MusicType::Gameplay, "resources/audio/music/gameplay.wav"))
		return false;

	if (!LoadMusic(MusicType::Menu, "resources/audio/music/menu.wav"))
		return false;

	//Sounds
	if (!LoadSound(SoundType::LoseLife, "resources/audio/sound/loseLife.wav"))
		return false;

	if (!LoadSound(SoundType::PlaceBlock, "resources/audio/sound/placeBlock.wav"))
		return false;

	return true;
}

std::shared_ptr<sf::Font> ModuleResources::GetFont(FontType type) const
{
	return _fonts.at(type);
}

std::shared_ptr<sf::Texture> ModuleResources::GetTexture(TextureType type) const
{
	return _textures.at(type);
}

std::shared_ptr<sf::Music> ModuleResources::GetMusic(MusicType type) const
{
	return _musics.at(type);
}

std::shared_ptr<sf::SoundBuffer> ModuleResources::GetSound(SoundType type) const
{
	return _sounds.at(type);
}

bool ModuleResources::LoadFont(FontType fontType, const char * path)
{
	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
	
	if (!font->loadFromFile(path))
	{
		LOG(ERROR) << "Failed to load font at: " << path;
		return false;
	}

	_fonts[fontType] = font;
	return true;
}

bool ModuleResources::LoadTexture(TextureType textureType, const char * path)
{
	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(path))
	{
		LOG(ERROR) << "Failed to load texture at: " << path;
		return false;
	}

	_textures[textureType] = texture;
	return true;
}

bool ModuleResources::LoadMusic(MusicType type, const char * path)
{
	auto music = std::make_shared<sf::Music>();
	if (!music->openFromFile(path))
	{
		LOG(ERROR) << "Failed to load music at: " << path;
		return false;
	}

	_musics[type] = music;

	return true;
}

bool ModuleResources::LoadSound(SoundType type, const char * path)
{
	auto soundBuffer = std::make_shared<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile(path))
	{
		LOG(ERROR) << "Failed to load sound at: " << path;
		return false;
	}

	_sounds[type] = soundBuffer;

	return true;
}
