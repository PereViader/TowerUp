#pragma once
#include "Module.h"
class ModuleInput :
	public Module
{
public:
	ModuleInput();
	virtual ~ModuleInput();

	virtual UpdateStatus PreUpdate() override;
};

