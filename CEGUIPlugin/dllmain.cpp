#include <Windows.h>
#include <ElDorito/ElDorito.hpp>
#include "CEGUIProvider.hpp"

#define PLUGIN_API extern "C" __declspec(dllexport)

ElDoritoPluginInfo ourPluginInfo =
{
	// plugin name
	"CEGUI Plugin",
	// plugin author
	"medsouz",
	// plugin description
	"Adds CEGUI support to ElDewrito.",
	// plugin version/build number, should be incremented with every release of your plugin
	1,
	// a friendly version number string we can show to the user (no leading "v"/"version" text please!)
	"0.1"
};

PLUGIN_API ElDoritoPluginInfo* __cdecl GetPluginInfo()
{
	return &ourPluginInfo;
}

PLUGIN_API bool __cdecl InitializePlugin(std::vector<std::shared_ptr<CommandProvider>>* commandProviders, std::vector<std::shared_ptr<PatchProvider>>* patchProviders)
{
	int version = GetDoritoVersion();
	int returnCode;
	IDebugLog* logger = reinterpret_cast<IDebugLog*>(CreateInterface(DEBUGLOG_INTERFACE_LATEST, &returnCode));
	//Make sure the logger interface is found
	if (returnCode != 0)
		return false;

	IEngine* engine = reinterpret_cast<IEngine*>(CreateInterface(ENGINE_INTERFACE_LATEST, &returnCode));
	//Make sure the engine interface is found
	if (returnCode != 0)
		return false;

	CEGUIPlugin::CEGUIProvider* provider = new CEGUIPlugin::CEGUIProvider(engine);
	logger->Log(LogSeverity::Debug, "CEGUIPlugin", "CEGUIProvider initialized.");
	return true;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return true;
	}

	return false;
}
