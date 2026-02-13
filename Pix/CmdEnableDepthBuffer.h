#pragma once

#include "Command.h"

class CmdEnableDepthBuffer : public Command
{
public:
    const char* GetName() override
    {
        return "EnableDepthBuffer";
    }
    const char* GetDescription() override
    {
        return
            "EnableDepthBuffer(enable)\n"
            "\n"
            "- enavles/disables the depth buffer rendering\n";
    }
    bool Execute(const std::vector<std::string>& params) override;
};