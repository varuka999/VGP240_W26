#pragma once

#include "Command.h"

class CmdSetFillMode : public Command
{
public:
    const char* GetName() override
    {
        return "SetFillMode";
    }
    const char* GetDescription() override
    {
        return
            "-set fill mode of triangle being drawn\n"
            "-only applies to triangles\n"
            "-wireframe or solid (lowercase sensitive)\n"
            "-defaults to wireframe\n";
    }
    bool Execute(const std::vector<std::string>& params) override;
};