#include "CmdSetColor.h"

#include "Rasterizer.h"
#include "VariableCache.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
    // Need at least 3 parameters for r, g, b
    if (params.size() < 3)
    {
        return false;
    }

    // Get the float values from the variable cache if a custom float is declared
    VariableCache* vc = VariableCache::Get();
    const float r = vc->GetFloat(params[0]);
    const float g = vc->GetFloat(params[1]);
    const float b = vc->GetFloat(params[2]);

    Rasterizer::Get()->SetColor({ r, g, b, 1.0f });
    return true;
}