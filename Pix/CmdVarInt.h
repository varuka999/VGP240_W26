#pragma once

#include "Command.h"

class CmdVarInt : public Command
{
public:
	const char* GetName() override
	{
		return "int";
	}

	const char* GetDescription() override
	{
		return
			"Declares a int variable. Can optionally specify a drag speed, min, and max.\n"
			"\n"
			"syntax: int $<name> = <value>, <speed>, <min>, <max>\n"
			"\n"
			"e.g.\n"
			"  int $numVertices = 10\n"
			"  int $step = 1, 1, 0, 100\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};