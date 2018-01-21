#include "stdafx.h"

#include "json.hpp"
#include "CommandParser.h"
#include <string>
#include <algorithm>

namespace Commands
{
	std::map< std::string, Commands::Type> lookUp
	{
		{ "Speed rise", Commands::Type::speedRise },
		{ "Speed reduction", Commands::Type::speedDown },
		{ "fuel drop", Commands::Type::fuelState },
	};

	Type CommandParser::type(const nlohmann::json& node)
	{
		auto eventInString = node["Event"];
		return lookUp[eventInString];
	}

	int CommandParser::value(const nlohmann::json& node)
	{
		std::string valuInString = node["value"];
		return std::atoi(valuInString.c_str());
	}

	int CommandParser::timeToProceed(const nlohmann::json& node)
	{
		if (node.find("timeToProceed") != node.end())
		{
			std::string timeInString = node["timeToProceed"];
			return timeInString == "" ? 0 : std::atoi(timeInString.c_str());
		}
		return 0;
	}

	Command CommandParser::fromJason(const nlohmann::json& node)
	{
		auto event = type(node);
		auto val = value(node);
		auto time = timeToProceed(node);

		return { event, val, time };
	}

	std::vector<Command> CommandParser::fromJason(std::string jasonAsString)
	{
		try
		{
			std::vector<Command> commands;
			nlohmann::json jsonCommands = nlohmann::json::parse(jasonAsString)["Commands"];
			std::for_each(jsonCommands.begin(), jsonCommands.end(), [&](const nlohmann::json& node)
			{
				auto command = fromJason(node);
				commands.push_back(command);
			}
			);

			return commands;
		}
		catch (...)
		{
			return std::vector<Command>();
		}
	}
}