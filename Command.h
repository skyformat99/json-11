#pragma once

namespace Commands
{
	enum class Type : unsigned char
	{
		speedRise,
		speedDown,
		fuelState,

	};

	struct Command
	{
		Type type;
		int value;
		int timeToProceed;
	};
}