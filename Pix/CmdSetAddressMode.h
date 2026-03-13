#pragma once

#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
    const char* GetName() override
    {
        return "SetAddressMode";
    }
    const char* GetDescription() override
    {
        return
            "SetAddressMode(mocde)"
            "\n"
            "- sets the addres mode for texture objects"
            "- <border>, <clamp>, <wrap>, <mirror>";
    }
    bool Execute(const std::vector<std::string>& params) override;
};
