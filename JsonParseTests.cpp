// JsonParseTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "json.hpp"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

using namespace nlohmann;
using namespace std;

#include "CommandParser.h"

int main()
{
	std::ifstream t("commands.json");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	auto commands = Commands::CommandParser().fromJason(str);
}
