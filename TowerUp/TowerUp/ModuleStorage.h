#pragma once
#include "Module.h"

#include <string>
#include <nlohmann/json.hpp>

class ModuleStorage :
	public Module
{
public:
	ModuleStorage();
	virtual ~ModuleStorage();

	virtual bool Init() override;
	virtual bool End() override;

	int GetInt(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	std::string GetString(const std::string& name) const;
	bool GetBool(const std::string& name) const;

	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetString(const std::string& name, const std::string& value);
	void SetBool(const std::string& name, bool value);

private:
	nlohmann::json _data;
};

