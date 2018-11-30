#include "stdafx.h"
#include "ModuleStorage.h"

#include <fstream>

ModuleStorage::ModuleStorage()
{
}


ModuleStorage::~ModuleStorage()
{
}

bool ModuleStorage::Init()
{
	std::ifstream fileStream("storage.json");

	if (fileStream.good()) 
	{
		// if we can access the file load it
		fileStream >> _data;
	}
	else
	{
		//otherwise, storage has no data
		_data = {};
	}

	return true;
}

bool ModuleStorage::End()
{
	std::ofstream fileStream("storage.json");

	if (!fileStream.good())
	{
		return false;
	}

	fileStream << _data;

	return true;
}

int ModuleStorage::GetInt(const std::string& name) const
{
	return _data[name].get<int>();
}

float ModuleStorage::GetFloat(const std::string& name) const
{
	return _data[name].get<float>();
}

std::string ModuleStorage::GetString(const std::string& name) const
{
	return _data[name].get<std::string>();
}

bool ModuleStorage::GetBool(const std::string& name) const
{
	return _data[name].get<bool>();
}

void ModuleStorage::SetInt(const std::string & name, int value)
{
	_data[name] = value;
}

void ModuleStorage::SetFloat(const std::string & name, float value)
{
	_data[name] = value;
}

void ModuleStorage::SetString(const std::string & name, const std::string & value)
{
	_data[name] = value;
}

void ModuleStorage::SetBool(const std::string & name, bool value)
{
	_data[name] = value;
}
