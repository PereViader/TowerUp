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
	if (!LoadFont(FontType::Sansation, "resources/fonts/sansation.ttf"))
		return false;

	if (!LoadTexture(TextureType::Crate, "resources/img/crate.png"))
		return false;

	if(!LoadTexture(TextureType::Ground, "resources/img/ground.png"))
		return false;

	if (!LoadTexture(TextureType::Background, "resources/img/background.jpg"))
		return false;

	return true;
}

std::shared_ptr<sf::Font> ModuleResources::GetFont(FontType type) const
{
	return _fonts.at(type);
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
