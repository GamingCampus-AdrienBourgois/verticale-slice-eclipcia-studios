#pragma once

#include <vector>
#include "Module.h"

class ModuleManager
{
public:
	ModuleManager() = default;
	~ModuleManager();

	void CreateDefaultModules();

	void Awake() const;
	void Start() const;
	void Update() const;

	void PreRender() const;
	void Render() const;
	void OnGUI() const;
	void PostRender() const;
	void OnDebug() const;
	void OnDebugSelected() const;
	void Present() const;

	void OnEnable() const;
	void OnDisable() const;

	void Destroy() const;
	void Finalize() const;

	template<class T>
	T* CreateModule();

	template<class T>
	T* GetModule();

private:
	std::vector<Module*> modules;
};

template<class T>
T* ModuleManager::CreateModule()
{
	T* module = new T();
	module->moduleManager = this;
	modules.push_back(module);
	return module;
}

template<class T>
T* ModuleManager::GetModule()
{
	for (Module*& module : modules)
	{
		T* module_cast = dynamic_cast<T*>(module);
		if (module_cast)
		{
			return module_cast;
		}
	}
	return nullptr;
}
