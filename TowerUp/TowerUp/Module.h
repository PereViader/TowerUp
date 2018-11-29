#pragma once

enum class UpdateStatus
{
	Error,
	Continue,
	Stop
};

class Module
{
public:
	Module();
	virtual ~Module();

	virtual bool Init();

	virtual UpdateStatus PreUpdate();
	virtual UpdateStatus Update();
	virtual UpdateStatus PostUpdate();
};