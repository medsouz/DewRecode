#include "ServerListWindow.hpp"
#include "../../ElDorito.hpp"

#include <cstdio>

namespace UI
{
	ServerListWindow::ServerListWindow()
	{
	}

	void ServerListWindow::Draw()
	{
		if (!isVisible)
			return;

		ImGui::SetNextWindowSize(ImVec2(520, 300), ImGuiSetCond_FirstUseEver);
		if (!ImGui::Begin("Server List", &isVisible))
		{
			ImGui::End();
			return;
		}

		std::stringstream ss;
		ImGui::BeginChild("server list", ImVec2(0, ImGui::GetWindowHeight() * 0.3), true);
		for (std::vector<Server::ServerCommandProvider::Server>::size_type i = 0; i != servers.size(); i++)
		{
			ss.str("");//Clear the stringstream
			ss.clear();
			ss << servers[i].name << " - By " << servers[i].hostPlayer << std::endl << "\t" << servers[i].map << " | " << servers[i].variant << " (" << servers[i].numPlayers << "/" << servers[i].maxPlayers << ")";
			if (ImGui::Selectable(ss.str().c_str(), selectedServer == i))
				selectedServer = i;
		}
		ImGui::EndChild();

		ImGui::BeginChild("server info", ImVec2(0, ImGui::GetWindowHeight() * 0.6), true);
		if(selectedServer < servers.size())
		{
			ImGui::BeginGroup();
				ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
					ss.str("");
					ss.clear();
					ss << servers[selectedServer].name << " - By " << servers[selectedServer].hostPlayer;
					ImGui::Text(ss.str().c_str(), selectedServer);
					ImGui::Separator();
					ss.str("");
					ss.clear();
					ss << "Map: " << servers[selectedServer].map << std::endl;
					ss << "Variant: " << servers[selectedServer].variant << std::endl;
					ImGui::TextWrapped(ss.str().c_str());
				ImGui::EndChild();
				ImGui::BeginChild("buttons");
					if (ImGui::Button("Refresh"))
					{
						UpdateServerList();
					}
					ImGui::SameLine();
					if (ImGui::Button("Connect")) 
					{
						ConnectToServer();
					}
				ImGui::EndChild();
			ImGui::EndGroup();
		}
		else
		{
			selectedServer = 0;
		}
		ImGui::EndChild();

		ImGui::End();
	}

	void ServerListWindow::UpdateServerList()
	{
		auto& dorito = ElDorito::Instance();
		servers = dorito.ServerCommands->ListServers();
	}

	void ServerListWindow::ConnectToServer()
	{
		auto& dorito = ElDorito::Instance();
		if (selectedServer < servers.size())
		{
			//TODO: Implement ServerCommandProvider.Connect()
			//Manually invoke a connect command
			std::vector<std::string> args;
			args.push_back(servers[selectedServer].host);
			dorito.ServerCommands->CommandConnect(args, dorito.CommandManager.ConsoleContext);
		}
	}
}