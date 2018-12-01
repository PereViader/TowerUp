#pragma once
#include "Module.h"

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

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

private:
	bool LoadFont(FontType, const char * path);
	bool LoadTexture(TextureType, const char * path);

private:
	std::map<FontType,std::shared_ptr<sf::Font>> _fonts;
	std::map<TextureType, std::shared_ptr<sf::Texture>> _textures;
};

