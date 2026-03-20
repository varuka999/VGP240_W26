#pragma once

#include "Command.h"

class CmdPostProcessingBeginDraw : public Command
{
public:
    const char* GetName() override
    {
        return "PostProcessingBeginDraw";
    }
    const char* GetDescription() override
    {
        return
            "PostProcessingBeginDraw()"
            "\n"
            "- begins rendering to the render target instead of the screen";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingEndDraw : public Command
{
public:
    const char* GetName() override
    {
        return "PostProcessingEndDraw";
    }
    const char* GetDescription() override
    {
        return
            "PostProcessingEndDraw()"
            "\n"
            "- draws the render target after applying effect type";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingSetEffectType : public Command
{
public:
    const char* GetName() override
    {
        return "PostProcessingSetEffectType";
    }
    const char* GetDescription() override
    {
        return
            "PostProcessingSetEffectType()"
            "\n"
            "- sets the effect mode to apply as a post process effect\n";
        // add the stuff
    }
    bool Execute(const std::vector<std::string>& params) override;
};

