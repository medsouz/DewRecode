#pragma once
#include <ElDorito/ElDorito.hpp>
#include "../imgui/imgui.h"

#include "../../Commands/ServerCommandProvider.hpp"

namespace UI
{
	class ServerListWindow : public UIWindow
	{
		bool isVisible = false;
		std::vector<Server::ServerCommandProvider::Server> servers;
		unsigned int selectedServer = 0;

	public:
		ServerListWindow();

		void Draw();
		void UpdateServerList();
		void ConnectToServer();

		bool SetVisible(bool visible) { isVisible = visible; return visible; }
		bool GetVisible() { return isVisible; }
	};
}