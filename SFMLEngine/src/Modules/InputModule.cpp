#include "Modules/InputModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();
}
