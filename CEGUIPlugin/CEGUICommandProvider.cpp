#include "CEGUICommandProvider.hpp"

namespace CEGUIPlugin
{

	CEGUICommandProvider::CEGUICommandProvider() {

	}

	std::vector<Command> CEGUICommandProvider::GetCommands()
	{
		std::vector<Command> commands =
		{
			Command::CreateCommand("Example", "Test", "test_cmd", "Example plugin test command", eCommandFlagsNone, BIND_COMMAND(this, &CEGUICommandProvider::CommandTest))
		};

		return commands;
	}

	bool CEGUICommandProvider::CommandTest(const std::vector<std::string>& Arguments, CommandContext& context)
	{
		context.WriteOutput("ExampleCommandProvider: Test passed!");
		return true;
	}
}