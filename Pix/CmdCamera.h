#pragma once

#include "Command.h"

class CmdSetCameraPosition : public Command
{
public:
    const char* GetName() override
    {
        return "SetCameraPosition";
    }
	const char* GetDescription() override
	{
		return
			"CmdSetCameraPositon\n"
			"\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraDirection : public Command
{
public:
    const char* GetName()
    {
        return "SetCameraDirection";
    }
	const char* GetDescription() override
	{
		return
			"CmdSetCameraPositon\n"
			"\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraNear: public Command
{
public:
	const char* GetName()
	{
		return "CmdSetCameraNear";
	}
	const char* GetDescription() override
	{
		return
			"CmdSetCameraPositon\n"
			"\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraFar : public Command
{
public:
	const char* GetName()
	{
		return "SetCameraFar";
	}
	const char* GetDescription() override
	{
		return
			"SetCameraFar\n"
			"\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraFov : public Command
{
public:
	const char* GetName()
	{
		return "SetCameraFov";
	}
	const char* GetDescription() override
	{
		return
			"SetCameraFov\n"
			"\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};