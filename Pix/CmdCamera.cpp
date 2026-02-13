#include "CmdCamera.h"
#include "VariableCache.h"
#include <XEngine.h>
#include "Camera.h"

bool CmdSetCameraPosition::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 3)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float x = vc->GetFloat(params[0]);
    float y = vc->GetFloat(params[1]);
    float z = vc->GetFloat(params[2]);

    X::SetCameraPosition({ x, y, z });
    return true;
}

bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 3)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float x = vc->GetFloat(params[0]);
    float y = vc->GetFloat(params[1]);
    float z = vc->GetFloat(params[2]);

    X::SetCameraDirection({ x, y, z });
    return true;
}

bool CmdSetCameraNear::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float nearPlane = vc->GetFloat(params[0]);

    if (Camera::Get() != nullptr)
    {
        Camera::Get()->SetNearPlane(nearPlane);
    }
    else
    {
    }

    return true;
}

bool CmdSetCameraFar::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float farPlane = vc->GetFloat(params[0]);

    if (Camera::Get() != nullptr)
    {
        Camera::Get()->SetFarPlane(farPlane);
    }

    return true;
}

bool CmdSetCameraFov::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float fov = vc->GetFloat(params[0]);

    if (Camera::Get() != nullptr)
    {
        // Expecting FOV in degrees in scripts; clamp happens inside Camera::SetFOV
        Camera::Get()->SetFOV(fov * X::Math::kDegToRad);
    }

    return true;
}