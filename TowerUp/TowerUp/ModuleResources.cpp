#include "stdafx.h"
#include "ModuleResources.h"


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
		return false;

	_fonts[fontType] = font;
	return true;
}
