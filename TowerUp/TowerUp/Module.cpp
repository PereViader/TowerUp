#include "stdafx.h"
#include "Module.h"


Module::Module()
{
}


Module::~Module()
{
}

bool Module::Init()
{
	return true;
}

UpdateStatus Module::PreUpdate()
{
	return UpdateStatus::Continue;
}

UpdateStatus Module::Update()
{
	return UpdateStatus::Continue;
}

UpdateStatus Module::PostUpdate()
{
	return UpdateStatus::Continue;
}
