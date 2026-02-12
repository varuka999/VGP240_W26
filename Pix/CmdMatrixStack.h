#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
    const char* GetName() override
    {
        return "PushTranslation";
    }
    const char* GetDescription() override
    {
        return
            "ReturnTranslation(x, y, z)"
            "\n"
            "- pushes a translation matrix to the matrix stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationX";
    }
    const char* GetDescription() override
    {
        return
            "PushRotationX(degrees)"
            "\n"
            "- pushes a rotation x matrix into the stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationY";
    }
    const char* GetDescription() override
    {
        return
            "PushRotationY(degrees)"
            "\n"
            "- pushes a rotation y matrix into the stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationZ";
    }
    const char* GetDescription() override
    {
        return
            "PushRotationZ(degrees)"
            "\n"
            "- pushes a rotation z matrix into the stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
    const char* GetName() override
    {
        return "PushScaling";
    }
    const char* GetDescription() override
    {
        return
            "PushScaling(x, y, z)"
            "\n"
            "- pushes a scaling matrix into the matrix stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPopMatrix : public Command
{
public:
    const char* GetName() override
    {
        return "PopMatrix";
    }
    const char* GetDescription() override
    {
        return
            "PopMatrix()"
            "\n"
            "- pop the last matrix on the matrix stack";
    }
    bool Execute(const std::vector<std::string>& params) override;
};