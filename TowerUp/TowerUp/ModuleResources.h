#pragma once
#include "Module.h"

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class FontType
{
	Sansation
};

enum class TextureType
{
	Block,
	Ground,
	Background
};

enum class MusicType
{
	Menu,
	Gameplay
};

enum class SoundType
{
	PlaceBlock,
	LoseLife
};


struct Fonts {
	std::unique_ptr<sf::Font> sansation;
};

class ModuleResources :
	public Module
{
public:
	ModuleResources();
	virtual ~ModuleResources();

	virtual bool Init() override;

	std::shared_ptr<sf::Font> GetFont(FontType) const;
	std::shared_ptr<sf::Texture> GetTexture(TextureType) const;
	std::shared_ptr<sf::Music> GetMusic(MusicType) const;
	std::shared_ptr<sf::SoundBuffer> GetSound(SoundType) const;


private:
	bool LoadFont(FontType, const char * path);
	bool LoadTexture(TextureType, const char * path);
	bool LoadMusic(MusicType, const char * path);
	bool LoadSound(SoundType, const char * path);

private:
	std::map<FontType,std::shared_ptr<sf::Font>> _fonts;
	std::map<TextureType, std::shared_ptr<sf::Texture>> _textures;
	std::map<SoundType, std::shared_ptr<sf::SoundBuffer>> _sounds;
	std::map<MusicType, std::shared_ptr<sf::Music>> _musics;
};

