#include "Modules/InputModule.h"

#include "Modules/WindowModule.h"
#include "ModuleManager.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();
}
