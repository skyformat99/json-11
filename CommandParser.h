#pragma once

#include "Command.h"
#include <vector>

namespace nlohmann
{
	class node;
}

namespace Commands
{
	/*
		Valid JSON command format:

		{
			"Commands": [
				{
					"type": "Speed rise",
					"value": "15",
				},
				{
					"type": "Speed reduction",
					"value": "10",
					"timeToProceed": ""
				},
				{
					"type": "fuel drop",
					"value": "",
					"timeToProceed": ""
				}]
		}

		Since we translate "type" to real command type, it is very
		important that ie. "Speed rise" stay as const string.
		If changed, it needs to be fixed in lookUp. Can be found in source, as:

		std::map< std::string, Commands::Type> lookUp
			{
				{ "Speed rise", Commands::Type::speedRise },
				{ "Speed reduction", Commands::Type::speedDown },
				{ "fuel drop", Commands::Type::fuelState },
			};

		timeToProceed is optional.
	*/

	class CommandParser
	{
	public:
		std::vector<Command> fromJason(std::string jasonAsString);

	private:
		Command fromJason(const nlohmann::json& node);
		Type type(const nlohmann::json& node);
		int value(const nlohmann::json& node);
		int timeToProceed(const nlohmann::json& node);

	};
}
